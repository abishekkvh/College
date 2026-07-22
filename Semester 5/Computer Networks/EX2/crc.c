 #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <stdbool.h>
  
  #define MAX_LEN 1024  // Larger buffer, still fixed for simplicity

  // Validate string contains only '0' and '1'
  bool is_binary(const char *s) {
      if (!s) return false;
      for (int i = 0; s[i]; i++) {
          if (s[i] != '0' && s[i] != '1') return false;
      }
      return true;
  }

  // Performs bitwise XOR between two binary strings (same length)
  void findXor(const char a[], const char b[], char result[], int n) {
      for (int i = 1; i < n; i++) {       // Skip index 0 (optimization)
          result[i - 1] = (a[i] == b[i]) ? '0' : '1';
      }
      result[n - 1] = '\0';
  }

  // Performs Modulo-2 Division with bounds checking
  void mod2div(const char dividend[], const char divisor[], char remainder[]) {
      int pick = strlen(divisor);
      int n = strlen(dividend);

      if (pick > n || pick <= 1) {        // Guard: divisor too long or trivial
          remainder[0] = '\0';
          return;
      }

      char tmp[MAX_LEN];
      char xorResult[MAX_LEN];
      char zeros[MAX_LEN];

      // Create string of zeros (same length as divisor)
      for (int i = 0; i < pick; i++) zeros[i] = '0';
      zeros[pick] = '\0';

      // Copy first part of dividend
      strncpy(tmp, dividend, pick);
      tmp[pick] = '\0';

      while (pick < n) {
          if (tmp[0] == '1')
              findXor(divisor, tmp, xorResult, pick);
          else
              findXor(zeros, tmp, xorResult, pick);

          // Bring down next bit from dividend
          int len = strlen(xorResult);
          if (len + 1 >= MAX_LEN) break;  // Safety: prevent overflow
          xorResult[len] = dividend[pick];
          xorResult[len + 1] = '\0';

          strncpy(tmp, xorResult, MAX_LEN - 1);
          tmp[MAX_LEN - 1] = '\0';
          pick++;
      }

      // Final XOR
      if (tmp[0] == '1')
          findXor(divisor, tmp, remainder, pick);
      else
          findXor(zeros, tmp, remainder, pick);
  }

  void encodeData(const char data[], const char key[], char code[]) {
      // Input validation
      if (!is_binary(data) || !is_binary(key)) {
          printf("Error: Input must be binary strings (only 0 and 1)\n");
          code[0] = '\0';
          return;
      }
      if (strlen(key) < 2) {
          printf("Error: Key must be at least 2 bits\n");
          code[0] = '\0';
          return;
      }

      char paddedData[MAX_LEN] = {0};
      char remainder[MAX_LEN] = {0};

      strncpy(paddedData, data, MAX_LEN - 1);
      int zeros = strlen(key) - 1;

      // Append zeros with bounds check
      if (strlen(paddedData) + zeros >= MAX_LEN) {
          printf("Error: Data too long for buffer\n");
          code[0] = '\0';
          return;
      }
      for (int i = 0; i < zeros; i++)
          strcat(paddedData, "0");

      mod2div(paddedData, key, remainder);

      // Build codeword: data + remainder
      strncpy(code, data, MAX_LEN - 1);
      strncat(code, remainder, MAX_LEN - strlen(code) - 1);
  }

  // Returns true (1) if no error detected, false (0) if error
  bool receiver(const char code[], const char key[]) {
      if (!is_binary(code) || !is_binary(key)) return false;
      if (strlen(key) < 2) return false;

      char remainder[MAX_LEN];
      mod2div(code, key, remainder);

      for (int i = 0; remainder[i]; i++) {
          if (remainder[i] == '1') return false;  // Error detected
      }
      return true;  // No error
  }

  int main() {
      char data[] = "100100";
      char key[] = "1101";
      char code[MAX_LEN];

      printf("Sender Side\n");
      printf("Data: %s\n", data);
      printf("Key:  %s\n", key);

      encodeData(data, key, code);

      if (code[0]) {  // Check if encoding succeeded
          printf("Encoded Data: %s\n\n", code);

          printf("Receiver Side\n");
          if (receiver(code, key))
              printf("Data is correct (No errors detected)\n");
          else
              printf("Data is incorrect (Error detected)\n");
      }

      return 0;
}