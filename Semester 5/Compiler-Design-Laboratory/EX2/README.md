# EX2 — Token Recognition and Lex Context

## Aim

Use Lex/Flex to recognize assignment operators, distinguish unary minus from subtraction, scan array declarations, and identify function names using trailing context.

## Files

| Source | Input opened by the program | Purpose |
| --- | --- | --- |
| `assignment.l` | `input.txt` | Recognize identifiers, integer constants, simple assignment, compound assignment, and semicolons. |
| `Unary_MInus.l` | `input.txt` | Use an exclusive `UNARY` state to distinguish unary minus from subtraction. |
| `array.l` | `array_input.txt` | Recognize data types, array names, dimensions, and initializer lists. |
| `function.l` | `func_input.txt` | Recognize an identifier immediately followed by `(` using trailing context. |

## Build and Run

Requires Flex and a C compiler (`cc`, GCC, or Clang). Run from the repository root:

```sh
cd "Semester 5/Compiler-Design-Laboratory/EX2"
mkdir -p build

for name in assignment Unary_MInus array function; do
    flex -o "build/$name.c" "$name.l"
    cc "build/$name.c" -o "build/$name"
done

./build/assignment
./build/Unary_MInus
./build/array
./build/function
```

Each scanner defines `yywrap()`, so `-lfl` is unnecessary. Run the executables from `EX2`: filenames are hard-coded and resolved relative to the current directory, and command-line filenames are not used.

## Sample Results

The supplied `input.txt` contains:

```text
x += 5; y -= 2; z *= 3;
```

The assignment scanner reports the first statement as:

```text
IDENTIFIER : x
COMPOUND OP : +=
INT CONSTANT : 5
PUNCTUATION : ;
```

For the supplied `array_input.txt`:

```text
DATA TYPE : int
ARRAY NAME : marks
DIMENSION : [5]
OPERATOR : =
INITIALIZER LIST: {90, 85, 70, 60, 100}
PUNCTUATION : ;
```

For `func_input.txt`, `display()` produces a `FUNCTION CALL (right context '(' ahead)` label for `display`, while `display;` produces an `IDENTIFIER` label. Parentheses and semicolons are reported separately.

## Unary Minus Example

The shared `input.txt` is an assignment example and does not demonstrate unary minus. To try a suitable expression without changing that file, run the scanner from a temporary directory:

```sh
scanner="$PWD/build/Unary_MInus"
sample_dir=$(mktemp -d)
printf '%s\n' '-a + b - -5' > "$sample_dir/input.txt"
(cd "$sample_dir" && "$scanner")
```

Expected output:

```text
UNARY MINUS
IDENTIFIER : a
OPERATOR : +
IDENTIFIER : b
SUBTRACTION OPERATOR
UNARY MINUS
NUMBER : 5
```

## Notes

- The unary scanner starts expecting an operand and returns to that state after an operator or opening parenthesis. It does not recognize compound assignments as single tokens; the supplied assignment sample can therefore produce echoed `=` characters and `UNKNOWN : ;` messages.
- Function recognition requires `(` immediately after the identifier. `display ()` is labeled as an identifier. This is a lexical pattern, not validation of a function call.
- The array scanner supports `int`, `float`, `char`, and `double`, with empty or numeric dimensions. Initializer matching stops at the first closing brace and does not handle nested lists.
- These scanners demonstrate token matching; they do not validate complete C statements.
