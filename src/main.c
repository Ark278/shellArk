#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  // TODO: Uncomment the code below to pass the first stage
  setbuf(stdout, NULL);
  char buffer[100] = {0};
  while(strcmp(buffer, "exit")) {
    printf("$ ");
    fflush(stdout);
    
    fgets(buffer, 100, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    if(strncmp(buffer, "echo ", 5) == 0) {
      printf("%s\n", buffer + 5);
      continue;
    }
    printf("%s: command not found\n", buffer);
  }
  return 0;
}
