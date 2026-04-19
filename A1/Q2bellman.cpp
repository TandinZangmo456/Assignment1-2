#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int V, E;
    cout << "Enter V (vertices) and E (edges): ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge as: u v w\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<long long> dist(V, LLONG_MAX);
    dist[src] = 0;

    for (int pass = 1; pass <= V - 1; pass++) {
        bool updated = false;
        for (auto& e : edges) {
            if (dist[e.u] != LLONG_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) {
            cout << "\n[Early termination at pass " << pass << "]\n";
            break;
        }
    }


    bool neg_cycle = false;
    for (auto& e : edges) {
        if (dist[e.u] != LLONG_MAX && dist[e.u] + e.w < dist[e.v]) {
            neg_cycle = true;
            break;
        }
    }

    cout << "\n Bellman-Ford Results \n";
    if (neg_cycle) {
        cout << "⚠  Negative weight cycle detected! Shortest paths undefined.\n";
    } else {
        cout << "Shortest distances from vertex " << src << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "  Vertex " << i << " : ";
            if (dist[i] == LLONG_MAX) cout << "UNREACHABLE\n";
            else cout << dist[i] << "\n";
        }
    }

    return 0;
}

/*
 *
 * COMPLEXITY:
 *   Time  : O(V × E)
 *   Space : O(V + E)
 *
 * WHY V-1 PASSES?
 *   A shortest path (without negative cycles) can have at most V-1 edges.
 *   Each pass i guarantees all paths using ≤ i edges are correctly settled.
 *
 * NEGATIVE CYCLE DETECTION:
 *   If a V-th relaxation still improves any distance, it means a cycle
 *   with negative total weight exists — traversing it always reduces cost.
 */