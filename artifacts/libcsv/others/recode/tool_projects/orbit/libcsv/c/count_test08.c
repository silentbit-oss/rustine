#include <stdio.h>
#include <string.h>

int main() {
  char test08_data[] = "\" abc\"                                             "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                          \", \"123\"";
  
  char test08_result[] = " abc\"                                               "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                                     "
                       "                                        ";
  
  printf("test08_data length: %zu\n", strlen(test08_data));
  printf("test08_result length: %zu\n", strlen(test08_result));
  
  // Count spaces in each line
  char line1[] = "\" abc\"                                             ";
  char line2[] = "                                                     ";
  char line9_data[] = "                                          \", \"123\"";
  char line9_result[] = "                                        ";
  
  printf("\nLine 1 length: %zu\n", strlen(line1));
  printf("Line 2-8 length: %zu\n", strlen(line2));
  printf("Line 9 data length: %zu\n", strlen(line9_data));
  printf("Line 9 result length: %zu\n", strlen(line9_result));
  
  return 0;
}
