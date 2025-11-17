// https://github.com/rtfeldman/c-workshop-v1/blob/dd100eb96ab3c5b56d884c7cd46f2545ff129f01/exercises/1.c

#include <unistd.h>
#include <stdio.h>

int main() {
  write(1, "Hello World!", 13);
  write(1, "Hello World!\n", 13);
  write(1, "Hello World!\n", 14);
  // write(1, "Hello World!\n", 200);

  int num = 42;
  printf("The number is: %d\n", num);

  int num2 = 43;
  printf("The numbers are: %d and %d\n", num, num2);

  return 0;
  // return 1;
}
