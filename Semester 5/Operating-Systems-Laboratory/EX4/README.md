# EX4 — CPU Scheduling Algorithms

## Aim

Compare CPU scheduling algorithms using completion time, waiting time, turnaround time, and their averages.

## Programs and Files

| Menu option | Algorithm |
| --- | --- |
| 1 | First Come First Served (FCFS). |
| 2 | Shortest Job First (SJF), non-preemptive. |
| 3 | Shortest Remaining Time First (SRTF), preemptive SJF. |
| 4 | Non-preemptive priority scheduling; lower numbers mean higher priority. |
| 5 | Round Robin with a user-supplied time quantum. |
| 0 | Exit. |

`main.c` handles input and the menu, `scheduling_algorithms.c` implements the algorithms, and `scheduling.h` declares shared data and functions.

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX4"
mkdir -p build
cc main.c scheduling_algorithms.c -o build/scheduling
./build/scheduling
```

Build outputs are kept in `build/`, separate from existing executables.

## Input and Output

Enter the process count, then arrival time and burst time for each process. Select an algorithm; priority scheduling asks for each priority, and Round Robin asks for a time quantum. The menu allows repeated comparisons with the same process data.

For an FCFS example, enter:

```text
3
0 5
1 3
2 1
1
0
```

Expected FCFS results:

| Process | Completion | Waiting | Turnaround |
| --- | --- | --- | --- |
| P1 | 5 | 0 | 5 |
| P2 | 8 | 4 | 7 |
| P3 | 9 | 6 | 7 |

Average waiting time is **3.33** and average turnaround time is **6.33**.

`Turnaround = Completion − Arrival`; `Waiting = Turnaround − Burst`.

## Implementation Notes

Use 1–100 processes, nonnegative arrival times, positive burst times, and a positive Round Robin quantum; these constraints are not validated by the program.

SRTF and idle-time advancement use 0.01 time steps, so floating-point rounding can affect results. The Round Robin implementation scans ready processes in input order on each sweep rather than maintaining an explicit arrival-ordered ready queue.
