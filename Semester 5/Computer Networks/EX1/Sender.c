#include <stdio.h>
#include <string.h>

#include "Sender.h"

// CRC-4 polynomial: x^4 + x + 1 = 0x13
#define CRC_POLY 0x13

unsigned short computeCRC(const char *data) {
  unsigned char crc = 0x00; // 4-bit CRC register
  int len = (int)strlen(data);

  for (int i = 0; i < len; i++) {
    unsigned char bit = (data[i] == '1') ? 1 : 0;
    unsigned char xorFlag = (crc & 0x08) ? 1 : 0; // Check MSB (bit 3)
    crc = (crc << 1) & 0x0F; // Shift left, keep 4 bits
    crc |= bit;
    if (xorFlag)
      crc ^= CRC_POLY & 0x0F; // XOR with lower 4 bits of polynomial (0x03)
  }

  // Push 4 zero bits through for CRC-4
  for (int i = 0; i < 4; i++) {
    unsigned char xorFlag = (crc & 0x08) ? 1 : 0;
    crc = (crc << 1) & 0x0F;
    if (xorFlag)
      crc ^= CRC_POLY & 0x0F;
  }

  return (unsigned short)(crc & 0x0F);
}

void MakeFrame(DDCMPFrame *frame, char *headerStr, char *bodyData) {
  frame->syn1 = 0xAA;
  frame->syn2 = 0xAA;
  frame->frameClass = 0x10;
  frame->count = (unsigned int)strlen(bodyData) / 8;
  strcpy(frame->header, headerStr);
  strcpy(frame->body, bodyData);

  // Compute CRC-4 over the body data
  frame->crc = computeCRC(bodyData);
}

void SendFrame(DDCMPFrame *frame) {
  printf("\n========== SENDER SIDE ==========\n");
  printf("SYN1   : 0x%02X\n", frame->syn1);
  printf("SYN2   : 0x%02X\n", frame->syn2);
  printf("Class  : 0x%02X\n", frame->frameClass);
  printf("Count  : %u bytes\n", frame->count);
  printf("Header : %s\n", frame->header);
  printf("Body   : %s\n", frame->body);
  printf("CRC-4  : 0x%X\n", frame->crc);
  printf("=================================\n");
}
