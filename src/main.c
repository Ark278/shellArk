#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  // TODO: Uncomment the code below to pass the first stage
  char buffer[100] = {0};
  while(strcmp(buffer, "exit")) {
    printf("$ ");
    fflush(stdout);
    scanf ("%99s", buffer);
    if(strcmp(buffer, "echo") == 0) {
      char echo_buffer[100] = {0};
      fgets(echo_buffer, 100, stdin);
      printf("%s", echo_buffer);
      continue;
    }
    printf("%s: command not found\n", buffer);
  }
  return 0;
}
