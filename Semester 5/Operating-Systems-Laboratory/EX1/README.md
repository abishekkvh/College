# EX1 — Process Creation and Hierarchies

## Aim

Create parent, child, and grandchild processes using `fork()`, display their process IDs, and coordinate completion with `wait()`.

## Programs

| File | Program |
| --- | --- |
| `LinearHierarchy.c` | Linear process hierarchy: P1 → P2 → P3. |
| `TreeHierarchy1.c` | Two children calculate even and odd array sums; the parent calculates the total. |
| `TreeHierarchy2.c` | Seven-process tree with multiple generations. |
| `p.c` | Three consecutive `fork()` calls, producing eight processes when all forks succeed. |
| `Tree.txt` | Notes and a process-tree sketch for consecutive forks. |

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX1"
mkdir -p build
for name in LinearHierarchy TreeHierarchy1 TreeHierarchy2 p; do
    cc "$name.c" -o "build/$name"
done
./build/LinearHierarchy
./build/TreeHierarchy1
./build/TreeHierarchy2
./build/p
```

Build outputs are kept in `build/`, separate from existing executables.

## Behavior

No keyboard input is required. A POSIX environment such as Linux or macOS is needed for process system calls.

- `LinearHierarchy` prints P3, then P2, then P1 because each ancestor waits for its child.
- `TreeHierarchy1` uses `{1, 2, 3, 4, 5, 6}`: even sum = **12**, odd sum = **9**, total = **21**.
- `TreeHierarchy2` creates the following hierarchy:

```text
P1
├── P2
│   └── P4
│       └── P6
└── P3
    ├── P5
    └── P7
```

- `p` prints `Hello` eight times if every fork succeeds.

Process IDs change on every run. Scheduling can change the order of output from sibling processes. The sketch in `Tree.txt` omits one of the eight processes created by its three-fork snippet.
