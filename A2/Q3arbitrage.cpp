/*
 * ANSWERS
 *
 * (a) MODELLING AS A WEIGHTED DIRECTED GRAPH:
 *     - Each currency = a vertex
 *     - Each exchange rate R[i][j] = a directed edge i → j
 *     - Edge weight = R[i][j] (the multiplier)
 *     - Arbitrage = a cycle where product of weights > 1
 *
 * (b) LOGARITHMIC TRANSFORMATION:
 *     Maximize: R[i][j] × R[j][k] × ... > 1
 *     Taking -log(): -log(R[i][j]) + -log(R[j][k]) + ... < 0
 *     This converts a multiplicative cycle product problem
 *     into an additive shortest-path/negative-cycle problem.
 *     Key insight: log converts multiplication → addition,
 *     and the negation flips maximization → minimization.
 *
 * (c) ALGORITHM USED — BELLMAN-FORD:
 *     Justification:
 *     - We need to detect negative cycles → Bellman-Ford is
 *       the standard algorithm for this.
 *     - Dijkstra cannot be used here: after log transformation,
 *       weights can be negative (when R[i][j] > 1).
 *     - Floyd-Warshall could also work (check dist[i][i] < 0)
 *       but Bellman-Ford is O(VE) vs Floyd's O(V³) — better
 *       for sparse currency graphs.
 *     - Run Bellman-Ford with all dist[] = 0 (virtual source
 *       connected to all vertices with 0-cost edges), then
 *       check if V-th relaxation still updates → negative cycle.
 * 
 * Example given below
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

const double INF = 1e18;

int main() {
    int N; 
    cout << "Enter number of currencies: ";
    cin >> N;

    vector<vector<double>> rate(N, vector<double>(N, 0.0));
    cout << "Enter exchange rate matrix (" << N << "×" << N << "):\n";
    cout << "(rate[i][j] = amount of currency j per 1 unit of currency i)\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> rate[i][j];

    struct Edge {
        int u, v;
        double w;
    };

    vector<Edge> edges;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && rate[i][j] > 0) {
                edges.push_back({i, j, -log(rate[i][j])});
            }
        }
    }

    vector<double> dist(N, 0.0); 
    for (int pass = 0; pass < N - 1; pass++) {
        for (auto& e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    bool arbitrage = false;
    int arb_vertex = -1;
    for (auto& e : edges) {
        if (dist[e.u] + e.w < dist[e.v]) {
            arbitrage = true;
            arb_vertex = e.v;
            break;
        }
    }

    cout << "\n Arbitrage Detection \n";
    if (arbitrage) {
        cout << "✓ ARBITRAGE OPPORTUNITY DETECTED!\n";
        cout << "  A negative cycle exists involving currency " << arb_vertex << ".\n";
        cout << "  By cycling through exchange rates along this path,\n";
        cout << "  you can generate profit from nothing.\n";
    } else {
        cout << "✗ No arbitrage opportunity found.\n";
        cout << "  No negative cycle exists in the -log(rate) graph.\n";
    }

    return 0;
}

