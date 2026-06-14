#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  char buffer[100] = 0;
  printf("$ ");
  scanf ("%99s", buffer); 
  printf("{%s}: command not found", buffer);
  return 0;
}
