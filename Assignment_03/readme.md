# Assignment 03

**Title:** Minimum Spanning Tree — Kruskal's Algorithm and Prim's Algorithm

**Type:** Individual

**Objective:** Implement both Kruskal's and Prim's algorithms for finding a Minimum Spanning Tree (MST) of a connected, weighted, undirected graph represented in CSR (Compressed Sparse Row) format, run both on the same input files so their results and execution times can be directly compared.

## Explanation of the Algorithm / Approach

**Kruskal's Algorithm**

A greedy algorithm: consider every edge in the graph in increasing order of weight, and add an edge to the growing graph only if its two endpoints currently belong to different components (i.e., adding it would not create
a cycle). A Disjoint Set Union (DSU / Union-Find) structure is used to answer "are these two vertices
already connected?" in near-constant time. Stops once V-1 edges have been selected. 

**Prim's Algorithm**

Also greedy, but grows a single tree outward one vertex at a time rather than considering all edges globally. Starting from vertex 0, it repeatedly adds the cheapest edge connecting a vertex already in the tree to a vertex outside
it. This implementation uses a binary min-heap with lazy deletion.

**Disjoint Set Union (`src/dsu.c`)**

A standard Union-Find structure supporting `find` (with path compression: every visited node on the way to the root gets re-pointed directly at it) and `union` (by rank: the shorter tree is always attached under the taller one's root, keeping future `find` calls fast). `dsuUnion` returns whether a union actually happened, which is exactly Kruskal's cycle check, if the two endpoints were already in the same set, adding that edge
would close a cycle, so it's skipped.

**Binary Min-Heap (`src/min_heap.c`)**

A minimal array-based binary heap supporting push and pop-min, used by Prim to always pick the next cheapest crossing edge in O(log V) time. 

**CSR Graph Conversion (reused, not reimplemented)**

Both algorithms read their input as a weighted, undirected adjacency list, converted to CSR via `readAdjacencyListAsCSR()` from
`Assingment_01/src/graph.c` — linked in via the Makefile, not copied.

## Input Format, Assumptions, and Constraints

**MST** — weighted, undirected adjacency-list file:
```
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
```
- `V` vertices, `E` **undirected** edges (each edge counted once, even
  though it appears in both adjacency lists, with the same weight on
  both sides).
- No `SOURCE` line, MST considers the whole graph, not a single source.
- Edge weights may be positive, zero, or negative integers.

**Assumptions:**
- Vertices are numbered 0 to V-1 and listed in that order in the file.
- The graph is connected,  this is checked, not just assumed; a valid MST input with V > 1 cannot contain
  an isolated vertex.
- Every edge genuinely appears in both endpoints' adjacency lists with
  matching weight — also checked, not just assumed.

**Constraints:**
- Both algorithms are run on the *same* input files.
- The `colIndex`/`edgeWeights` arrays in the CSR structure are sized at
  `2 x E`, matching each undirected edge being listed once per endpoint.
- Prim's min-heap is allocated with capacity equal to the total number of
  directed CSR entries (`rowPtr[V]`), a safe upper bound on how many
  times any push could ever occur, since a push only happens when
  traversing an edge.

## Source Files, Driver Files, Helper Functions, and Test Files

**`src/kruskal.c` / `kruskal.h`**
- `runKruskal(graph)` — the algorithm described above; returns the
  selected edges (in the order added), the total weight, and the
  measured time. Also defines `MSTEdge` (`{u, v, weight}`), reused by
  Prim's result type as well.
- `printKruskalResult(result)` / `freeKruskalResult(result)`.

**`src/prims.c` / `prims.h`**
- `runPrim(graph)` — the algorithm described above, starting from vertex
  0, using the min-heap.
- `printPrimResult(result)` / `freePrimResult(result)`.

**`src/dsu.c` / `dsu.h`** — Union-Find with path compression and union by
rank, used only by Kruskal.

**`src/min_heap.c` / `min_heap.h`** — the lazy-deletion binary min-heap,
used only by Prim.

**`utils/graph_utils.c` / `graph_utils.h`** — shared preprocessing/validation:
- `sortNeighborListsWeighted(graph)` — sorts each vertex's `(neighbor,
  weight)` pairs by neighbor id, enabling binary search.
- `getEdgeWeight(graph, u, v, &outWeight)` — binary search for a directed
  edge's weight; requires the above sort to have run first.
- `validateUndirectedWeightedSymmetry(graph)` — the symmetry + weight
  check described above.
- `validateConnected(graph)` — the connectivity check described above.


**`driver/kruskal_runner.c`, `driver/prim_runner.c`** (with matching `.h`
files) — each independently opens the input file, builds and validates
CSR (untimed), then calls its algorithm (timed) and prints the result.

**`driver/driver.c`** — contains `main()`. Reads the input file path and algorithm name (`kruskal` or `prim`) and dispatches to the Kruskal or Prim runner accordingly, timing execution and printing the result.

**`tests/`** — MST input files at the required sizes.

**`tests/invalid/`** — malformed input files, including two specific to
this assignment (an edge missing its reciprocal, an edge with mismatched
weights between directions, and a disconnected graph).

## Compilation and Execution Instructions

From inside `Assignment_03/`:

```bash
cd Assignment_03
```

**Compile:**
```bash
make
```

**Run (Kruskal only):**
```bash
./run tests/mst_10.txt kruskal
```

**Run (Prim only):**
```bash
./run tests/mst_10.txt prim
```

## MST Results Table

| File | V | E  | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal Weight? | Status |
|---|---|---|---|---|---|---|---|---|
| mst_10.txt | 10 | 20  | 53 | 53 | 0.0070 ms | 0.0070 ms | Yes | Pass |
| mst_100.txt | 100 | 300  | -66 | -66 | 0.0810 ms | 0.0470 ms | Yes | Pass |
| mst_10000.txt | 10000 | 15000  | 187717 | 187717 | 1.6510 ms | 3.3810 ms | Yes | Pass |
| mst_50000.txt | 50000 | 75000  | 934832 | 934832 | 5.9800 ms | 14.4610 ms | Yes | Pass |
| mst_100000.txt | 100000 | 150000 | 1867079 | 1867079 | 10.5110 ms | 26.1890 ms | Yes | Pass |



## Input Validation Test Results

| Test File | Malformed Condition | Program Output | Exit Code | Status |
|---|---|---|---|---|
| bad_header_missing_E.txt | Header line has only V, missing E | `Input format error: Expected 'V E' on the first line, but couldn't read two integers from it.` | 1 | Correctly rejected |
| bad_vertex_order.txt | Vertices not listed in order 0 to V-1 | `Input format error: vertices must be listed in order 0 to V-1; expected vertex line for a different vertex than the one found.` | 1 | Correctly rejected |
| bad_neighbor_range.txt | A neighbor id is out of range | `Input format error: a neighbor id is out of range (must be between 0 and V-1)` | 1 | Correctly rejected |
| bad_asymmetric_edge.txt | Edge (0,1) listed for vertex 0 but not reciprocated in vertex 1's list | `Error: Invalid input file format - edge (0, 1) is not symmetric: vertex 1's adjacency list does not contain vertex 0, but the graph must be undirected.` | 1 | Correctly rejected |
| bad_weight_mismatch.txt | Edge (0,1) has weight 5, reverse edge (1,0) has weight 9 | `Error: Invalid input file format - edge (0, 1) has weight 5, but the reverse edge (1, 0) has weight 9; both directions of an undirected edge must carry the same weight.` | 1 | Correctly rejected |
| bad_disconnected.txt | Graph has two separate components ({0,1} and {2,3}, no edge between them) | `Error: Invalid input file format - graph is not connected: only 2 of 4 vertices are reachable from vertex 0, but MST requires a connected graph.` | 1 | Correctly rejected |
| (missing file path) | Input file does not exist | `Error: could not open input file '<path>'` | 1 | Correctly rejected |


## Time and Space Complexity

**Kruskal's Algorithm:**
- Time complexity: O(E log E) — dominated by sorting the edge list.

- Space complexity: O(V + E) — the CSR arrays, the extracted edge list
  (O(E)), and the DSU's parent/rank arrays (O(V)).

**Prim's Algorithm:**
- Time complexity: O(E log V) — each of the up to E edge relaxations may
  trigger a heap push/pop, each costing O(log V) with a binary heap of
  size bounded by the number of edges.
- Space complexity: O(V + E) — the CSR arrays, the `key`/`parent`/`inTree`
  arrays (O(V)), and the heap (bounded by O(E) due to the lazy-deletion
  approach pushing more than once per vertex in the worst case).