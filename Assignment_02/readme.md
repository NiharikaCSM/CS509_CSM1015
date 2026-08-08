# Assignment 02

**Title:** Single-Source and All-Pairs Shortest Paths (Bellman-Ford and Floyd-Warshall)

**Type:** Individual

**Objective:** Implement Bellman-Ford (single-source shortest path, tolerant
of negative edge weights) and Floyd-Warshall (all-pairs shortest path) on a
CSR (Compressed Sparse Row) graph representation, measure the execution
time of each algorithm and detect and report negative-weight cycles where the algorithm's own procedure calls for it. The adjacency-list-to-CSR conversion is not reimplemented here — it is called directly from `assignment_01/src/graph.c`.

## Explanation of the Algorithm / Approach

**Bellman-Ford**

Computes the shortest distance from a single source vertex to every other vertex, and works correctly even when some edge weights are negative. It relaxes every edge in the graph, repeated V-1 times, where V is the number of vertices. After the V-1 passes, one additional pass is run: if any edge can still be relaxed, a negative-weight cycle is reachable from the source and distances are undefined. Running time is O(V·E).

**Floyd-Warshall**

Computes the shortest distance between every pair of vertices in a single run, using dynamic programming. For every intermediate vertex `k`, it updates `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])` for every pair `(i, j)`. It also tolerates negative edge weights, provided the graph has no negative-weight cycle. After the DP completes, a negative `dist[i][i]`
on the diagonal indicates a negative-cylce was present. Running time is O(V³) and memory usage is O(V²), so it is only run on the smaller graph sizes.

## Input Format, Assumptions, and Constraints

**Bellman-Ford** — directed, weighted adjacency-list file:
```
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
SOURCE s
```
- `V` vertices, `E` directed edges. A vertex with no outgoing edges is
  written as `u 0`.
- Edge weights may be negative; `s` is the source vertex for the run.

**Floyd-Warshall** — dense adjacency-matrix file:
```
V
row 0 values
row 1 values
...
row (V-1) values
```
- Each row has exactly `V` space-separated entries: an integer weight, or
  the literal token `INF` for "no direct edge". `(i, i)` must be `0`.
- No `SOURCE` line as Floyd-Warshall computes all pairs at once.

Bellman-Ford reads its input as an adjacency list and converts it to CSR using `readAdjacencyListAsCSR()` from `assignment_01/src/graph.c`, exactly as written for Assignment 1. The function is linked  via the Makefile, not copied. Floyd-Warshall is exempt from CSR. It reads a dense V x V matrix directly.

**Assumptions:**
- Vertices are numbered 0 to V-1 and listed in that order in the file.
- Bellman-Ford's input graph does not contain a negative-weight cycle reachable from the source unless the test case is specifically designed to exercise negative-cycle detection (and likewise for Floyd-Warshall).
- To indicate no edge between vertices for Floyd-Warshall's input matrix, token "INF" is used.  

**Constraints:**
- Floyd-Warshall's O(V³) time and O(V²) memory rule out the 50,000 /100,000 vertex scale used for Bellman-Ford 
- Bellman-Ford's two largest graphs (50,000 and 100,000 vertices) are kept sparse (E ≈ 2V to 4V) so that O(V·E) stays practical.
- `colIndex` and `edgeWeights` in the CSR structure are sized at `2 x E` (the same upper-bound convention as Assignment 1), even though Bellman-Ford's edges are directed and not double-counted per endpoint.


## Source Files, Driver Files, Helper Functions, and Test Files

**`src/bellman_ford.c` / `bellman_ford.h`**

- `runBellmanFord(graph, source)` — runs the V-1 loop plus the extra negative cycle detection pass directly on the CSR arrays. It returns distances, reachability, and the negative-cycle flag.
- `printBellmanFordResult(result)` — prints the distance table or the negative-cycle message, plus the execution time.
- `freeBellmanFordResult(result)` — frees the result's memory allocations

**`src/floyd_warshall.c` / `include/floyd_warshall.h`**

- `readAdjacencyMatrix(file, &vertices)` — reads the dense `V x V` matrix format directly (Floyd-Warshall does not go through CSR).
- `runFloydWarshall(matrix, vertices)` — the O(V³) DP over every intermediate vertex `k`, followed by the diagonal negative-cycle check.
- `printFloydWarshallResult(result)` — prints the distance matrix or the negative-cycle message, plus the execution time.
- `freeFloydWarshallResult(result)` / `freeMatrix(matrix, vertices)` — free the matrices.

**`src/driver.c`** — contains `main()`. Reads the input file path and algorithm name (`bf` or `fw`) and dispatches to the Bellman-ford or Floyd-Warshall runner accordingly, timing execution and printing the result.

**`tests/`** — adjacency-list files (`bf_*.txt`) and dense-matrix files (`fw_*.txt`) at the required sizes, plus one dedicated negative-cycle test per algorithm. (`*_bad_*.txt`) are malformed input files used to verify error handling.

## Compilation and Execution Instructions

From inside `Assignment_02/` 
```bash
cd Assingment_02
```

**Compile:**
```bash
make
```

**Run (Bellman-Ford):**
```bash
./run tests/bf_10.txt bf
```

**Run (Floyd-Warshall):**
```bash
./run tests/fw_10.txt fw
```

## Bellman-Ford / Floyd-Warshall Results Table

| Algorithm | Test File | Vertices | Edges | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
|---|---|---|---|---|---|---|---|---|---|
| BellmanFord | bf_test_01.txt | 10 | 20 | 0 | No | Distances | Distances (matches) | 0.0030 ms | Pass |
| BellmanFord | bf_negative_cycle.txt | 10 | 14 | 0 | Yes | Negative cycle: true | Negative cycle: true | 0.0050 ms | Pass |
| BellmanFord | bf_test_02.txt | 100 | 400 | 0 | No | Distances | Distances (matches) | 0.0200 ms | Pass |
| BellmanFord | bf_test_03.txt | 10000 | 30000 | 0 | No | Distances | Distances (matches) | 2.3860 ms | Pass |
| BellmanFord | bf_test_04.txt | 50000 | 150000 | 0 | No | Distances | Distances (matches) | 11.4800 ms | Pass |
| BellmanFord | bf_test_05.txt | 100000 | 300000 | 0 | No | Distances | Distances (matches) | 21.3120 ms | Pass |
| FloydWarshall | fw_test_01.txt | 10 | 20 | N/A | No | Distance matrix | Distance matrix (matches) | 0.0090 ms | Pass |
| FloydWarshall | fw_negative_cycle.txt | 10 | 20 | N/A | Yes | Negative cycle: true | Negative cycle: true | 0.0090 ms | Pass |
| FloydWarshall | fw_test_02.txt | 100 | 400 | N/A | No | Distance matrix | Distance matrix (matches) | 3.0620 ms | Pass |
| FloydWarshall | fw_test_03.txt | 500 | 2000 | N/A | No | Distance matrix | Distance matrix (matches) | 230.2390 ms | Pass |
| FloydWarshall | fw_test_04.txt | 1000 | 4000 | N/A | No | Distance matrix | Distance matrix (matches) | 1746.2270 ms | Pass |
| FloydWarshall | fw_test_05.txt | 2000 | 8000 | N/A | No | Distance matrix | Distance matrix (matches) | 14321.4530 ms | Pass |

Note: Floyd-Warshall input files have no explicit E field. The Edges column above is the count of non-INF off-diagonal matrix entries, i.e. the number of directed edges the dense matrix encodes.

## Input Validation Test Results

| Test File | Malformed Condition | Program Output | Exit Code | Status |
|---|---|---|---|---|
| bf_bad_header_missing_E.txt | Header line has only V, missing E | `Input format error: Expected 'V E' on the first line, but couldn't read two integers from it.` | 1 | Correctly rejected |
| bf_bad_vertex_order.txt | Vertices not listed in order 0 to V-1 | `Input format error: vertices must be listed in order 0 to V-1; expected vertex line for a different vertex than the one found.` | 1 | Correctly rejected |
| bf_bad_neighbor_range.txt | A neighbor id is out of range | `Input format error: a neighbor id is out of range (must be between 0 and V-1)` | 1 | Correctly rejected |
| bf_bad_missing_source.txt | File has no trailing `SOURCE s` line | `Error: expected a trailing 'SOURCE s' line in 'tests/invalid/bf_bad_missing_source.txt'` | 1 | Correctly rejected |
| bf_bad_source_outOfRange.txt | `SOURCE` vertex id is outside 0..V-1 | `Error: source vertex 99 is out of range` | 1 | Correctly rejected |
| fw_bad_diagonal.txt | `dist[i][i]` in the input is not 0 | `Input format error: diagonal entry (i, i) must be 0.` | 1 | Correctly rejected |
| fw_bad_row_length.txt | A matrix row has fewer than V entries | `Input format error: matrix ended early or contained a malformed entry.` | 1 | Correctly rejected |
| fw_bad_token.txt | A matrix entry is neither an integer nor `INF` | `Input format error: matrix entry is neither an integer nor the literal token INF.` | 1 | Correctly rejected |
| (missing file path) | Input file does not exist | `Error: could not open input file 'tests/does_not_exist.txt'` | 1 | Correctly rejected |


## Time and Space Complexity

**Bellman-Ford:**
- Time complexity: O(V·E) : V-1 passes, each scanning every edge once, plus one extra full pass for negative-cycle detection.
- Space complexity: O(V + E) : the CSR arrays (`rowPtr`, `colIndex`, `edgeWeights`) plus the `dist[]` and `reachable[]` arrays of size V.

**Floyd-Warshall:**
- Time complexity: O(V³) : three nested loops over every intermediate vertex `k` and every pair `(i, j)`.
- Space complexity: O(V²) : the full `V x V` distance matrix is kept in memory (the input matrix and the working copy).