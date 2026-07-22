#include <stdio.h>
#include <string.h>

#include "Sender.h"

void ReceiveFrame(DDCMPFrame *frame) {
  printf("\n========= RECEIVER SIDE =========\n");

  // 1. Check SYN bytes
  if (frame->syn1 != 0xAA || frame->syn2 != 0xAA) {
    printf("[Error] Synchronization failed! Invalid SYN bytes.\n");
    return;
  }
  printf("[Receiver] SYN bytes verified.\n");

  // 2. Check Class type
  if (frame->frameClass != 0x10) {
    printf("[Error] Invalid frame class! Expected data frame.\n");
    return;
  }
  printf("[Receiver] Class type verified (Data Frame).\n");

  // 3. Check Count (Framing Error check)
  unsigned int actualBodyLen = (unsigned int)strlen(frame->body) / 8;
  if (frame->count != actualBodyLen) {
    printf("[Error] Framing Error! Count field (%u) does not match the actual "
           "body size (%u).\n",
           frame->count, actualBodyLen);
    return;
  }
  printf("[Receiver] Count field verified (%u bytes).\n", frame->count);

  // 4. CRC Validation - recompute and compare
  unsigned short receivedCRC = frame->crc;
  unsigned short computedCRC = computeCRC(frame->body);

  if (receivedCRC != computedCRC) {
    printf("[Error] CRC-4 Check Failed! Received: 0x%X, Computed: 0x%X\n",
           receivedCRC, computedCRC);
    printf("[Receiver] Frame is CORRUPTED. Requesting retransmission.\n");
    printf("=================================\n");
    return;
  }
  printf("[Receiver] CRC-4 verified (0x%X). Frame integrity confirmed.\n",
         receivedCRC);

  printf("SYN1   : 0x%02X\n", frame->syn1);
  printf("SYN2   : 0x%02X\n", frame->syn2);
  printf("Class  : 0x%02X\n", frame->frameClass);
  printf("Count  : %u bytes\n", frame->count);
  printf("Header : %s\n", frame->header);
  printf("Body   : %s\n", frame->body);
  printf("CRC-4  : 0x%X\n", frame->crc);
  printf("[Receiver] Frame received successfully.\n");
  printf("=================================\n");
}
