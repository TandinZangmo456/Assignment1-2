**Assignments 1 & 2 — Report**


# **Introduction**

This report covers the two programming assignments completed. Assignment 1 deals with Standard Template Library containers in C++, the Bellman-Ford single-source shortest path algorithm, and the Floyd-Warshall all-pairs shortest path algorithm. 

Assignment 2 covers subset enumeration using bitmasking, Johnson's algorithm, arbitrage detection using graph theory, Edmonds' minimum spanning arborescence algorithm, and string matching using the Knuth-Morris-Pratt and Rabin-Karp algorithms.



# **Assignment 1**

## **Question 1: STL Usage in C++**

The C++ Standard template library offers a collection of general purpose containers, which do not require one to write their own common data structures. Three of them are utilized in this question: vector, deque, and std::array. Each was selected on the basis of being the most suitable to a certain task.

### ***Algorithm Explanation***

**vector** 

vector is a dynamically sized array that is stored on the heap. The reason it was used here is that N, the number of elements, is unknown at compile-time. It can be reversed in O(N) with the STL reverse() operation which switches the elements at both ends and moves towards the middle.

**deque** 
The operation task was selected as deque (double-ended queue) due to its O(1) insertions and deletions at the front and back side respectively. A vector would require push front to take O(N) time as it would have to move all the elements making it incorrect in cases where front operations are required.

**std::array** 
std array is a fixed-size array, the size of which must be known at compile-time. It resides on the stack and not the heap and hence faster to allocate. It is also aware of its size, unlike a raw C array, and can be used with STL algorithms such as accumulate() to add up elements and max_element() to find the largest element.

Here is the input and output that would be given when a sample is run.

### ***Sample Input and Output***

| Part | Input | Output |
| :---- | :---- | :---- |
| A — vector | N=5,  1 2 3 4 5 | Reversed: 5 4 3 2 1 |
| B — deque | push\_back 10, push\_front 5, push\_back 20, pop\_front | Deque: 10 20 |
| C — std::array | 3 1 4 1 5 | Sum=14, Max=5, Min=1 |

### ***Complexity Analysis***

| Operation | Time | Space |
| :---- | :---- | :---- |
| reverse() | O(N) | O(1) |
| push\_front / pop\_front | O(1) | O(N) |
| accumulate() | O(N) | O(1) |
| max\_element() | O(N) | O(1) |

## **Question 2: Bellman-Ford Algorithm**


Bellman-Ford algorithm is used to determine the minimum path of one source node to the other nodes in a directed weighted graph. It is even applicable when the weights on the edges are negative which the Dijkstra algorithm fails to deal with. The assumption that the distance of a settled vertex is final is made by Dijkstra, but later on a negative edge might violate this assumption.

### ***Algorithm Explanation***

The algorithm starts by initialising all the distances to infinity with the exception of the source, which is set to one. It then repeats the process of relaxing all the edges: in case of an edge between u and v that has a weight w, when there is a shorter distance between u and v than the existing known distance to v it changes the distance of v. This relaxation is done V-1 times with V the number of vertices.

This is because a shortest path with no cycles can touch at most V vertices and there are actually V-1 such paths, hence the name V-1 passes. Pass k All the shortest paths using k or fewer edges are settled correctly.

One more pass following V-1 relaxations is done to detect negative cycles. When any distance further reduces, then there is a cycle of negative total weight in the graph. A cycle like this can enable the cost of the path to reduce endlessly hence there is no finite shortest path.

### ***Sample Input and Output***

Graph: 5 vertices, 8 edges including negative weights, source \= vertex 0\.

| Vertex | Shortest Distance from Vertex 0 |
| :---- | :---- |
| 0 | 0  (source) |
| 1 | \-1 |
| 2 | 2 |
| 3 | \-2 |
| 4 | 1 |

### ***Complexity Analysis***

| Metric | Value | Reason |
| :---- | :---- | :---- |
| Time | O(V x E) | V-1 passes, each iterating over all E edges |
| Space | O(V \+ E) | Distance array of size V plus edge list of size E |

## **Question 3: Floyd-Warshall Algorithm**

Floyd-Warshall finds the shortest paths between all pairs of the graph vertices at the same time. It supports negative edge weights and dynamic programming and is therefore more general than Dijkstra and easier to implement than to run Bellman-Ford at each vertex.

### ***Algorithm Explanation***

The algorithm has a V by V distance matrix. The diagonal is initially initialized to be zero (cost of edge to a vertex) and known edge weights are entered into their corresponding cells, with the rest initialized to infinity.

In each case of a potential intermediate vertex k, the algorithm examines all pairs (i, j): in case the direct path between i and j is longer than the direct path between i and k, the matrix is updated. On completion of processing all V intermediate vertices, the shortest path between any two is stored in dist\[i]][j].

This is because with negative weights, the operation is always additive-- it only asks whether a particular path sum is less than another. No avaricious guess is engaged upon as to the end paths. It is inadmissible with negative cycles since a negative cycle will permit a path cost to reduce indefinitely, and the shortest distance will be undefined. Once the algorithm is complete, a dist\[i] less than zero means that vertex i is on a negative cycle.

### ***Sample Input and Output***

Graph: 4 vertices, 5 directed edges.

|  | \[0\] | \[1\] | \[2\] | \[3\] |
| :---- | :---- | :---- | :---- | :---- |
| \[0\] | 0 | 3 | 5 | 6 |
| \[1\] | 8 | 0 | 2 | 3 |
| \[2\] | INF | INF | 0 | 1 |
| \[3\] | INF | INF | INF | 0 |

### ***Complexity Analysis***

| Metric | Value | Reason |
| :---- | :---- | :---- |
| Time | O(V^3) | Three nested loops, each running V times |
| Space | O(V^2) | V by V distance matrix |

# **Assignment 2**

## **Question 1: Bitmasking**

Bitmasking uses the binary representation of integers to represent subsets of a set. There are 2 N subsets of elements. The set of subsets of a set of size N is the set of integers between 0 and 2N -1, each of which is a subset. This provides a succinct and effective method of listing all subsets without recursion.

### ***Algorithm Explanation***

In order to obtain all the subsets, we repeat a variable mask in the range 0 to (1<N-1). 
For each mask we need to check each bit position i using the expression (mask & (1 \<\< i)). Assuming this is non-zero, then element i is in the current subset. We add up the items listed and decide whether it is a multiple of K.

### ***Sample Input and Output***

Input: N=3, array \= {1, 2, 3}, K \= 3\.

| Subset | Sum | Divisible by 3 |
| :---- | :---- | :---- |
| { } | 0 | Yes |
| { 1 } | 1 | No |
| { 2 } | 2 | No |
| { 1, 2 } | 3 | Yes |
| { 3 } | 3 | Yes |
| { 1, 3 } | 4 | No |
| { 2, 3 } | 5 | No |
| { 1,2,3 } | 6 | Yes |

Result: 4 out of 8 subsets are divisible by 3\.

### ***Complexity Analysis***

| Metric | Value | Reason |
| :---- | :---- | :---- |
| Time | O(2^N x N) | 2^N subsets, checking N bits per subset |
| Space | O(N) | Only the current subset is stored at any time |
| Constraint | N \<= 20 | 2^20 is about 1 million — manageable |

## **Question 2: Johnson's Algorithm**

The algorithm by Johnson is a solution to the all-pairs shortest path problem similar to Floyd-Warshall, but it is more efficient on sparse graphs. It achieves this by executing one Bellman-Ford run, and one Dijkstra run per vertex, with a reweighting step to ensure all edge weights are non-negative, allowing Dijkstra to be used.

### ***Algorithm Explanation***

This algorithm introduces a virtual source vertex, connected to each real vertex with zero-weight edges, and performs Bellman-Ford starting at the virtual source. The resulting shortest paths h\[v\] are possible values of each vertex. The weight of all edges (u, v) with weight w is then reweighted to w' = w + h[u] - h[v] which is non-negative by the triangle inequality.

Dijkstra is again executed on all the nodes of the reweighted graph. Once the Dijkstra distances have been obtained, the original distances are reconstructed with d(u,v) = dijkstra_dist\[v\] - h\[u] + h\[v]]. The reweighting does not alter the shortest path since all the paths between the same two nodes are moved by the same constant distance.

On sparse graphs with the number of edges E far less than V2, Johnson runs in O(VE + V2 log V) which is much faster than the O(V3) of FloydWarshall.

### ***Sample Input and Output***

Graph: 4 vertices, 5 directed edges including one negative weight edge.

|  | \[0\] | \[1\] | \[2\] | \[3\] |
| :---- | :---- | :---- | :---- | :---- |
| \[0\] | 0 | 3 | 8 | \-4 |
| \[1\] | INF | 0 | INF | 7 |
| \[2\] | INF | 4 | 0 | 11 |
| \[3\] | INF | INF | INF | 0 |

### ***Complexity Analysis***

| Phase | Time | Reason |
| :---- | :---- | :---- |
| Bellman-Ford | O(VE) | Run once from the virtual source |
| V x Dijkstra | O(V(E+V) log V) | One run per vertex on reweighted graph |
| Total | O(VE \+ V^2 log V) | Better than O(V^3) when E is small |

## **Question 3: Arbitrage Detection**


Currency exchange Arbitrage in currency exchange is when one begins with a unit of a currency, and by changing it to another currency, then to another currency, and finally returns to the original currency, the person will have more than one unit of a currency. It is a nothing-profit in itself- a sheer mathematical chance given by unstable exchange rates.

### ***Algorithm Explanation***

The issue is represented as a directed graph, with each currency being a vertex and each exchange rate R\[i\]\[j] being a directed edge between currency i and j. Arbitrage exists when a cycle satisfies R\[i\]\[j\] x R\[j\]\[k\] x ... \> 1\.

The negative logarithm is used to transform this multiplicative condition into an additive one. Taking \-log of both sides, the arbitrage condition becomes: \-log(R\[i\]\[j\]) \+ \-log(R\[j\]\[k\]) \+ ... \< 0\. This is exactly what a negative cycle in a graph is when the weight of each edge is the negative log of the exchange rate. Bellman-Ford is then run on this transformed graph. A negative cycle proves the presence of an arbitrage opportunity, in case a V-th relaxation pass continues to update any distance.

This can not be done using Dijkstra since once the log transformation has been made, some of the edge weights are negative. Bellman-Ford can deal with negative weights, and it can identify negative cycles, which is why it is the correct option.

### ***Sample Input and Output***

| From \\ To | USD | EUR | GBP |
| :---- | :---- | :---- | :---- |
| USD | 1.0 | 0.85 | 0.75 |
| EUR | 1.18 | 1.0 | 0.88 |
| GBP | 1.33 | 1.14 | 1.0 |

Output: with these rates, no arbitrage is detected. If a rate like EUR to GBP is inflated to 1.5, the product of rates around a cycle exceeds 1 and arbitrage is detected.

## **Question 4: Edmonds' Algorithm**

Edmonds' algorithm solves the minimum spanning arborescence problem: given a directed weighted graph and a root vertex, find the lowest-cost subgraph where every non-root vertex has exactly one incoming edge and every vertex is reachable from the root. This is the directed equivalent of finding a minimum spanning tree.

### ***Algorithm Explanation***

The algorithm by Edmonds is a solution to the minimum spanning arborescence problem: given a directed weighted graph and a root node, the minimum-cost spanning subgraph is to be found with the only difference that the non-root nodes have only one incoming edge and the root is reachable by all nodes. This is the directed variant of minimum spanning tree.

### ***Algorithm Explanation***

In the case of undirected graphs, the Prim or Kruskal algorithm is applicable since you can select any edge freely. With a directed graph, it is easy to greedily select the cheapest incoming edge to each vertex to form directed cycles, which are prohibited in an arborescence.

To address this Edmonds algorithm identifies cycles in the greedy selection and contracts each cycle into a single super-vertex and reweighting the edges entering the cycle to indicate the cost of breaking into the cycle at each entry point. The algorithm recursively acts on the contracted graph. On returning it is again enlarged with the same edge and precisely one of them being removed the one that was in effect replaced by the incoming edge that has been selected in the recursive step.

### ***Sample Input and Output***

Graph: 4 vertices, 6 directed edges, root \= vertex 0\.

Output: Minimum arborescence weight from root 0 \= 4\. This represents the cheapest set of 3 directed edges that connects all vertices back to the root.

### ***Complexity Analysis***

| Metric | Value | Notes |
| :---- | :---- | :---- |
| Time (basic) | O(V^2 x E) | Per iteration, optimised versions use a priority queue |
| Time (optimised) | O(E log V) | Using Fibonacci heaps |
| Space | O(V \+ E) | Adjacency list and distance arrays |

## **Question 5: String Matching Algorithms**

String matching is a problem of locating all the occurrences of a given pattern in a text. The naive method examines each word in the text resulting in a worst-case time of O(N x M). Both KMP and Rabin-Karp enhance this, but with a different approach to prevent unnecessary work.

### ***KMP — Algorithm Explanation***

KMP preprocesses the pattern to create an LPS (Longest prefix suffix) array. LPS\[i\] is the length of the longest proper prefix of pattern\[0..i\] which happens to be a suffix. In case of a mismatch at position j in the pattern, the algorithm does not restart at position 0. rather it moves back to LPS[j-1] since all that comes before it is certain to fit the text.

The text pointer does not move backwards, hence the search stage is O(N). The LPS construction has O(M). Together the algorithm runs in O(N \+ M) in all cases with no worst-case degradation.

### ***KMP — LPS Array for Pattern 'ABABCABAB'***

| Index | Char | LPS | Reasoning |
| :---- | :---- | :---- | :---- |
| 0 | A | 0 | No proper prefix possible for a single character |
| 1 | B | 0 | B does not match A |
| 2 | A | 1 | Pattern\[0\] A equals Pattern\[2\] A — prefix A equals suffix A |
| 3 | B | 2 | AB equals AB — prefix of length 2 matches suffix |
| 4 | C | 0 | C does not match A, fallback to 0 |
| 5 | A | 1 | A matches A again, length 1 |
| 6 | B | 2 | AB matches again, length 2 |
| 7 | A | 3 | ABA equals ABA, length 3 |
| 8 | B | 4 | ABAB equals ABAB — longest prefix equals suffix, length 4 |

Final LPS: \[ 0, 0, 1, 2, 0, 1, 2, 3, 4 \]

Search result on 'ABABDABABCABABCABAB': pattern found at index 5 and index 10\.

### ***Rabin-Karp — Algorithm Explanation***

Rabin-Karp calculates a hash of the pattern and slides a window over the text, calculating the hash of each window in O(1) with a rolling hash formula. When the window hash is not equal to the pattern hash, that window is immediately skipped without making any comparisons of the characters. The algorithm only matches hashes to verify the characters when they are equal.

The hash collision (spurious hit) is defined when the hash of two different strings is equal. This results in a false positive - the hashes are identical but the strings are not. This and the algorithm proceed will be caught by the character comparison that will follow. To ensure that spurious hits are infrequent a large prime is taken as the modulus and a well-spread base is selected.

The key benefit of Rabin-Karp compared to KMP is the multiple pattern matching. When K patterns must be located in a single text, they can be hashed and stored in a set and the window hashes compared to the set as a whole in O(1). This implies that a single pass through the text reveals all K patterns so the total is O(N + KM) rather than the O(KM) that would have been incurred by repeating KMP K times.

### ***Sample Input and Output***

Search for pattern 'ABAB' in text 'ABCCDABABABCABAB':

| Algorithm | Result | Spurious Hits |
| :---- | :---- | :---- |
| KMP | Found at indices 5, 7, 12 | N/A — no hashing |
| Rabin-Karp | Found at indices 5, 7, 12 | 0 (with good hash parameters) |

### ***Complexity Analysis***

| Algorithm | Time (average) | Time (worst) | Multi-pattern? |
| :---- | :---- | :---- | :---- |
| KMP | O(N \+ M) | O(N \+ M) — always | No |
| Rabin-Karp | O(N \+ M) | O(N x M) — bad hash or adversarial input | Yes — O(N \+ K\*M) |

# **Conclusion**

Both the assignments discuss a sequence of concepts in the design of algorithms. The basics are set in Assignment 1 is selecting an appropriate data structure to use in a task (STL containers), finding the shortest path starting from a single source (Bellman-Ford) and generalizing that to pairs (Floyd-Warshall). The improvements in Assignment 2 build upon these foundations with more specialised algorithms: Johnson improves all-pairs performance on sparse graphs by reweighting Bellman-Ford with Dijkstra; arbitrage detection reframes a financial problem as negative cycle detection; and KMP and Rabin-Karp demonstrate two entirely different methods of eliminating redundant work in string search.

One trend that cuts across all the algorithms in this section is the concept of work repetition prevention by using previously calculated data. KMP precalculates the LPS array in such a way that it does not revisit a match. Rabin-Karp precomputes a rolling hash in such a way that it never has to do character comparisons. Bellman-Ford constructs edge-by-edge shortest paths, and never discards the output of past passes. Floyd-Warshall re-solves sub problems solved earlier. Johnson precomputes possible values in such a way that Dijkstra can be implemented. Learning this pattern is what enables one to reason why an algorithm works and not just memorise the steps.