// https://github.com/rtfeldman/c-workshop-v1/blob/dd100eb96ab3c5b56d884c7cd46f2545ff129f01/exercises/2.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
  char *header = "HTTP/1.1 200 OK";
  char *header_with_zero_byte = "HT\0TP/1.1 200 OK";

  write(1, header, 15);
  write(1, header, strlen(header));

  printf("\n\nThat output was from write(). This is from printf: %s\n", header);

  write(1, header_with_zero_byte, 16);
  write(1, header, strlen(header_with_zero_byte));

  printf("\n\nThat output was from write(). This is from printf: %s\n", header_with_zero_byte);
  printf("\n\nThat output was from write(). This is from printf: %zu\n", header_with_zero_byte);
  // printf("\n\nThat output was from write(). This is from printf: %s\n", (char*)123456);
  printf("\n\nThat output was from write(). This is from printf: %s\n", (char*)0);

  return 0;
}
