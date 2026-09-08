# C Network Programming Utilities

A collection of C network programming applications demonstrating **TCP socket programming**, **client-server communication**, **multi-process concurrency using `fork()`**, **multi-threaded concurrency using POSIX threads (`pthread`)**, and **synchronization using mutexes**.

The repository contains three main networking modules:

* File Transfer System
* Simulated ARP Lookup System
* Interactive TCP Chat System

---

## Module Overview

| File                 | Role                       | Concurrency Model          | Main Technologies / System Calls                      |
| -------------------- | -------------------------- | -------------------------- | ----------------------------------------------------- |
| `ser_file.c`         | File Transfer Server       | Multi-Process (`fork`)     | TCP sockets, `fopen`, `recv`, `waitpid`               |
| `cli_file.c`         | File Transfer Client       | Single-Threaded            | TCP sockets, `fopen`, `send`, `basename`              |
| `ser_arp.c`          | ARP Lookup Server          | Multi-Threaded (`pthread`) | TCP, hash table, `pthread_mutex`, `popen("arp -a")`   |
| `received_ser_arp.c` | ARP Server - Linux Variant | Multi-Threaded (`pthread`) | TCP, hash table, `pthread_mutex`, `popen("ip neigh")` |
| `cli_arp.c`          | ARP Lookup Client          | Single-Threaded            | TCP sockets, `inet_pton`, `send`, `recv`              |
| `ser_chat.c`         | TCP Chat Server            | Multi-Process (`fork`)     | TCP sockets, `fgets`, `send`, `recv`                  |
| `cli_chat.c`         | TCP Chat Client            | Single-Threaded            | TCP sockets, `fgets`, `send`, `recv`                  |

---

# 1. File Transfer System

### Files

* `ser_file.c`
* `cli_file.c`

### Protocol

The file transfer application uses a custom file-transfer protocol over:

```text
TCP (SOCK_STREAM)
```

TCP provides reliable and ordered delivery of the transmitted file data.

### Client - `cli_file.c`

The client performs the following operations:

1. Accepts the server IP address and port number.
2. Prompts the user to enter the path of the file to be transferred.
3. Opens the selected file in binary read mode.
4. Extracts the filename from the supplied file path.
5. Establishes a TCP connection with the server.
6. Sends the filename followed by a newline character (`\n`).
7. Reads the file in chunks of approximately `1024` bytes.
8. Sends each chunk to the server using `send()`.
9. Closes the file and socket after the transfer is complete.

### Server - `ser_file.c`

The server performs the following operations:

1. Creates a TCP socket.
2. Binds the socket to the specified port.
3. Listens for incoming client connections.
4. Accepts a client connection.
5. Uses `fork()` to create a child process for each connected client.
6. Reads the filename sent by the client.
7. Creates an output file prefixed with:

```text
received_
```

For example:

```text
document.pdf
```

is stored as:

```text
received_document.pdf
```

8. Receives file data using `recv()`.
9. Writes the received binary data to the output file.
10. Continues receiving until the client closes the connection.
11. Uses non-blocking `waitpid()` to clean up terminated child processes and prevent zombie processes.

### Architecture

```text
                TCP Connection
+---------+  --------------------->  +---------+
| Client  |                           | Server  |
+---------+                           +---------+
     |                                    |
     | Send filename                      |
     |----------------------------------->|
     |                                    |
     | Send file data                     |
     |----------------------------------->|
     |                                    |
     |                              Save as
     |                         received_<filename>
```

---

# 2. Simulated ARP Lookup Engine

### Files

* `ser_arp.c`
* `received_ser_arp.c`
* `cli_arp.c`

### Protocol

The ARP application uses a request-response model over:

```text
TCP (SOCK_STREAM)
```

The client sends an IPv4 address and the server returns the corresponding MAC address.

---

## ARP Server

### Files

```text
ser_arp.c
received_ser_arp.c
```

The server maintains an in-memory ARP cache using a structure similar to:

```c
struct ARP arr[10];
```

The hash table stores mappings between:

```text
IP Address → MAC Address
```

### Hash Table

The ARP cache uses:

* Fixed-size hash table
* Hash-based indexing
* Linear probing for collision handling

When a requested IP address already exists in the cache, the corresponding MAC address is returned immediately.

If the address is not present, the server generates a deterministic MAC address and stores the new mapping in the cache.

---

## Multi-Threaded Client Handling

The ARP server uses POSIX threads to handle multiple clients concurrently.

Important functions include:

```c
pthread_create()
pthread_detach()
pthread_mutex_lock()
pthread_mutex_unlock()
```

Each connected client is handled by a separate thread.

The threads are detached using:

```c
pthread_detach()
```

so that completed threads can release their resources automatically.

---

## Thread Synchronization

Because multiple threads may access the ARP hash table simultaneously, a mutex is used to protect the shared data.

```c
pthread_mutex_t
```

The mutex prevents multiple threads from modifying the ARP cache at the same time.

Conceptually:

```text
Thread 1 ----\
              \
Thread 2 ------> Mutex ---> Shared ARP Cache
              /
Thread 3 ----/
```

This prevents race conditions.

---

## Host ARP Table

The server can also display ARP or neighbor information available on the host operating system.

### `ser_arp.c`

Uses:

```bash
arp -a
```

through:

```c
popen()
```

### `received_ser_arp.c`

Uses the Linux command:

```bash
ip neigh
```

through:

```c
popen()
```

---

## ARP Client - `cli_arp.c`

The client:

1. Connects to the ARP server.
2. Prompts the user for an IPv4 address.
3. Validates the entered IPv4 address using:

```c
inet_pton()
```

4. Sends the IP address to the server.
5. Waits for the server response.
6. Receives the corresponding MAC address.
7. Displays the lookup result to the user.

### Architecture

```text
                         TCP
+-------------+    IP Address    +----------------+
| ARP Client  | ---------------->|   ARP Server   |
+-------------+                  +----------------+
                                        |
                                        v
                               +-----------------+
                               | ARP Hash Table  |
                               | IP -> MAC       |
                               +-----------------+
                                        |
                                        v
                               Generate / Lookup
                                  MAC Address
                                        |
+-------------+     MAC Address         |
| ARP Client  | <-----------------------+
+-------------+
```

---

# 3. Interactive TCP Chat System

### Files

* `ser_chat.c`
* `cli_chat.c`

### Protocol

The chat application uses:

```text
TCP (SOCK_STREAM)
```

Communication follows a simple turn-based text messaging model.

---

## Chat Server - `ser_chat.c`

The chat server:

1. Creates a TCP socket.
2. Binds the socket to the specified port.
3. Listens for incoming client connections.
4. Accepts client connections.
5. Creates a separate child process using:

```c
fork()
```

for each connected client.

6. Sends a client identification message such as:

```text
You are Client 1
```

7. Receives messages from the client.
8. Reads server responses from standard input using:

```c
fgets()
```

9. Sends responses back to the client.
10. Continues the conversation until either side terminates the chat.

---

## Chat Client - `cli_chat.c`

The client:

1. Connects to the TCP chat server.
2. Displays the welcome message received from the server.
3. Accepts user input using:

```c
fgets()
```

4. Sends the message to the server.
5. Waits for the server response.
6. Displays the received message.
7. Continues alternating between sending and receiving messages.

The chat session ends when either side enters:

```text
quit
```

or:

```text
/quit
```

### Architecture

```text
          TCP Connection

+-------------+                +-------------+
| Chat Client |                | Chat Server |
+-------------+                +-------------+
       |                              |
       |------ Client Message ------->|
       |                              |
       |<----- Server Response -------|
       |                              |
       |------ Client Message ------->|
       |                              |
       |<----- Server Response -------|
       |                              |
```

---

# Concepts Demonstrated

This project demonstrates several important concepts in Unix network programming.

### Socket Programming

* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `connect()`
* `send()`
* `recv()`
* `close()`

### Process-Based Concurrency

Used by:

```text
ser_file.c
ser_chat.c
```

using:

```c
fork()
```

Each client connection can be handled by a separate process.

### Thread-Based Concurrency

Used by:

```text
ser_arp.c
received_ser_arp.c
```

using POSIX threads:

```c
pthread_create()
```

### Synchronization

The ARP server protects shared hash-table data using:

```c
pthread_mutex_t
```

### File Handling

The file-transfer application uses:

```c
fopen()
fread()
fwrite()
fclose()
```

### Network Address Handling

Functions such as:

```c
inet_pton()
```

are used to validate and convert IPv4 addresses.

---

# Compilation

The programs can be compiled using GCC.

## 1. File Transfer Module

```bash
gcc -Wall -Wextra -o ser_file ser_file.c
gcc -Wall -Wextra -o cli_file cli_file.c
```

## 2. ARP Lookup Module

The ARP servers use POSIX threads, so the `-pthread` option is required.

```bash
gcc -Wall -Wextra -pthread -o ser_arp ser_arp.c
gcc -Wall -Wextra -pthread -o received_ser_arp received_ser_arp.c

gcc -Wall -Wextra -o cli_arp cli_arp.c
```

## 3. TCP Chat Module

```bash
gcc -Wall -Wextra -o ser_chat ser_chat.c
gcc -Wall -Wextra -o cli_chat cli_chat.c
```

---

# Usage

## File Transfer

### Terminal 1 - Start Server

```bash
./ser_file 8080
```

### Terminal 2 - Start Client

```bash
./cli_file 127.0.0.1 8080
```

Example input:

```text
Enter path of file to send: document.pdf
```

The server stores the received file as:

```text
received_document.pdf
```

---

# ARP Lookup

### Terminal 1 - Start Server

```bash
./ser_arp 9090
```

or, for the Linux variant:

```bash
./received_ser_arp 9090
```

### Terminal 2 - Start Client

```bash
./cli_arp 127.0.0.1 9090
```

Example:

```text
Enter IP address: 192.168.1.15
```

The server searches its ARP cache and returns the corresponding MAC address.

---

# Interactive TCP Chat

### Terminal 1 - Start Server

```bash
./ser_chat 7070
```

### Terminal 2 - Start Client

```bash
./cli_chat 127.0.0.1 7070
```

Messages can then be exchanged interactively between the client and server.

To terminate the chat, enter:

```text
quit
```

or:

```text
/quit
```

---

# Project Structure

```text
.
├── ser_file.c
├── cli_file.c
├── ser_arp.c
├── received_ser_arp.c
├── cli_arp.c
├── ser_chat.c
├── cli_chat.c
└── README.md
```

---

# Requirements

* GCC compiler
* Unix/Linux-like operating system
* POSIX socket support
* POSIX threads (`pthread`)
* Terminal access

For the Linux ARP server variant, the system should provide:

```bash
ip neigh
```

For systems using the traditional ARP utility:

```bash
arp -a
```

---

# Summary

| Application   | Protocol | Server Concurrency | Purpose                                         |
| ------------- | -------- | ------------------ | ----------------------------------------------- |
| File Transfer | TCP      | Multi-Process      | Transfer binary files between client and server |
| ARP Lookup    | TCP      | Multi-Threaded     | Simulate IP-to-MAC address resolution           |
| TCP Chat      | TCP      | Multi-Process      | Interactive client-server messaging             |

---

## Key Learning Outcomes

By working with these programs, you can understand:

* TCP client-server architecture
* Socket creation and connection establishment
* File transfer through sockets
* Multi-process servers using `fork()`
* Multi-threaded servers using `pthread`
* Mutex-based synchronization
* Shared data protection
* Hash-table implementation
* IP address validation
* Request-response communication
* Interactive network messaging
* Process and thread concurrency in Unix systems
