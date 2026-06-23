#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUILTIN 5
static const char *builtin_commands[] = {
  "echo",
  "exit",
  "type",
  "pwd",
  "cd"
};

char* find_executable(const char *cmd){
  char *path_env = getenv("PATH");
  if(path_env == NULL) {
    return NULL;
  }
  char *path_env_copy = strdup(path_env);
  if(path_env_copy == NULL) {
    return NULL;
  }
  char *dir = strtok(path_env_copy, ":");
  while(dir !=NULL){
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
    if(access(full_path, X_OK) == 0) {
      char *result = strdup(full_path);
      free(path_env_copy);
      return result;
    }
    dir = strtok(NULL, ":");
  }
  free(path_env_copy);
  return NULL;
}


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
        continue;
      }
      char *path = find_executable(buffer + 5);
      if(path) {
        printf("%s is %s\n", buffer + 5, path);
        free(path);
      }
      else {
        printf("%s: not found\n", buffer + 5);
      }
    }
    else if(strncmp(buffer, "echo ", 5) == 0) {
      printf("%s\n", buffer + 5);
    }
    else if(strcmp(buffer, "pwd") == 0) {
      char cwd[1024];
      if(getcwd(cwd, sizeof(cwd)) !=NULL) {
        printf("%s\n", cwd);
      }
      else {
        perror("getcwd");
      }
    }
    else if(strncmp(buffer, "cd ", 3) == 0) {
      char *dir = buffer + 3;
      if(strcmp(dir, "..") == 0) {
        if(chdir("..") != 0) {
          printf("cd: %s: No such file or directory\n", dir);
        }
        continue;
      }
      if(strcmp(dir, "~") == 0) {
        char *home = getenv("HOME");
        if(home != NULL) {
          if(chdir(home) != 0) {
            printf("cd: %s: No such file or directory\n", home);
          }
          continue;
        }
      }
      if(chdir(dir) != 0) {
        printf("cd: %s: No such file or directory\n", dir);
      }
    }
    else {
      char *args[64];
      int argc = 0;

      char *token = strtok(buffer, " ");
      while(token != NULL && argc < 63) {
        args[argc++] = token;
        token = strtok(NULL, " ");
      }
      args[argc] = NULL;
      if(argc == 0) {
        continue;
      }

      char *path = find_executable(args[0]);
      if(path == NULL) {
        printf("%s: command not found\n", buffer);
        continue;
      }
      else{
        pid_t pid = fork();
        if(pid == 0) {
          execv(path, args);
          perror("execv");
          exit(1);
        }
        else if(pid > 0) {
          int status;
          waitpid(pid, &status, 0);
        }
        else {
          perror("fork");
        }
        free(path);
      }
      // else{
      //   printf("%s: command not found\n", buffer);
      // }
    }
  }
  return 0;
}
