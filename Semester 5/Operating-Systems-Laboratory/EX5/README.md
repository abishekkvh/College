# EX5 — Producer–Consumer Synchronization Using Semaphores

## Aim

Synchronize a producer and consumer sharing a bounded circular buffer using System V shared memory and semaphores.

## Files

| File | Purpose |
| --- | --- |
| `producer.c` | Create shared resources and write the ten characters A through J. |
| `consumer.c` | Read ten characters, print their ASCII values, and remove the IPC resources. |
| `header.h` | Shared buffer structure, semaphore indexes, and wait/signal helpers. |

The buffer has five slots. `MUTEX` protects access, `EMPTY` counts free slots, and `FULL` counts available items. Initial values are 1, 5, and 0 respectively.

## Build and Run

From the repository root, using a C compiler (`cc`, GCC, or Clang):

```sh
cd "Semester 5/Operating-Systems-Laboratory/EX5"
mkdir -p build
cc producer.c -o build/producer
cc consumer.c -o build/consumer
```

Build outputs are kept in `build/`, separate from existing executables.

## Run

Use two terminals with the same `EX5` working directory. Start the producer first:

```sh
./build/producer
```

Wait until it prints `Producer started...`, then run in the second terminal:

```sh
./build/consumer
```

No keyboard input is needed. The producer fills the five-slot buffer and waits until the consumer frees space. The consumer prints characters A–J with ASCII values 65–74, then deletes the shared memory and semaphore set.

Both programs derive keys from the current directory using `ftok()`. Starting the consumer before resource creation fails; running multiple producer instances in the same directory can reinitialize shared state.

## Platform Note

Use a Linux environment with System V IPC and a C library where the application defines `union semun`. On the inspected macOS SDK, both builds fail because `header.h` defines `union semun` and the system header already defines it. A conditional definition is needed for macOS portability; the source has not been changed here.

Interrupted runs may leave shared memory or semaphores behind because normal cleanup is performed by the consumer.
