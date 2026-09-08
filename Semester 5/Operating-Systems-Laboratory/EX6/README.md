# EX6 — Banker’s Algorithm

## Aim

Avoid unsafe resource allocation by calculating remaining needs, finding a safe sequence, and evaluating one additional resource request.

## Program

`bankersAlgorithm.c` implements the safety algorithm and resource-request algorithm. It computes `Need = Maximum − Allocation`, simulates process completion, and tentatively grants a request only when the resulting state is safe. An unsafe tentative allocation is rolled back.

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX6"
mkdir -p build
cc bankersAlgorithm.c -o build/bankers
./build/bankers
```

Build outputs are kept in `build/`, separate from existing executables.

## Input Order

1. Number of processes and number of resource types.
2. Available resource vector.
3. Maximum matrix, one row per process.
4. Allocation matrix, one row per process.
5. If the initial state is safe, the requesting process number and its request vector.

Processes use zero-based labels: P0 through P(n−1). Use 1–10 processes and 1–10 resource types, nonnegative values, allocation no greater than maximum, and a valid requesting process index. The source does not validate all these constraints.

## Example

Two processes each hold one instance and may need two; one instance is available. P0 requests one more:

```text
2
1
1
2
2
1
1
0
1
```

The need matrix contains `1` for each process. The initial and post-request safe sequence is **P0 → P1**, and the program prints:

```text
Request can be GRANTED to P0.
```

## Possible Results

The program reports an unsafe initial state, a request exceeding the maximum claim, unavailable resources, a granted safe request, or a request that must wait because it would make the state unsafe. An unsafe state means that completion cannot be guaranteed under the maximum claims; it does not by itself establish a current deadlock.
