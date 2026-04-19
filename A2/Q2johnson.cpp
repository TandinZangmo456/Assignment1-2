#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const long long INF = 1e18;

struct Edge {
    int to, weight;
};

bool bellmanFord(int V, vector<vector<Edge>>& adj, vector<long long>& h) {
    fill(h.begin(), h.end(), 0); 

    for (int pass = 0; pass < V - 1; pass++) {
        for (int u = 0; u < V; u++) {
            for (auto& e : adj[u]) {
                if (h[u] + e.weight < h[e.to]) {
                    h[e.to] = h[u] + e.weight;
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (auto& e : adj[u]) {
            if (h[u] + e.weight < h[e.to]) return false;
        }
    }
    return true;
}

// Dijkstra from a single source using reweighted edges
vector<long long> dijkstra(int src, int V, vector<vector<Edge>>& adj,
                           vector<long long>& h) {
    vector<long long> dist(V, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto& e : adj[u]) {
            long long newW = e.weight + h[u] - h[e.to];
            if (dist[u] + newW < dist[e.to]) {
                dist[e.to] = dist[u] + newW;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

int main() {
    int V, E;
    cout << "Enter V and E: ";
    cin >> V >> E;

    vector<vector<Edge>> adj(V);
    cout << "Enter edges as: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> h(V);
    if (!bellmanFord(V, adj, h)) {
        cout << "Negative cycle detected! Johnson's Algorithm cannot proceed.\n";
        return 1;
    }

    cout << "\n Johnson's All-Pairs Shortest Paths \n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << "  [" << j << "]";
    cout << "\n";

    for (int src = 0; src < V; src++) {
        vector<long long> dist = dijkstra(src, V, adj, h);
        cout << "[" << src << "]  ";
        for (int j = 0; j < V; j++) {
            if (dist[j] == INF) cout << "  INF ";
            else {
                long long original = dist[j] - h[src] + h[j];
                cout << "  " << original << "   ";
            }
        }
        cout << "\n";
    }

    return 0;
}

/*
 * QUESTIONS AND ANSWERS
 *
 * (a) WHY JOHNSON'S IS MORE EFFICIENT THAN FLOYD-WARSHALL
 *     FOR SPARSE GRAPHS:
 *
 *     Floyd-Warshall: O(V³) time, O(V²) space — always.
 *     Johnson's     : O(V² log V + VE) time
 *
 *     For a SPARSE graph where E << V², Johnson's is faster:
 *       - Sparse example: E = O(V) → Johnson's = O(V² log V)
 *         vs Floyd's O(V³) — significantly faster for large V.
 *       - Dense graph (E ≈ V²): both are roughly equivalent.
 *
 *     Real-world sparse graphs: road networks, social graphs,
 *     sparse dependency trees — Johnson's is the clear winner.
 *
 *
 * (b) EDGE REWEIGHTING AND BELLMAN-FORD'S ROLE:
 *
 *     Problem: Dijkstra requires non-negative edge weights.
 *     But the graph may have negative weights.
 *
 *     Solution — Johnson's reweighting trick:
 *       1. Add a virtual source vertex q with zero-cost edges
 *          to every vertex in the graph.
 *       2. Run Bellman-Ford from q → get h[v] for each vertex
 *          (h[v] = shortest distance from q to v).
 *       3. Reweight each edge (u,v,w):
 *             w'(u,v) = w + h[u] - h[v]
 *          This is ALWAYS ≥ 0 (triangle inequality guarantees it).
 *       4. Now run Dijkstra from every vertex on the reweighted
 *          graph safely.
 *       5. Restore original distances:
 *             d(u,v) = dijkstra_dist[v] - h[u] + h[v]
 *
 *     Why does reweighting preserve shortest paths?
 *       The reweighting adds h[u] and subtracts h[v] along every
 *       path. For any path u→...→v, the total adjustment is
 *       always h[u] - h[v] regardless of the path taken.
 *       So relative ordering of paths is preserved — shortest
 *       path before = shortest path after reweighting.
 *
 * COMPLEXITY SUMMARY:
 *   Bellman-Ford step : O(VE)
 *   V × Dijkstra      : O(V(E + V) log V) with a min-heap
 *   Total             : O(VE + V² log V)
 */