# Assignment 02

**Title:** Single-Source and All-Pairs Shortest Paths (Bellman-Ford and Floyd-Warshall)

**Type:** Individual

**Objective:** Implement Bellman-Ford (single-source shortest path, tolerant
of negative edge weights) and Floyd-Warshall (all-pairs shortest path) on a
CSR (Compressed Sparse Row) graph representation, measure the execution
time of each algorithm and detect and report negative-weight cycles where the algorithm's own procedure calls for it. The adjacency-list-to-CSR conversion is not reimplemented here — it is called directly from `assignment_01/src/graph.c`.