#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// DDCMP Frame Structure
typedef struct {
    unsigned char syn1;
    unsigned char syn2;
    unsigned char class_type;
    unsigned int count : 14;     
    unsigned long long header : 42;    
    char body[1024];         
    unsigned short crc;
} DDCMP_Frame;

DDCMP_Frame currentFrame;
char dataBuffer[1024];

void GetData() {
    printf("Enter data to send: ");
    fgets(dataBuffer, sizeof(dataBuffer), stdin);
    dataBuffer[strcspn(dataBuffer, "\n")] = 0; // Remove trailing newline
}

void MakeFrame() {
    currentFrame.syn1 = 0xAA; // Standard SYN byte
    currentFrame.syn2 = 0xAA; // Standard SYN byte
    currentFrame.class_type = 0x10; // 0x10 conveys that it is data
    currentFrame.count = strlen(dataBuffer); // Byte count of body
    currentFrame.header = 0; // Keeping header zero
    strcpy(currentFrame.body, dataBuffer);
    currentFrame.crc = 0x0000; // 16 zeros
}

void SendFrame() {
    printf("\n========== SENDER SIDE ==========\n");
    printf("SYN1   : 0x%02X\n", currentFrame.syn1);
    printf("SYN2   : 0x%02X\n", currentFrame.syn2);
    printf("Class  : 0x%02X\n", currentFrame.class_type);
    printf("Count  : %u bytes\n", currentFrame.count);
    printf("Header : 0x%llX\n", currentFrame.header);
    printf("Body   : %s\n", currentFrame.body);
    printf("CRC    : 0x%04X\n", currentFrame.crc);
    printf("=================================\n");
}

void ReceiveFrame() {
    printf("\n========= RECEIVER SIDE =========\n");
    
    // 1. Check SYN bytes
    if (currentFrame.syn1 != 0xAA || currentFrame.syn2 != 0xAA) {
        printf("[Error] Synchronization failed! Invalid SYN bytes.\n");
        return;
    }
    printf("[Receiver] SYN bytes verified.\n");

    // 2. Check Class type
    if (currentFrame.class_type != 0x10) {
        printf("[Error] Invalid frame class! Expected data frame.\n");
        return;
    }
    printf("[Receiver] Class type verified (Data Frame).\n");

    // 3. Check Count (Framing Error check)
    unsigned int actualBodyLen = strlen(currentFrame.body);
    if (currentFrame.count != actualBodyLen) {
        printf("[Error] Framing Error! Count field (%u) does not match the actual body size (%u).\n", currentFrame.count, actualBodyLen);
        return;
    }
    printf("[Receiver] Count field verified (%u bytes).\n", currentFrame.count);

    printf("SYN1   : 0x%02X\n", currentFrame.syn1);
    printf("SYN2   : 0x%02X\n", currentFrame.syn2);
    printf("Class  : 0x%02X\n", currentFrame.class_type);
    printf("Count  : %u bytes\n", currentFrame.count);
    printf("Header : 0x%llX\n", currentFrame.header);
    printf("Body   : %s\n", currentFrame.body);
    printf("CRC    : 0x%04X\n", currentFrame.crc);
    printf("[Receiver] Frame received successfully.\n");
    printf("=================================\n");
}

int main() {
    char choice;
    
    printf("========== DDCMP PROTOCOL ==========\n");

    while (true) {
        printf("\nDo you have data to send? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // clear newline
        
        if (choice == 'n' || choice == 'N') {
            printf("Exiting...\n");
            break;
        }
        
        GetData();
        MakeFrame();
        SendFrame();
        ReceiveFrame();
    }
    
    return 0;
}
