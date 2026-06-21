#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  // TODO: Uncomment the code below to pass the first stage
  setbuf(stdout, NULL);
  char buffer[100];
  while(1) {
    printf("$ ");
    fflush(stdout);
    fgets(buffer, 100, stdin);
    size_t len = strlen(buffer);
    if(len > 0 && buffer[len - 1] == '\n'){
      buffer[len-1] = '\0';
    }
    if(strcmp(buffer, "exit") == 0) {
      break;
    }
    else if(strncmp(buffer, "echo ", 5) == 0) {
      printf("%s\n", buffer + 5);
    }
    else {
      printf("%s: command not found\n", buffer);
    }
  }
  return 0;
}
