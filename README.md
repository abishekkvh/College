# College | Computer Science in Practice

Algorithms, operating systems, computer networks, and compiler fundamentals—implemented through semester-wise laboratory work.

This repository documents my progression from standalone C++ algorithms to C programs that manage processes, coordinate concurrent clients, communicate over sockets, and recognize language tokens. It brings together foundational exercises and larger networking applications, with source code and exercise-level documentation for deeper exploration.

**Core stack:** C · C++ · Java · Lex/Flex · POSIX sockets · Pthreads · Make · Python integration tests

## Start Here

These examples offer a focused introduction to the work and the engineering questions behind it.

| Highlight | Implementation | What to explore |
| --- | --- | --- |
| **Concurrent network services** | [Examination, hotel booking, file sharing, and chat](Semester%205/Computer-Networks-Laboratory/EX7/Self-Questions/) | Shared socket utilities, threaded client handling, protocol validation, and integration tests. |
| **Persistent hotel reservations** | [Hotel server](Semester%205/Computer-Networks-Laboratory/EX7/Self-Questions/Hotel/server.c) | Mutex-protected bookings, reservation tokens, and a journal committed before in-memory state changes. |
| **Reliable data transmission** | [Stop-and-Wait and Go-Back-N](Semester%205/Computer-Networks-Laboratory/EX8/README.md) | UDP acknowledgements and retries, duplicate suppression, and a deterministic sliding-window simulation. |
| **CPU scheduling comparisons** | [Scheduling laboratory](Semester%205/Operating-Systems-Laboratory/EX4/README.md) | Five scheduling strategies, with completion, waiting, and turnaround times for comparison. |
| **Algorithmic problem solving** | [Algorithm laboratory](Semester%204/Design%20%26%20Analysis%20of%20Algorithm%20Laboratory/) | Divide and conquer, greedy methods, dynamic programming, backtracking, and branch and bound. |
| **Lexical analysis and automata** | [Comment recognition and DFA simulation](Semester%205/Compiler-Design-Laboratory/EX3/README.md) | Scanner states, transition tables, and string acceptance. |

## Repository Map

```text
College/
├── Semester 4/
│   └── Design & Analysis of Algorithm Laboratory/   # EX1–EX9
└── Semester 5/
    ├── Operating-Systems-Laboratory/                # EX1–EX7
    ├── Computer-Networks-Laboratory/                # EX0–EX8
    └── Compiler-Design-Laboratory/                  # EX1–EX3
```

Each laboratory is organized by exercise. Several exercises include their own README with build instructions, sample inputs, expected output, and implementation constraints.

## Coursework Coverage

| Area | Topics implemented |
| --- | --- |
| [Design & Analysis of Algorithms](Semester%204/Design%20%26%20Analysis%20of%20Algorithm%20Laboratory/) | Bubble, selection, insertion, merge, quick, and heap sort; closest pair; brute-force pattern matching; Horspool; Floyd–Warshall; Huffman coding; N-Queens; branch-and-bound knapsack. |
| [Operating Systems](Semester%205/Operating-Systems-Laboratory/) | Process hierarchies, pipes, shared memory, message queues, producer–consumer coordination, CPU scheduling, Banker's algorithm, and First/Best/Worst Fit memory allocation. |
| [Computer Networks](Semester%205/Computer-Networks-Laboratory/) | Framing, CRC, parity, Hamming codes, Bellman–Ford, TCP/UDP sockets, DNS/DHCP/ARP demonstrations, file transfer, chat, and reliable transmission protocols. Includes C++, Java, and C problem-solving exercises. |
| [Compiler Design](Semester%205/Compiler-Design-Laboratory/) | Lex/Flex text processing, token recognition, assignment operators, unary minus, array declarations, function-name recognition, block comments, and DFA simulation. |

## Run a Demonstration

Use a C/C++ compiler such as GCC or Clang. The networking and operating-system exercises use POSIX APIs; Linux or WSL is a practical starting environment, while platform support varies by exercise. Lexical scanners additionally require Flex. The network service test suite requires Make and Python 3.

Run each example below from the repository root. Build locally from source rather than relying on existing executables.

### Compare CPU scheduling strategies

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX4"
mkdir -p build
cc main.c scheduling_algorithms.c -o build/scheduling
./build/scheduling
```

Enter process arrival and burst times, then compare FCFS, SJF, SRTF, priority scheduling, and Round Robin. The [exercise guide](Semester%205/Operating-Systems-Laboratory/EX4/README.md) includes a reproducible example and explains implementation details that affect the results.

### Observe recovery from a lost frame

```sh
cd "Semester 5/Computer-Networks-Laboratory/EX8"
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic Go-Back-N/go_back_n.c -o build/go_back_n
printf '4\n10\n3\n1\n' | ./build/go_back_n
```

This simulates a window of four frames, ten total frames, and the loss of frame three. Follow the output to see acknowledgements and retransmissions. For a two-process UDP example, follow the [Stop-and-Wait instructions](Semester%205/Computer-Networks-Laboratory/EX8/README.md).

### Run the network service integration tests

```sh
cd "Semester 5/Computer-Networks-Laboratory/EX7/Self-Questions"
make check
```

The [Python test suite](Semester%205/Computer-Networks-Laboratory/EX7/Self-Questions/tests/check_systems.py) builds the services in a temporary directory and exercises:

- Examination authentication, evaluation, concurrent sessions, and disconnect handling.
- Competing hotel bookings, cancellation, persistence across restarts, and journal corruption.
- Parallel file transfers, binary and empty files, access checks, and truncated-download cleanup.
- Concurrent chat broadcasts, malformed or fragmented requests, and terminal clients.

These checks cover the EX7 services; other exercises have their own sample runs and validation guidance where documented.

## Engineering Discussion Points

The code provides concrete starting points for technical conversations:

- **Concurrency and persistence:** How does the hotel server prevent two clients from booking the same room, and when does it commit a reservation to disk?
- **Stream protocols:** How do shared networking helpers handle partial sends, fragmented requests, and malformed input?
- **Reliability and throughput:** What changes when a sender allows multiple outstanding frames instead of waiting for every acknowledgement?
- **Scheduling trade-offs:** How do arrival times, preemption, priorities, and time quantum affect waiting and turnaround times?
- **Algorithm selection:** How do problem structure and input size influence the choice between exhaustive search, greedy methods, and backtracking?

## Scope

This is an academic programming portfolio. Exercises range from compact concept demonstrations to more structured applications with shared utilities and automated tests. Some programs use fixed-size inputs or simplified protocol models; the individual exercise guides document those constraints where available. The repository is organized for studying implementations, reproducing experiments, and discussing design decisions.
