
# Course Code : CS509 

## About this repository

This repository contains my submissions for CS509 assignments. Each assignment lives in its own folder and includes the source code, a driver program to run it and sample test cases. A common wrapper is shared across all assignments to handle repetitive setup like timing and I/O formatting, so each assignment folder only needs to focus on the actual logic.

## Student Details

- **Name:** Niharika Girdhar
- **Entry Number:** 2026CSM1015

## Language, compiler, and tools

- **Language:** C 
- **Compiler:** gcc 
- **Build tool:** Make 
- **OS tested on:** macOS 

## Repository structure
```
CS509_CSM1015/
├── README.md
├── common_wrapper/
│ └── wrapper.c
│ └── wrapper.h
├── Assignment_01/
│ ├── makefile
│ ├── src/ 
│ ├── driver/ 
│ ├── tests/ 
│ └── readme.md 
├── assignment_02/
```
- **`src/`** contains the actual implementation for that assignment.
- **`driver/`** contains the program that invokes the code in `src/` and runs it against the test cases.
- **`tests/`** contains individual test input files, numbered sequentially.
- **`outputs/`** (when present) contains the expected or generated output for each corresponding test file.

## Common wrapper

The `common_wrapper/` folder contains a single wrapper file (`wrapper.c`) that is reused by every assignment. It's meant to keep repetitive boilerplate — like reading test files, timing execution, and printing results in a consistent format — out of the assignment code itself.

## How to run the code

Each assignment folder has its own `makefile`, so building and running is done **from inside that assignment's folder**, not from the repo root.

At a high level, the general pattern across all assignments is:

```bash
cd assignment_XX
make
./run <arguments specific to that assignment>
```
 
For the exact command, arguments, and expected output for a specific assignment, refer to that assignment's own `readme.md` (e.g.`assignment_01/readme.md`). It documents the precise input format, the exact compilation and execution steps, sample test cases, and expected output for that assignment.

To run a different assignment, just `cd` into that assignment's folder and repeat the same steps, each one builds and runs independently.

## Conventions followed

- **Test files** are named `test_01.txt`, `test_02.txt`, etc., numbered in the order they should be run.
- **Runtime measurement** is done inside the common wrapper so that timing is consistent across all assignments — each driver just calls the wrapper's timing function around the actual logic rather than implementing its own.
- Each assignment has its own `readme.md` with any notes specific to that assignment (assumptions made, edge cases handled, how to run it, etc.). This top-level README only covers repo-wide information.