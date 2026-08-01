# Assignment 01

**Title:** Matrix Multiplication (GEMM — General Matrix Multiplication)

**Type:** Single

**Objective:** 

## Explanation of the Algorithm / Approach

**GEMM Simple**

This is the standard triple nested loop matrix multiplication. For a result matrix C (M x N), computed from A (M x K) and B (K x N). Each element of C is computed independently as a dot product of a row of A and a column of B.

**GEMM Blocking**

This version splits the matrices into smaller square blocks (tiles) of a fixed size (`BLOCK_SIZE`), and multiplies block-by-block instead of element-by-element across the whole matrix at once

## Input Format, Assumptions, and Constraints

Each test file follows this format:
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

**Assumptions:**
- All matrix values are integers.
- The input file is well-formed (correct number of values per the stated
  dimensions) — no validation is done for malformed input beyond the
  dimension compatibility check.

**Constraints:**
- `BLOCK_SIZE` for the blocking implementation is fixed at compile time (currently 32) — it isn't read from input.

  ## Source Files, Driver Files, Helper Functions, and Test Files

**`src/matrix.c` / `matrix.h`** — the core logic:
- `allocateMatrixSpace(rows, cols)` — allocates a 2D integer matrix.
- `freeMatrixSpace(matrixFile, rows)` — frees a previously allocated matrix.
- `getDimensions(matrixFile, &rowsA, &colsA, &colsB)` — reads the `M K N` header line.
- `readMatrixFromFile(matrixFile, rows, cols)` — reads one matrix's values from the file, given its dimensions.
- `printMatrix(matrixFile, rows, cols)` — prints a matrix to stdout.
- `multiplyMatricesSimple(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB)` — the simple triple-loop multiplication.

**`driver/driver.c`** — contains `main()`. Reads the test file and method argument, calls the appropriate multiplication function from `matrix.c`, times the execution, and prints the result.

**`../common_wrapper/wrapper.c`** (shared across all assignments):
- `openFile(filename)` — opens the input file, exits with an error if it can't be opened.
- `getExecutionTime()` — returns the current time, used to measure how long multiplication takes.
- `printExecutionTime(start, end)` — prints the elapsed time in seconds.

**`tests/`** — contains input files following the format describe above. Each file has both matrices A and B, sized to test different scenarios (square matrices, non-square matrices, etc.)

## Compilation and Execution Instructions

From inside `assignment_01/`:

**Compile:**
```bash
make
```

**Run (simple method):**
```bash
./run tests/test_01.txt simple
```

**Run (blocking method):**
```bash
./run tests/test_01.txt blocking
```

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

## Time and Space Complexity

**Simple GEMM:**
- Time complexity: O(M × K × N) — three nested loops, each element of C
  requires K multiply-add operations.
- Space complexity: O(M×K + K×N + M×N) for storing A, B, and C.

**Blocking GEMM:**
- Time complexity: same asymptotic complexity, O(M × K × N) — blocking
  doesn't reduce the number of operations, only changes the memory access
  pattern to improve cache utilization.
- Space complexity: same as the simple version, O(M×K + K×N + M×N) — no
  extra data structures are allocated, just an additional fixed-size
  `BLOCK_SIZE` constant controlling loop tiling.