#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  // TODO: Uncomment the code below to pass the first stage
  char buffer[100] = {0};
  bool flag = true;
  while(flag) {
    printf("$ ");
    fflush(stdout);
    scanf ("%99s", buffer); 
    printf("%s: command not found\n", buffer);
  }
  return 0;
}
