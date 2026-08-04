# Assignment 01

**Title:** Matrix Multiplication (GEMM — General Matrix Multiplication)

**Type:** Single

**Objective:** 

## Explanation of the Algorithm / Approach

**GEMM Simple**

This is the standard triple nested loop matrix multiplication. For a result matrix C (M x N), computed from A (M x K) and B (K x N). Each element of C is computed independently as a dot product of a row of A and a column of B.

**GEMM Blocking**

This version splits the matrices into smaller square blocks (tiles) of a fixed size (`BLOCK_SIZE`), and multiplies block-by-block instead of element-by-element across the whole matrix at once.

**CSR Graph Conversion**
 
Compressed Sparse Row (CSR) is a compact way to store a graph's adjacency information using three flat arrays : `rowPtr`, `colIndex`, and `edgeWeights`, instead of a full adjacency matrix. `rowPtr` marks where each vertex's neighbors start and end in `colIndex`, `colIndex` stores the actual neighbor list, and `edgeWeights` stores edge weights when the graph is weighted.

## Input Format, Assumptions, and Constraints

**GEMM** — Each test file follows this format:
```
M K N
A row 0 values
A row 1 values
...
A row M-1 values
B row 0 values
B row 1 values
...
B row K-1 values
```
- A is `M x K`, B is `K x N`, result C is `M x N`.
- Each row is on its own line, values space-separated.
- Both matrices are read from the **same** file, one after the other —
  A's rows first, then B's rows.

**CSR** — Each test file follows this format:
```
V E
u0 degree neighbor1 [weight1] neighbor2 [weight2] ...
u1 degree neighbor1 [weight1] neighbor2 [weight2] ...
...
u(V-1) degree neighbor1 [weight1] neighbor2 [weight2] ...
SOURCE s
```
- `V` is the number of vertices, `E` the number of unique edges.
- Each vertex's line lists its ID, degree, and that many neighbors.
- Weighted graphs list each neighbor followed by its edge weight; unweighted graphs list only neighbor IDs.
- A vertex with no neighbors is written as `u 0`.


**Assumptions:**
- All matrix values are integers.
- The input file is well-formed (correct number of values per the stated
  dimensions) — no validation is done for malformed input beyond the
  dimension compatibility check.
- Graph vertices are listed in order (0 to V-1) in the input file.


**Constraints:**
- `BLOCK_SIZE` for the blocking implementation is fixed at compile time (currently 32) — it isn't read from input.
- `colIndex` and `edgeWeights` are sized at `2 x E`, since each undirected edge is listed once per endpoint.

  ## Source Files, Driver Files, Helper Functions, and Test Files

**`src/matrix.c` / `matrix.h`** — the core logic:
- `allocateMatrixSpace(rows, cols)` — allocates a 2D integer matrix.
- `freeMatrixSpace(matrixFile, rows)` — frees a previously allocated matrix.
- `getDimensions(matrixFile, &rowsA, &colsA, &colsB)` — reads the `M K N` header line.
- `readMatrixFromFile(matrixFile, rows, cols)` — reads one matrix's values from the file, given its dimensions.
- `printMatrix(matrixFile, rows, cols)` — prints a matrix to stdout.
- `multiplyMatricesSimple(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB)` — the simple triple-loop multiplication.

**`src/graph.c` / `graph.h`** — the CSR conversion logic:
- `readAdjacencyListAsCSR(graphFile, isWeighted)` — reads the adjacency list and builds `rowPtr`, `colIndex`, and (if weighted) `edgeWeights` in a single pass. ; exits with a descriptive error on any malformed input.
- `printCSRGraph(graph)` — prints the resulting CSR arrays.
- `freeCSRGraph(graph)` — frees all memory associated with a CSR graph.

**`driver/driver.c`** — contains `main()`. Reads the input file and method argument, and dispatches to the GEMM or CSR runner accordingly, timing execution and printing the result.

**`../common_wrapper/wrapper.c`** (shared across all assignments):
- `openFile(filename)` — opens the input file, exits with an error if it can't be opened.
- `getExecutionTime()` — returns the current time, used to measure how long multiplication takes.
- `printExecutionTime(start, end)` — prints the elapsed time in seconds.

**`tests/`** — contains input files following the format describe above. Each file has both matrices A and B, sized to test different scenarios (square matrices, non-square matrices, etc.). Graph test files contain adjacency lists at various sizes.

## Compilation and Execution Instructions

From inside `assignment_01/`:

**Compile:**
```bash
make
``` 
**Run (GEMM simple):**
```bash
./run tests/test_01.txt simple
```

**Run (GEMM blocking):**
```bash
./run tests/test_01.txt blocking
```
 
**Run (CSR Conversion):**
```bash
./run tests/csr_test_01.txt csr 0
```
Use `0` for unweighted graph files, `1` for weighted graph files.
 

## GEMM Results Table

| Test File | Input Type / Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|---|---|---|---|---|---|---|---|
| test_01.txt | 3x3 and 3x3 | Result matrix | Result matrix | 0.0020 ms | 0.0030 ms | 32 | Pass |
| test_02.txt | 1x3 and 4x1 | Result matrix | Result matrix | 0.0050 ms | 0.0030 ms | 32 | Pass |
| test_03.txt | 3x3 and 3x3 (Identity B) | Result matrix = A | Result matrix | 0.0030 ms | 0.0040 ms | 32 | Pass |
| test_04.txt | 2x2 and 2x2 (Zero B) | Result matrix = 0 | Result matrix | 0.0030 ms | 0.0040 ms | 32 | Pass |
| test_05.txt | 12x17 and 17x23 | Result matrix | Result matrix | 0.0240 ms | 0.0310 ms | 32 | Pass |
| test_06.txt | 40x60 and 60x30 | Result matrix | Result matrix | 0.2830 ms | 0.1550 ms | 32 | Pass |
| test_07.txt | 50x50 and 50x50 | Result matrix | Result matrix | 0.4840 ms | 0.2180 ms | 32 | Pass |
| test_08.txt | 100x100 and 100x100 | Result matrix | Result matrix | 3.5680 ms | 3.0530 ms | 32 | Pass |
| test_09.txt | 300x300 and 300x300 | Result matrix | Result matrix | 72.2060 ms | 51.9220 ms | 32 | Pass |
| test_10.txt | 800x1000 and 1000x600 | Result matrix | Result matrix | 1146.3760 ms | 766.9800 ms | 32 | Pass |

## CSR Conversion Results Table

| Test File | Vertices (V) | Edges (E) | Input Type | Execution Time | Status |
|---|---|---|---|---|---|
| csr_test_01.txt | 10 | 30 | Unweighted | 0.1170 ms | Pass |
| csr_test_02.txt | 100 | 300 | Unweighted | 0.1480 ms | Pass |
| csr_test_03.txt | 10000 | 30000 | Unweighted | 7.1680 ms | Pass |
| csr_test_04.txt | 50000 | 150000 | Unweighted | 29.5620 ms | Pass |
| csr_test_05.txt | 100000 | 300000 | Unweighted | 60.5950  ms | Pass |
| csr_test_06.txt | 10000 | 300000 | Weighted | 14.1590 ms | Pass |
| csr_test_07.txt | 50000 | 150000 | Weighted | 49.5950 ms | Pass |

## Time and Space Complexity

**Simple GEMM:**
- Time complexity: O(M × K × N) — three nested loops, each element of C
  requires K multiply-add operations.
- Space complexity: O(M×K + K×N + M×N) for storing A, B, and C.

**Blocking GEMM:**
- Time complexity: same asymptotic complexity, O(M × K × N) — blocking doesn't reduce the number of operations, only changes the memory access pattern to improve cache utilization.
- Space complexity: same as the simple version, O(M×K + K×N + M×N) — no extra data structures are allocated, just an additional fixed-size `BLOCK_SIZE` constant controlling loop tiling.