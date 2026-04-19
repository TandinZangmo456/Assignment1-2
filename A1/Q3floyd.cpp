#include <iostream>
#include <vector>
using namespace std;
 
const long long INF = 1e18;
 
int main() {
    int V, E;
    cout << "Enter V (vertices) and E (edges): ";
    cin >> V >> E;
 
    vector<vector<long long>> dist(V, vector<long long>(V, INF));
    for (int i = 0; i < V; i++) dist[i][i] = 0; 
 
    cout << "Enter each edge as: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); 
    }
 
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    bool neg_cycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            neg_cycle = true;
            cout << "\n Negative cycle detected involving vertex " << i << "!\n";
            break;
        }
    }
 
    if (neg_cycle) {
        cout << "All-pairs shortest paths are UNDEFINED due to negative cycle.\n";
        return 0;
    }
 
    cout << "\n All-Pairs Shortest Path Matrix \n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << "  [" << j << "]";
    cout << "\n";
 
    for (int i = 0; i < V; i++) {
        cout << "[" << i << "]  ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "  INF";
            else cout << "  " << dist[i][j] << "  ";
        }
        cout << "\n";
    }
 
    return 0;
}


/*
 * Part D
 *
 * WHY IT WORKS WITH NEGATIVE EDGE WEIGHTS:
 *   Floyd-Warshall is based on dynamic programming.
 *   dist[i][j] = min cost path from i to j using only
 *   intermediate vertices {0..k}. The recurrence:
 *
 *       dist[i][j] = min(dist[i][j],  dist[i][k] + dist[k][j])
 *
 *   only ever adds weights — never multiplies — so negative
 *   edge weights are handled correctly. As long as there is
 *   no negative CYCLE, a true minimum exists and is found.
 *
 * WHY IT FAILS WITH NEGATIVE CYCLES:
 *   A negative cycle is a cycle whose total weight < 0.
 *   Traversing it repeatedly keeps decreasing path cost
 *   toward −∞, so no finite "shortest" path exists.
 *   Detection: after the algorithm, any dist[i][i] < 0
 *   means vertex i lies on a negative cycle.
 *   All paths passing through such vertices become invalid.
 */