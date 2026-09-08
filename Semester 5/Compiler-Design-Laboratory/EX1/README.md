# EX1 — Basic Lex Programs

## Aim

Use Lex/Flex regular expressions to count text, transform matched patterns, and recognize tokens in a C-like program.

## Files

| Source | Sample input | Purpose |
| --- | --- | --- |
| `file.l` | Any text file | Count newline characters, whitespace-separated words, and total characters. |
| `numbers.l` | `numbers.txt` | Add 1 to integers and 0.5 to decimal numbers; print decimals to two places. |
| `pattern.l` | `pattern.txt` | Capitalize the first letter of every five-letter alphabetic word. |
| `spaces.l` | `spaces.txt` | Replace each run of spaces or tabs with one space, preserving newlines. |
| `programs.l` | `programs.txt` | Recognize keywords, identifiers, numbers, operators, and punctuation. |
| `lex.yy.c` | — | Generated scanner source; regenerate from the desired `.l` file before compiling. |

## Build and Run

Requires Flex and a C compiler (`cc`, GCC, or Clang). From the repository root:

```sh
cd "Semester 5/Compiler-Design-Laboratory/EX1"
mkdir -p build

for name in file numbers pattern spaces programs; do
    flex -o "build/$name.c" "$name.l"
    cc "build/$name.c" -o "build/$name"
done

./build/file programs.txt
./build/numbers numbers.txt
./build/pattern pattern.txt
./build/spaces spaces.txt
./build/programs programs.txt
```

Each scanner defines `yywrap()`, so these commands do not require `-lfl`. Generated files go into `build/` to preserve the existing `lex.yy.c`.

Except for `numbers`, the programs also accept standard input when no filename is supplied. Finish interactive input with Ctrl+D on an empty line. `numbers` requires a filename to perform scanning.

## Sample Results

For `numbers.txt`:

```text
Integers : 11
Floating-Numbers : 22.00
Integers : 101
Floating-Numbers : 16.00
```

For `pattern.txt`:

```text
Apple Mango Hello cat Tiger World Books pen Table House
```

For `spaces.txt`:

```text
Hello World
This is Lex
```

The program tokenizer emits keywords as `<kw,void>`, identifiers as `<id,main>`, operators as `<op,=>`, integers as `10i`, and decimal numbers as `10.3f`.

## Notes

- `file.l` counts newline characters as lines; a final line without a newline is not included in that count. Its character count includes whitespace and counts bytes rather than Unicode characters.
- Number patterns recognize unsigned digit sequences and decimals containing digits on both sides of the decimal point. Signs and exponent notation are not part of a numeric token.
- `programs.l` is a basic lexical demonstration, without full handling of C strings, comments, or syntax validation.
