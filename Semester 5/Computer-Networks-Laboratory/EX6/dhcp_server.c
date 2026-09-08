#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 5000
#define MAX_BLOCKS 64

#define REQ_SETUP 1
#define REQ_ALLOCATE 2
#define REQ_EXIT 3

struct Message {
  int type;
  int total_ips;
  int num_blocks;
  int block_id;
  int request_ips;
  int status;
  char payload[1024];
};

struct Block {
  int id;
  int start_ip;
  int end_ip;
  int available;
  int allocated[256];
};

int next_power_of_2(int n) {
  if (n <= 1)
    return 1;
  int p = 1;
  while (p < n)
    p <<= 1;
  return p;
}

int main() {
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);
  struct Message msg;

  struct Block blocks[MAX_BLOCKS];
  int network_prefix[3] = {192, 168, 0};
  int num_blocks_active = 0;

  srand(time(NULL));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("Bind failed");
    close(sockfd);
    exit(1);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    memset(&msg, 0, sizeof(msg));
    int n = recvfrom(sockfd, &msg, sizeof(msg), 0,
                     (struct sockaddr *)&client_addr, &client_len);
    if (n < 0) {
      perror("Recvfrom failed");
      continue;
    }

    struct Message response;
    memset(&response, 0, sizeof(response));
    response.type = msg.type;

    if (msg.type == REQ_SETUP) {
      printf("\n[SETUP] Requested Total IPs: %d, Blocks: %d\n", msg.total_ips,
             msg.num_blocks);

      if (msg.num_blocks > MAX_BLOCKS || msg.num_blocks <= 0) {
        response.status = 0;
        strcpy(response.payload, "Invalid number of blocks requested.\n");
      } else {
        int capacity = next_power_of_2(msg.total_ips);
        int block_size = capacity / msg.num_blocks;

        if (block_size == 0)
          block_size = 1;

        network_prefix[2] = rand() % 256;
        num_blocks_active = msg.num_blocks;

        printf("Nearest power of 2 for %d is %d.\n", msg.total_ips, capacity);
        printf("Generated network: %d.%d.%d.0\n", network_prefix[0],
               network_prefix[1], network_prefix[2]);

        char buffer[1024] = "";
        char temp[256];

        sprintf(temp, "Network: %d.%d.%d.0\nCapacity: %d IPs, Block Size: %d\n",
                network_prefix[0], network_prefix[1], network_prefix[2],
                capacity, block_size);
        strcat(buffer, temp);

        for (int i = 0; i < msg.num_blocks; i++) {
          blocks[i].id = i + 1;
          blocks[i].start_ip = i * block_size;
          blocks[i].end_ip = blocks[i].start_ip + block_size - 1;
          if (blocks[i].end_ip > 255)
            blocks[i].end_ip = 255;
          blocks[i].available = blocks[i].end_ip - blocks[i].start_ip + 1;
          memset(blocks[i].allocated, 0, sizeof(blocks[i].allocated));

          sprintf(
              temp,
              "Block %d: Start %d.%d.%d.%d - End %d.%d.%d.%d | Available: %d\n",
              blocks[i].id, network_prefix[0], network_prefix[1],
              network_prefix[2], blocks[i].start_ip, network_prefix[0],
              network_prefix[1], network_prefix[2], blocks[i].end_ip,
              blocks[i].available);
          strcat(buffer, temp);
          printf("%s", temp);
        }

        response.status = 1;
        strcpy(response.payload, buffer);
      }
      sendto(sockfd, &response, sizeof(response), 0,
             (struct sockaddr *)&client_addr, client_len);
    } else if (msg.type == REQ_ALLOCATE) {
      printf("\n[ALLOCATE] Requested Block %d, IPs: %d\n", msg.block_id,
             msg.request_ips);

      if (msg.block_id < 1 || msg.block_id > num_blocks_active) {
        response.status = 0;
        strcpy(response.payload, "Invalid block ID.\n");
      } else {
        struct Block *b = &blocks[msg.block_id - 1];
        if (b->available < msg.request_ips) {
          response.status = 0;
          strcpy(response.payload,
                 "Not enough addresses available in this block.\n");
        } else {
          char buffer[1024] = "Allocated IPs:\n";
          char temp[64];
          int allocated_count = 0;

          for (int i = b->start_ip;
               i <= b->end_ip && allocated_count < msg.request_ips; i++) {
            if (b->allocated[i] == 0) {
              b->allocated[i] = 1;
              b->available--;
              allocated_count++;

              sprintf(temp, "%d.%d.%d.%d\n", network_prefix[0],
                      network_prefix[1], network_prefix[2], i);
              strcat(buffer, temp);
            }
          }

          sprintf(temp, "Remaining available in block %d: %d\n", b->id,
                  b->available);
          strcat(buffer, temp);

          response.status = 1;
          strcpy(response.payload, buffer);
          printf("Successfully allocated %d IPs from Block %d.\n",
                 msg.request_ips, b->id);
        }
      }
      sendto(sockfd, &response, sizeof(response), 0,
             (struct sockaddr *)&client_addr, client_len);
    } else if (msg.type == REQ_EXIT) {
      printf("\n[EXIT] Client requested disconnect.\n");
      response.status = 1;
      strcpy(response.payload, "Disconnecting... Goodbye!\n");
      sendto(sockfd, &response, sizeof(response), 0,
             (struct sockaddr *)&client_addr, client_len);
    }
  }

  close(sockfd);
  return 0;
}