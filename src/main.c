#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  printf("$ ");
  char cmd[BUFSIZ];
  if (fgets(cmd, sizeof(cmd), stdin) && cmd[0] != '\n' && cmd[0] != '\t' &&
      cmd[0] != ' ') {
    for (int i = 0; i < BUFSIZ; i++) {
      if (cmd[i] == '\n')
        cmd[i] = '\0';
    }
    printf("%s: command not found\n", cmd);
    return 0;
  } else {
    printf("$ ");
  };
  return 0;
}
