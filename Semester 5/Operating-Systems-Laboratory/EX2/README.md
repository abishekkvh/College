# EX2 — Interprocess Communication Using Pipes

## Aim

Exchange data between related processes using unnamed pipes, including request/response communication and a three-process string-processing chain.

## Programs

| File | Program |
| --- | --- |
| `t.c` | Parent sends N; child returns the sum of the first N natural numbers. |
| `two_way_pipe.c` | Two-way request/response: natural-number sum and integer reversal. |
| `p.c` | Intended P1 → P2 → P3 string chain for vowel counting and palindrome checking; contains a descriptor-handling issue. |
| `process_tree.c` | Alternative string-processing chain; contains premature pipe closures. |
| `generate_record.sh` | Helper to compile/run the C files and record a terminal session in `EX2.prn`. |
| `EX2.prn` | Existing lab-session record. |

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX2"
mkdir -p build
for name in t two_way_pipe p process_tree; do
    cc "$name.c" -o "build/$name"
done
./build/t
./build/two_way_pipe
```

Build outputs are kept in `build/`, separate from existing executables.

## Inputs and Results

Requires a POSIX environment such as Linux or macOS.

- For `t`, enter `5`; the child returns **15**.
- For `two_way_pipe`, enter `5` at the parent's prompt and `1234` at the child's prompt. The exchanged answers are **15** and **4321**. Enter values interactively as prompted.
- The string-chain variants accept a line of up to 80 characters. Their intended operations are case-insensitive vowel counting and palindrome checking. For `madam`, the intended results are two vowels and a palindrome.

## Current Limitations

`p.c` closes `pipe2[0]` in P2 before forking P3. P3 inherits that closed descriptor, so its read fails and the palindrome result is not printed.

`process_tree.c` closes the first pipe's read end and both ends of the second pipe before creating children. Its initial write has no reader and can terminate the program with `SIGPIPE`. These variants compile, but their intended string-processing results are not reliable as written.

`generate_record.sh` uses macOS/BSD-style `script` and `sed` commands, requires Bash and Python 3, overwrites `EX2.prn`, and removes `a.out` after running. Its recorded run is also affected by the source issues above.
