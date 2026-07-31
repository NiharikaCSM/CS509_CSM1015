
# Course Code : CS509 

## About this repository

This repository contains my submissions for CS509 assignments. Each assignment lives in its own folder and includes the source code, a driver program to run it, sample test cases, and (optionally) expected outputs. A common wrapper is shared across all assignments to handle repetitive setup like timing and I/O formatting, so each assignment folder only needs to focus on the actual logic.

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
├── assignment_01/
│ ├── src/ 
│ ├── driver/ 
│ ├── tests/ 
│ ├── outputs/
│ └── readme.md 
├── assignment_02/
```
- **`src/`** contains the actual implementation for that assignment.
- **`driver/`** contains the program that invokes the code in `src/` and runs it against the test cases.
- **`tests/`** contains individual test input files, numbered sequentially.
- **`outputs/`** (when present) contains the expected or generated output for each corresponding test file.

## Common wrapper

The `common_wrapper/` folder contains a single wrapper file (`wrapper.c`) that is reused by every assignment. It's meant to keep repetitive boilerplate — like reading test files, timing execution, and printing results in a consistent format — out of the assignment code itself.

## Conventions followed

- **Test files** are named `test_01.txt`, `test_02.txt`, etc., numbered in the order they should be run.
- **Runtime measurement** is done inside the common wrapper so that timing is consistent across all assignments — each driver just calls the wrapper's timing function around the actual logic rather than implementing its own.
- Each assignment has its own `readme.md` with any notes specific to that assignment (assumptions made, edge cases handled, how to run it, etc.). This top-level README only covers repo-wide information.