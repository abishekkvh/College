#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CRC_MAX_LEN 1024

bool is_binary(const char *s) {
    for (int i = 0; s[i]; i++) if (s[i] != '0' && s[i] != '1') return false;
    return true;
}

void findXor(const char a[], const char b[], char result[], int n) {
    for (int i = 1; i < n; i++) result[i-1] = (a[i] == b[i]) ? '0' : '1';
    result[n-1] = '\0';
}

void mod2div(const char dividend[], const char divisor[], char remainder[]) {
    int pick = strlen(divisor);
    int n = strlen(dividend);
    if (pick > n || pick <= 1) { remainder[0] = '\0'; return; }
    char tmp[CRC_MAX_LEN], xorResult[CRC_MAX_LEN], zeros[CRC_MAX_LEN];
    for (int i = 0; i < pick; i++) zeros[i] = '0';
    zeros[pick] = '\0';
    strncpy(tmp, dividend, pick); tmp[pick] = '\0';
    while (pick < n) {
        if (tmp[0] == '1') findXor(divisor, tmp, xorResult, pick);
        else findXor(zeros, tmp, xorResult, pick);
        int len = strlen(xorResult);
        if (len + 1 >= CRC_MAX_LEN) break;
        xorResult[len] = dividend[pick];
        xorResult[len+1] = '\0';
        strncpy(tmp, xorResult, CRC_MAX_LEN-1);
        tmp[CRC_MAX_LEN-1] = '\0';
        pick++;
    }
    int divisorLen = strlen(divisor);
    if (tmp[0] == '1') findXor(divisor, tmp, remainder, divisorLen);
    else findXor(zeros, tmp, remainder, divisorLen);
}

void encodeData(const char data[], const char key[], char code[]) {
    char paddedData[CRC_MAX_LEN] = {0}, remainder[CRC_MAX_LEN] = {0};
    strncpy(paddedData, data, CRC_MAX_LEN-1);
    int zeros = strlen(key) - 1;
    for (int i = 0; i < zeros; i++) strcat(paddedData, "0");
    mod2div(paddedData, key, remainder);
    strncpy(code, data, CRC_MAX_LEN-1);
    strncat(code, remainder, CRC_MAX_LEN - strlen(code) - 1);
}

bool verifyCRC(const char code[], const char key[]) {
    char remainder[CRC_MAX_LEN];
    mod2div(code, key, remainder);
    for (int i = 0; remainder[i]; i++) if (remainder[i] == '1') return false;
    return true;
}

int main() {
    // Test 1: Simple case from crc.c
    char data1[] = "100100";
    char key[] = "1101";
    char code1[CRC_MAX_LEN];
    encodeData(data1, key, code1);
    printf("Test 1: data=%s, key=%s\n", data1, key);
    printf("  code=%s\n", code1);
    printf("  verify=%s\n", verifyCRC(code1, key) ? "PASS" : "FAIL");
    
    // Test 2: byteCount + payload
    char byteCount[] = "0000000000011010";  // 26
    char payload[] = "1000100111101111000101011110110011000000101010000110010000000001100011101111101000001010000000010000000000011010001010110011110001001101010111101010101000010001001000100011001101000100010101010110100001100101";
    char crcInput[CRC_MAX_LEN];
    strcpy(crcInput, byteCount);
    strcat(crcInput, payload);
    printf("\nTest 2: byteCount+payload (len=%d)\n", (int)strlen(crcInput));
    
    char code2[CRC_MAX_LEN];
    encodeData(crcInput, key, code2);
    printf("  code len=%d\n", (int)strlen(code2));
    printf("  verify=%s\n", verifyCRC(code2, key) ? "PASS" : "FAIL");
    
    // Test 3: receiver side - byteCount + data + remainder
    // The sender sends: data + remainder (frame->data + frame->crc)
    // The receiver builds: byteCount + data + remainder
    char senderSent[CRC_MAX_LEN];
    strcpy(senderSent, payload);
    // Get remainder from code2
    int remLen = strlen(key) - 1;
    int codeLen = strlen(code2);
    char remainder[CRC_MAX_LEN];
    strncpy(remainder, code2 + codeLen - remLen, remLen);
    remainder[remLen] = '\0';
    printf("  remainder=%s\n", remainder);
    
    strcat(senderSent, remainder);
    printf("  senderSent (data+remainder) len=%d\n", (int)strlen(senderSent));
    
    char receiverCodeword[CRC_MAX_LEN];
    strcpy(receiverCodeword, byteCount);
    strcat(receiverCodeword, senderSent);
    printf("  receiverCodeword (byteCount+data+remainder) len=%d\n", (int)strlen(receiverCodeword));
    printf("  verify=%s\n", verifyCRC(receiverCodeword, key) ? "PASS" : "FAIL");
    
    // Debug: show remainders
    char rem[CRC_MAX_LEN];
    mod2div(receiverCodeword, key, rem);
    printf("  final remainder: %s\n", rem);
}
