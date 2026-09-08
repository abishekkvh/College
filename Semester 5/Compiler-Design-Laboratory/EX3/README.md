# EX3 — Block Comments and DFA Simulation

## Aim

Recognize complete C-style block comments with Lex/Flex and simulate a deterministic finite automaton (DFA) using a user-supplied transition table.

## Files

| File | Purpose |
| --- | --- |
| `comments.l` | Recognize `/* ... */` comments with an exclusive `COMMENT` state. |
| `input.txt` | Sample containing one complete block comment. |
| `dfa_states.c` | Interactive DFA simulator written in C. |
| `lex.yy.c` | Generated scanner source; regenerate from `comments.l` for the build. |

## Build

Requires Flex and a C compiler (`cc`, GCC, or Clang). From the repository root:

```sh
cd "Semester 5/Compiler-Design-Laboratory/EX3"
mkdir -p build
flex -o build/comments.c comments.l
cc build/comments.c -o build/comments
cc dfa_states.c -o build/dfa_states
```

The scanner supplies `yywrap()`, so `-lfl` is unnecessary. Build output is kept separate from the existing `lex.yy.c`.

## Block Comment Recognition

Always provide an input filename; the program accesses `argv[1]` without checking the argument count.

```sh
./build/comments input.txt
```

Output for the supplied sample:

```text
Valid Comment
```

The scanner enters `COMMENT` when it sees `/*` and prints `Valid Comment` whenever `*/` closes that comment. If the file ends while still inside a comment, it prints `Invalid/Incomplete Comment`. Text outside comments is ignored, and a file with no block comments produces no output.

This demonstration does not recognize `//` comments, nested comments, or string literals, so comment markers inside quoted text are also processed.

## DFA Simulation

```sh
./build/dfa_states
```

Enter the number of states, state labels, starting state, accepting states, alphabet symbols, and transition table when prompted. Table rows follow the entered state order, and columns follow the alphabet order. Each table entry is a destination state label.

For example, this DFA accepts binary strings ending in `1`:

| State | Input `0` | Input `1` | Accepting? |
| --- | --- | --- | --- |
| 0 (start) | 0 | 1 | No |
| 1 | 0 | 1 | Yes |

Enter these values in order:

```text
2
0 1
0
1
1
2
0 1
0 1
0 1
101
100
```

After setup, the program reports:

```text
String "101" Accepted
String "100" Rejected
```

It then continues prompting for strings. Use Ctrl+C to stop; there is no exit command or end-of-file handling.

### Input Constraints

- Use at most 20 states, with state labels from `0` to `19`. Use declared labels for the start, accepting, and destination states.
- Use at most 100 distinct, non-whitespace single-character alphabet symbols.
- Keep each input string to at most 99 characters. The input buffer is fixed-size and the program does not enforce this limit.
- Empty strings and strings containing whitespace cannot be entered with the current input method.
- An unknown symbol produces an invalid-symbol message. A transition of `-1` stops evaluation without printing an acceptance or rejection result; use a complete table for consistent results.
