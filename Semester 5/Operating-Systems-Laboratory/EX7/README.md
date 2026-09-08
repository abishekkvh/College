# EX7 — Contiguous Memory Allocation

## Aim

Compare First Fit, Best Fit, and Worst Fit placement of processes into available memory holes.

## Program

`continuos_memory_allocation.c` provides three menu choices:

| Choice | Method | Selection rule |
| --- | --- | --- |
| 1 | First Fit | First unused hole large enough for the process. |
| 2 | Best Fit | Smallest unused hole large enough for the process. |
| 3 | Worst Fit | Largest unused hole large enough for the process. |

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX7"
mkdir -p build
cc continuos_memory_allocation.c -o build/memory_allocation
./build/memory_allocation
```

Build outputs are kept in `build/`, separate from existing executables.

## Input and Output

Enter the number of processes, each process size, the number of memory holes, each hole size, and a menu choice. Use 1–20 processes and holes, with positive sizes expressed in the same units. These bounds are not checked by the code.

Example for First Fit:

```text
3
100 200 300
3
150 350 250
1
```

Result:

```text
Process Size Hole
P1      100  H1
P2      200  H2
P3      300  Not Allocated
```

Rerun and select another method to compare:

| Method | P1 (100) | P2 (200) | P3 (300) |
| --- | --- | --- | --- |
| First Fit | H1 | H2 | Not Allocated |
| Best Fit | H1 | H3 | H2 |
| Worst Fit | H2 | H3 | Not Allocated |

## Implementation Notes

Each hole can hold only one process: once selected, the entire hole is marked used. Remaining space is not split into a new hole or reused. The program does not simulate deallocation, coalescing, or compaction. Equal-sized candidates are resolved by their input order, and each execution runs one allocation method.
