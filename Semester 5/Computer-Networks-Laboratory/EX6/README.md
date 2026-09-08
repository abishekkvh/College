# Network Application Suite - UDP Protocols

A collection of C network programming applications demonstrating **client-server communication using UDP sockets**.

The repository contains three main networking modules:

* Custom DHCP Subnet Allocator
* Caching DNS Resolver
* UDP Interactive Chat System

These programs demonstrate concepts such as:

* UDP socket programming
* Client-server communication
* Dynamic IP allocation
* Subnet calculation
* DNS resolution and caching
* Terminal-based messaging
* `sendto()` and `recvfrom()`
* `getaddrinfo()`

---

# Module Overview

| File                | Role               | Default Port | Main Function                                         |
| ------------------- | ------------------ | -----------: | ----------------------------------------------------- |
| `dhcp_client.c`     | Custom DHCP Client |         5000 | Requests network setup and IP allocation              |
| `dhcp_server.c`     | Custom DHCP Server |         5000 | Creates subnet blocks and allocates IP addresses      |
| `dns_client.c`      | DNS Client         |         6001 | Sends domain names and displays resolved IP addresses |
| `dns_server.c`      | Caching DNS Server |         6001 | Resolves domains and stores results in a DNS cache    |
| `UDP_Chat_Client.c` | UDP Chat Client    |         6001 | Sends and receives interactive text messages          |
| `UDP_Chat_Server.c` | UDP Chat Server    |         6001 | Receives messages and sends interactive replies       |

> **Note:** The DNS module and UDP Chat module both use port `6001`. Therefore, they should not be executed simultaneously unless the port number of one module is changed.

---

# 1. Custom DHCP Subnet Allocator

## Files

* `dhcp_client.c`
* `dhcp_server.c`

## Protocol

The DHCP simulation uses:

```text
UDP (SOCK_DGRAM)
```

The application simulates network setup and dynamic IP address allocation between a DHCP-like client and server.

---

## DHCP Client - `dhcp_client.c`

The client performs the following operations:

1. Creates a UDP socket.
2. Connects logically to:

```text
127.0.0.1:5000
```

3. Sends a setup request:

```text
REQ_SETUP
```

4. Provides information such as:

   * Total number of required IP addresses
   * Number of required subnet blocks
5. Receives the generated network and subnet information from the server.
6. Allows the user to select a subnet block.
7. Sends an allocation request:

```text
REQ_ALLOCATE
```

8. Receives an available IP address from the selected block.
9. Repeats allocation requests interactively.
10. Terminates the session using:

```text
REQ_EXIT
```

---

## DHCP Server - `dhcp_server.c`

The server:

1. Creates a UDP socket.
2. Binds the socket to port:

```text
5000
```

3. Waits for incoming client requests.
4. Processes the requested total number of IP addresses.
5. Uses:

```c
next_power_of_2()
```

to round the required number of IP addresses to the nearest power of 2.

For example:

```text
Requested IPs = 100
Allocated Capacity = 128
```

6. Generates a network prefix similar to:

```text
192.168.X.0
```

where `X` is selected dynamically.

7. Divides the total network into the requested number of subnet blocks.
8. Maintains individual IP allocation states.
9. Assigns available IP addresses when the client requests an allocation.
10. Tracks used and available addresses internally.

---

## DHCP Architecture

```text
              UDP Communication

+-------------+                     +-------------+
| DHCP Client |                     | DHCP Server |
+-------------+                     +-------------+
       |                                  |
       |--------- REQ_SETUP ------------->|
       |                                  |
       |      Total IPs + Block Count     |
       |--------------------------------->|
       |                                  |
       |<----- Network/Subnet Details ----|
       |                                  |
       |-------- REQ_ALLOCATE ----------->|
       |                                  |
       |<------- Allocated IP ------------|
       |                                  |
       |-------- REQ_ALLOCATE ----------->|
       |                                  |
       |<------- Allocated IP ------------|
       |                                  |
       |---------- REQ_EXIT ------------->|
```

---

# 2. Caching DNS Resolver

## Files

* `dns_client.c`
* `dns_server.c`

## Protocol

The DNS application uses:

```text
UDP (SOCK_DGRAM)
```

The client sends a domain name to the server, and the server returns its corresponding IP address.

---

## DNS Client - `dns_client.c`

The client:

1. Creates a UDP socket.
2. Communicates with:

```text
127.0.0.1:6001
```

3. Prompts the user to enter a domain name.

Example:

```text
google.com
```

4. Sends the domain name to the DNS server.
5. Waits for the server response.
6. Displays the returned IP address.
7. Continues accepting domain queries.
8. Ends the session when the user enters:

```text
exit
```

---

## DNS Server - `dns_server.c`

The DNS server:

1. Creates a UDP socket.
2. Binds to port:

```text
6001
```

3. Waits for incoming domain queries.
4. Maintains an in-memory DNS cache containing up to approximately 100 records.

The records are stored using a structure such as:

```c
struct DNSRecord
```

Each entry stores:

```text
Domain Name -> IP Address
```

---

## DNS Cache Operation

When a domain request is received, the server first checks its local cache.

### Cache Hit

If the domain already exists:

```text
Domain Query
     |
     v
DNS Cache
     |
     v
Return Stored IP
```

No system-level DNS lookup is required.

---

### Cache Miss

If the domain does not exist in the cache, the server uses:

```c
getaddrinfo()
```

to perform system DNS resolution.

The result is then:

1. Converted into a readable IP address.
2. Stored in the local DNS table.
3. Returned to the client.

---

## DNS Architecture

```text
+------------+                 +-------------+
| DNS Client |                 | DNS Server  |
+------------+                 +-------------+
      |                              |
      |------ Domain Name ---------->|
      |                              |
      |                         Check Cache
      |                              |
      |                     +--------+--------+
      |                     |                 |
      |                 Cache Hit        Cache Miss
      |                     |                 |
      |                     |           getaddrinfo()
      |                     |                 |
      |                     |          Store New Record
      |                     |                 |
      |<---------- IP Address ---------------|
```

---

## Example

First query:

```text
Enter domain: google.com
```

The server may resolve the domain using:

```c
getaddrinfo()
```

and store:

```text
google.com -> <resolved IP>
```

If the client requests `google.com` again, the result can be returned directly from the local cache.

---

# 3. UDP Interactive Chat System

## Files

* `UDP_Chat_Client.c`
* `UDP_Chat_Server.c`

## Protocol

The chat application uses:

```text
UDP (SOCK_DGRAM)
```

Communication follows a simple turn-based messaging model.

---

## UDP Chat Client - `UDP_Chat_Client.c`

The client:

1. Creates a UDP socket.
2. Sends text messages to the server.
3. Communicates with port:

```text
6001
```

4. Reads messages from the keyboard.
5. Sends messages using:

```c
sendto()
```

6. Waits for the server reply using:

```c
recvfrom()
```

7. Displays the received response.
8. Continues alternating between sending and receiving messages.
9. Terminates when:

```text
exit
```

is entered or received.

---

## UDP Chat Server - `UDP_Chat_Server.c`

The server:

1. Creates a UDP socket.
2. Binds the socket to port:

```text
6001
```

3. Waits for incoming messages using:

```c
recvfrom()
```

4. Displays the received client message.
5. Prompts the server operator to enter a reply.
6. Sends the reply using:

```c
sendto()
```

7. Continues the conversation sequentially.
8. Terminates when either side sends:

```text
exit
```

---

## UDP Chat Architecture

```text
              UDP Communication

+-------------+                     +-------------+
| Chat Client |                     | Chat Server |
+-------------+                     +-------------+
       |                                  |
       |-------- Client Message --------->|
       |                                  |
       |<------- Server Response ---------|
       |                                  |
       |-------- Client Message --------->|
       |                                  |
       |<------- Server Response ---------|
       |                                  |
       |------------- exit -------------->|
```

---

# UDP Socket Programming Concepts

The programs mainly use the following socket functions.

## `socket()`

Creates the UDP socket.

```c
socket(AF_INET, SOCK_DGRAM, 0);
```

---

## `bind()`

Associates the server socket with an IP address and port.

```c
bind();
```

Primarily used by the server programs.

---

## `sendto()`

Sends data through a UDP socket.

```c
sendto();
```

Used for:

* DHCP control messages
* Domain queries
* DNS responses
* Chat messages

---

## `recvfrom()`

Receives UDP datagrams.

```c
recvfrom();
```

---

## `getaddrinfo()`

Used by the DNS server to resolve domain names into IP addresses.

```c
getaddrinfo();
```

---

# UDP Communication Model

Unlike TCP, UDP is connectionless.

There is normally no use of:

```text
listen()
accept()
```

Instead, communication generally follows:

```text
Client
  |
socket()
  |
sendto()
  |
  v
Server
  |
recvfrom()
  |
Process Request
  |
sendto()
  |
  v
Client
  |
recvfrom()
```

---

# Compilation

All programs can be compiled using GCC.

## 1. Custom DHCP Module

```bash
gcc -Wall -Wextra -o dhcp_server dhcp_server.c
gcc -Wall -Wextra -o dhcp_client dhcp_client.c
```

---

## 2. DNS Resolver Module

```bash
gcc -Wall -Wextra -o dns_server dns_server.c
gcc -Wall -Wextra -o dns_client dns_client.c
```

---

## 3. UDP Interactive Chat Module

```bash
gcc -Wall -Wextra -o udp_chat_server UDP_Chat_Server.c
gcc -Wall -Wextra -o udp_chat_client UDP_Chat_Client.c
```

---

# Execution Guide

# Custom DHCP Subnet Allocator

## Terminal 1 - Start Server

```bash
./dhcp_server
```

## Terminal 2 - Start Client

```bash
./dhcp_client
```

The client may request values such as:

```text
Total required IP addresses: 100
Number of blocks: 4
```

The server calculates an appropriate address space, creates subnet blocks, and allows the client to request addresses from individual blocks.

---

# DNS Resolver

## Terminal 1 - Start DNS Server

```bash
./dns_server
```

## Terminal 2 - Start DNS Client

```bash
./dns_client
```

Example query:

```text
Enter domain: google.com
```

or:

```text
Enter domain: example.com
```

The server returns the corresponding IP address.

When the same domain is requested again, the result may be served directly from the server's local DNS cache.

To terminate:

```text
exit
```

---

# UDP Interactive Chat

## Terminal 1 - Start Chat Server

```bash
./udp_chat_server
```

## Terminal 2 - Start Chat Client

```bash
./udp_chat_client
```

Messages can then be exchanged sequentially between both terminals.

Example:

```text
Client: Hello Server
Server: Hello Client

Client: How are you?
Server: I am fine.
```

To terminate the chat:

```text
exit
```

---

# Project Structure

```text
.
├── dhcp_client.c
├── dhcp_server.c
├── dns_client.c
├── dns_server.c
├── UDP_Chat_Client.c
├── UDP_Chat_Server.c
└── README.md
```

---

# Requirements

The programs require:

* GCC compiler
* Unix/Linux-like operating system
* POSIX socket support
* IPv4 networking
* Terminal access

The DNS server additionally requires access to the system resolver for:

```c
getaddrinfo()
```

---

# TCP vs UDP

The applications in this repository specifically demonstrate UDP communication.

| Feature       | TCP                     | UDP                          |
| ------------- | ----------------------- | ---------------------------- |
| Connection    | Connection-oriented     | Connectionless               |
| Reliability   | Reliable                | No delivery guarantee        |
| Ordering      | Ordered                 | No ordering guarantee        |
| Speed         | Relatively slower       | Faster and lightweight       |
| Socket Type   | `SOCK_STREAM`           | `SOCK_DGRAM`                 |
| Data Transfer | `send()` / `recv()`     | `sendto()` / `recvfrom()`    |
| Common Uses   | File transfer, web, SSH | DNS, DHCP, streaming, gaming |

---

# Concepts Demonstrated

This repository provides practical examples of:

* UDP socket programming in C
* Client-server architecture
* IPv4 socket addressing
* `sockaddr_in`
* `sendto()` and `recvfrom()`
* Dynamic subnet creation
* Power-of-two address allocation
* Simulated DHCP operations
* Dynamic IP address allocation
* Domain name resolution
* DNS caching
* `getaddrinfo()`
* Interactive terminal communication
* Connectionless network programming

---

# Summary

| Application  | Protocol | Port | Purpose                                   |
| ------------ | -------- | ---: | ----------------------------------------- |
| Custom DHCP  | UDP      | 5000 | Subnet creation and dynamic IP allocation |
| DNS Resolver | UDP      | 6001 | Domain-to-IP resolution with caching      |
| UDP Chat     | UDP      | 6001 | Two-way terminal messaging                |

---

# Learning Outcomes

By working with these programs, you can understand:

* How UDP client-server applications are developed in C
* How UDP differs from TCP
* How clients communicate using `sendto()` and `recvfrom()`
* How subnet capacity can be calculated
* How IP addresses can be allocated dynamically
* How DNS requests can be resolved and cached
* How `getaddrinfo()` performs hostname resolution
* How connectionless chat applications work
* How application-level network protocols can be simulated using sockets
