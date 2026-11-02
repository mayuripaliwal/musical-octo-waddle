# Track D: performance log

Every step from the reference to your final version, each with the live-board run ID that measured it. Judges check that the run IDs exist and that each change moved the way you say it did.

| Step | Change | Run ID | T (s) | M (MB) | Points |
|---:|---|---|---:|---:|---:|
| 0 | Reference, unchanged | — | 72.69 | 893 | 0 |
| 1 | Initial single-threaded Dijkstra using adjacency lists and ifstream | c403b96 | 10.5 | 205 | 19.433 |
| 2 | Use uint32_t for edge weights instead of long long | 27eac14 | 10.3 | 157 | 20.774 |
| 3 | Skip self-loops, duplicate edges and heavier parallel edges | 18be72a | 10.8 | 267 | 17.867 |
| 4 | Fix adjacency-list deduplication | 14b3077 | 10.5 | 267 | 18.147 |
| 5 | Remove timestamping (seenBy) | 7847e28 | 9.895 | 150 | 21.453 |
| 6 | Introduce CSR | 8d3aefb | 10.7 | 83 | 23.028 |
| 7 | Reduce lines of code | 7ff8ea1 | 10.7 | 83 | 23.078 |
| 8 | Add timestamping again | f4e87d9 | 8.601 | 90 | 29.958 |
| 9 | Move priority queue outside function | 5105cb5 | 8.352 | 90 | 30.220 |
| 10 | Use bool for indegree; preallocate 2,000 queries | a6089da | 9.002 | 83 | 29.690 |
| 11 | Introduce multithreading | 9616447 | 5.703 | 105 | 33.314 |
| 12 | Increase thread count to 4 | 2924f49 | 3.893 | 147 | 35.973 |
| 13 | Increase thread count to 6 | 892c975 | 3.293 | 190 | 36.687 |
| 14 | Increase thread count to 8 | a9d8e86 | 3.204 | 233 | 36.106 |
| 15 | Further thread-count experiment (8) | f0f0c00 | 3.240 | 233 | 35.986 |
| 16 | Use uint16_t for seenBy | 2a0721d | 3.788 | 133 | 36.703 |
| 17 | Enable pthread compilation flag | d06cbf9 | 3.879 | 134 | 36.444 |
| 18 | Change thread count to 12 | 6909860 | 2.883 | 276 | 36.508 |
| 19 | Use -march=native and flat edge arrays | 0f9b0fb | 3.191 | 276 | 35.287 |
| 20 | Free temporary edge memory using swap; return to 4 threads | 09e0e2b | 3.099 | 126 | 39.094 |
| 21 | Reuse and clear priority queue | 0fab7ea | 3.566 | 127 | 37.463 |
| 22 | Introduce buffered file reading | 0dd7ba6 | 2.240 | 128 | 41.448 |
| 23 | Read graph and queries concurrently | e0794eb | 2.558 | 128 | 39.969 |
| 24 | Increase input buffer to 2 MiB | 56cbb0a | 2.328 | 131 | 40.940 |
| 25 | Remove chrono timing line | 630c402 | 2.444 | 128 | 40.524 |
| 26 | Use hash map to remove invalid edges | 47a285b | 10.5 | 448 | 19.140 |
| 27 | Remove indegree array | 3a75aca | 3.166 | 128 | 37.790 |
| 28 | Add indegree array | 0926445 | 2.317 | 128 | 41.103 |
