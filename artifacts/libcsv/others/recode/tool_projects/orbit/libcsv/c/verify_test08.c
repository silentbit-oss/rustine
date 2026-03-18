#include <stdio.h>
#include <string.h>

int main() {
  // From test_csv.c line 310-320
  char test08_result[] = " abc\"                                               "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                        ";
  
  printf("Result length: %zu\n", strlen(test08_result));
  
  // Let's count character by character
  int spaces_line1_after = 0;
  for (int i = 5; test08_result[i] == ' ' && i < 51; i++) {
    spaces_line1_after++;
  }
  printf("Line 1: ' abc\"' (5 chars) + %d spaces = %d\n", spaces_line1_after, 5 + spaces_line1_after);
  
  int spaces_line2 = 0;
  for (int i = 51; test08_result[i] == ' ' && i < 104; i++) {
    spaces_line2++;
  }
  printf("Line 2: %d spaces\n", spaces_line2);
  
  // Print as hex to verify
  printf("\nFirst 60 bytes (hex):");
  for (int i = 0; i < 60; i++) {
    if (i % 10 == 0) printf("\n%3d: ", i);
    printf("%02x ", (unsigned char)test08_result[i]);
  }
  printf("\n");
  
  return 0;
}
