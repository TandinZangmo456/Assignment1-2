/* Problem Statement and Edmonds' Algorithm Implementation
 *
 * Problem: Minimum Spanning Arborescence (Directed Minimum
 *          Spanning Tree or Optimum Branching Problem)
 *
 * Given:
 *   - A DIRECTED weighted graph G = (V, E) with edge weights w(u,v)
 *   - A designated root vertex r ∈ V
 *
 * Find:
 *   A spanning arborescence rooted at r — a subgraph T of G such that:
 *     1. T contains exactly V-1 edges
 *     2. Every vertex v ≠ r has exactly ONE incoming edge in T
 *     3. r has no incoming edge in T
 *     4. There exists a directed path from r to every other vertex
 *     5. The total sum of edge weights in T is MINIMIZED
 *
 * OR find the minimum-weight directed spanning tree
 * rooted at r, where all edges point AWAY from the root.
 *
 * // Why is this non-trivial?
 *
 * For undirected graphs, Prim's or Kruskal's algorithm finds the
 * MST greedily. For DIRECTED graphs, this greedy approach fails
 * because choosing the cheapest incoming edge to each vertex can
 * create DIRECTED CYCLES — which Edmonds' algorithm handles.
 *
 * ALGORITHM OVERVIEW (Edmonds' / Chu-Liu Algorithm)
 *
 * Step 1 — Greedy Selection:
 *   For each vertex v ≠ r, select the minimum-weight incoming edge.
 *
 * Step 2 — Cycle Detection:
 *   If the selected edges form no directed cycle → done (this IS
 *   the minimum arborescence).
 *
 * Step 3 — Cycle Contraction:
 *   If a directed cycle C exists:
 *     a) Contract C into a single super-vertex
 *     b) Reweight all edges entering C:
 *        w'(u, C) = w(u, v) - w(cheapest_incoming_to_v_in_C)
 *        (This represents the "savings" of switching into C at v)
 *     c) Recursively find the arborescence in the contracted graph
 *
 * Step 4 — Expansion:
 *   Expand the super-vertex back, removing exactly one edge of
 *   the cycle C — the one that was "replaced" by the incoming
 *   edge chosen for the super-vertex in the recursive step.
 */

#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
using namespace std;

const int MAXN = 505;
const long long INF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

long long edmonds(vector<Edge>& edges, int root, int V) {
    long long result = 0;
    vector<int> id(V), prev_node(V), vis(V);

    while (true) {
        vector<long long> minIn(V, INF);
        fill(prev_node.begin(), prev_node.end(), -1);

        for (auto& e : edges) {
            if (e.u != e.v && e.v != root && e.w < minIn[e.v]) {
                minIn[e.v] = e.w;
                prev_node[e.v] = e.u;
            }
        }

        for (int i = 0; i < V; i++) {
            if (i != root && minIn[i] == INF) return -1; 
        }

        for (int i = 0; i < V; i++)
            if (i != root) result += minIn[i];

        fill(id.begin(), id.end(), -1);
        fill(vis.begin(), vis.end(), -1);
        int cnt = 0;

        for (int i = 0; i < V; i++) {
            if (i == root) continue;
            int v = i;
            while (vis[v] == -1 && id[v] == -1 && v != root)
                vis[v] = i, v = prev_node[v];

            if (v != root && id[v] == -1 && vis[v] == i) {
                int u = v;
                do {
                    id[u] = cnt;
                    u = prev_node[u];
                } while (u != v);
                cnt++;
            }
        }

        if (cnt == 0) break; 

        for (int i = 0; i < V; i++)
            if (id[i] == -1) id[i] = cnt++;

        for (auto& e : edges) {
            int u = id[e.u], v = id[e.v];
            if (u != v) {
                e.w -= minIn[e.v]; 
            }
            e.u = u;
            e.v = v;
        }

        root = id[root];
        V = cnt;
        minIn.assign(V, INF);
        prev_node.assign(V, -1);
        id.assign(V, -1);
        vis.assign(V, -1);
    }

    return result;
}

int main() {
    int V, E;
    cout << "Enter V (vertices) and E (edges): ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges as: u v w\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    int root;
    cout << "Enter root vertex: ";
    cin >> root;

    cout << "\n====== Edmonds' Algorithm — Problem Statement ======\n";
    cout << "PROBLEM: Minimum Spanning Arborescence\n\n";
    cout << "Given a directed weighted graph G = (V, E) and a root r,\n";
    cout << "find a subgraph T such that:\n";
    cout << "  1. T contains exactly V-1 edges\n";
    cout << "  2. Every vertex v != r has exactly ONE incoming edge in T\n";
    cout << "  3. r has NO incoming edge in T\n";
    cout << "  4. A directed path exists from r to every other vertex\n";
    cout << "  5. The total weight of edges in T is MINIMIZED\n\n";
    cout << "In short: find the minimum-weight directed spanning tree\n";
    cout << "rooted at r where all edges point away from the root.\n";
    cout << "====================================================\n";

    long long ans = edmonds(edges, root, V);

    cout << "\n====== Edmonds' Algorithm Result ======\n";
    if (ans == -1)
        cout << "No spanning arborescence exists from root " << root << ".\n";
    else
        cout << "Minimum arborescence weight from root " << root << ": " << ans << "\n";

    return 0;
}

/*
 * COMPLEXITY:
 *   Time  : O(VE) per iteration, O(V) iterations - O(V²E)
 *   With priority queue optimizations: O(E log V)
 *
 * APPLICATIONS:
 *   - Network design (minimum-cost broadcast trees)
 *   - Dependency resolution in directed systems
 *   - Optimizing directed communication networks
 *   - Phylogenetic tree construction in bioinformatics
 */