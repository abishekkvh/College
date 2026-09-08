# EX3 — Message Queues and Shared Memory

## Aim

Use System V message queues and shared memory to exchange text, files, student records, matrices, and array data between processes.

## Programs

| Location under EX3 | Program |
| --- | --- |
| `Message Queue/Batch1/q1.c` | Producer–consumer word counting using a message queue. |
| `Message Queue/Batch1/q2.c` | Text-file copying through a message queue using parent and child processes. |
| `Message Queue/Batch1/producer.c`, `consumer.c` | Text-file transfer using separate producer and consumer executables. |
| `Message Queue/Batch2/q1.c` | Another copy of the message-queue word-count program. |
| `Message Queue/Batch2/q2.c` | Student grade-sheet generation from a record sent through a message queue. |
| `Shared Memory/Batch 1/producer_consumer_vowels.c` | Extract and print vowels from a shared string. |
| `Shared Memory/Batch 1/matrix_sum_shared_memory.c` | Add two matrices using shared memory. |
| `Shared Memory/Batch 2/producer_consumer_reverse.c` | Print a shared string in reverse. |
| `Shared Memory/Batch 2/process_chain_array_sum.c` | Calculate four array-partition sums in a P1 → P2 → P3 → P4 chain. |

`Message Queue/Batch1/i.txt` is a sample input file. `Shared Memory/Batch 1/script.js` is an unrelated Google Earth Engine flood-analysis script and is not part of the C IPC exercises.

## Build

Use a C compiler on a system supporting System V IPC. From the repository root:

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX3"
for folder in "Message Queue/Batch1" "Message Queue/Batch2" "Shared Memory/Batch 1" "Shared Memory/Batch 2"; do
    mkdir -p "$folder/build"
    for source in "$folder"/*.c; do
        name=$(basename "$source" .c)
        cc "$source" -o "$folder/build/$name"
    done
done
```

## Run the Message-Queue Programs

From `EX3`:

```sh
(cd "Message Queue/Batch1" && ./build/q1)
(cd "Message Queue/Batch1" && ./build/q2)
(cd "Message Queue/Batch2" && ./build/q1)
(cd "Message Queue/Batch2" && ./build/q2)
```

- Word counting: enter `Operating systems lab` to obtain **3** words.
- File copying: enter `i.txt` as the source and a new filename as the destination. The destination is opened for writing and is overwritten if it exists.
- Grade sheet: enter a roll number, a single-word name (under 50 characters), and five marks. Grades are S (90+), A (80–89), B (70–79), C (60–69), D (50–59), and F (below 50). The consumer prints subject grades, total, and average.

For the separate file-transfer pair, open two terminals in `EX3/Message Queue/Batch1`. Run `./build/consumer` in one, supply a new destination filename, then run `./build/producer` in the other and supply `i.txt`. Both must use the same working directory because their queue key comes from `ftok(".", 66)`. The consumer waits for data and removes the queue after completion.

## Run the Shared-Memory Programs

From `EX3`:

```sh
"./Shared Memory/Batch 1/build/producer_consumer_vowels"
"./Shared Memory/Batch 1/build/matrix_sum_shared_memory"
"./Shared Memory/Batch 2/build/producer_consumer_reverse"
"./Shared Memory/Batch 2/build/process_chain_array_sum"
```

| Program | Input example | Result |
| --- | --- | --- |
| Vowel extraction | `Operating Systems` | `Oeaie` |
| Matrix addition | Dimensions `1 2`, first matrix `1 2`, second matrix `3 4` | `4 6` |
| String reversal | `hello` | `olleh` |
| Array partition sums | Count `8`, then `1 2 3 4 5 6 7 8` | P1: 3, P2: 7, P3: 11, P4: 15. |

Matrix dimensions must be between 1 and 10. The array count must be positive, divisible by four, and no greater than 100. The array program prints individual partition sums, not a combined total. String buffers hold 1024 bytes.

## Notes

Shared-memory examples use `wait()` to order access and remove their segments on normal completion. Message-queue examples also remove queues on normal completion; interrupted runs may leave IPC resources behind.

Run queue examples one at a time within a working directory: some reuse the same key. File transfer is line-oriented text transfer with reserved `EOF` and error messages, not a general binary-copy protocol. Most message-queue calls do not check system-call failures.
