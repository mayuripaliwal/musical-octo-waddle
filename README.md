# My C++ implementation of the Traverse challenge from Speed Demon 2026

Efficiently computes shortest paths across large directed weighted graphs for multiple source-target queries. Designed to reduce execution time and memory consumption, this implementation brings the reference runtime down from 72.69 seconds to 2.24 seconds while preserving the expected output for every query.

## Overview

In my approach, I used the following:
- **CSR (Compressed Sparse Row)** for compact, cache-friendly graph representation.
- **Dijkstra's algorithm** for shortest-path computation.
- **Multithreading** to process independent queries concurrently.
- **Buffered input parsing** using `fread()`.
- **Lazy distance initialization** to avoid repeatedly resetting large arrays.

## Performance

| Metric | Best measured result |
|---|---:|
| Execution time | 2.240 seconds |
| Memory usage | 128 MB |
| Score | 41.448 points |

Best measured run: [0dd7ba6](https://github.com/mayuripaliwal/musical-octo-waddle/commit/0dd7ba6db2eeb71dc453f8e346d1bbedd7e11cf5)

## Repository structure

- [`track-d/README.md`](track-d/README.md) — Detailed implementation, approach and optimization journey.
- [`track-d/PERF.md`](track-d/PERF.md) — Performance log with leaderboard run IDs.

## Technologies

C++ · Dijkstra · CSR · Multithreading · Buffered I/O

## Competition

[Speed Demon 2026](https://speeddemon.dev/)