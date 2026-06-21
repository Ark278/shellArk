#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUILTIN 3
static const char *builtin_commands[] = {
  "echo",
  "exit",
  "type"
};

static int is_builtin_command(const char *command) {
  for (int i = 0; i < BUILTIN; i++) {
    if (strcmp(command, builtin_commands[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

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
    if(strncmp(buffer, "type ", 5) == 0) {
      if(is_builtin_command(buffer + 5)) {
        printf("%s is a shell builtin\n", buffer + 5);
      }
      else {
        printf("%s: not found\n", buffer + 5);
      }
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
