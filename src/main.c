#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Entree
  char raw_input[BUFSIZ];

  printf("$ ");
  while (fgets(raw_input, sizeof(raw_input), stdin)) {

    // Tableau contenant les mots dans l'entree
    char *command[BUFSIZ];
    int k = 0;

    // Chaine de charactere representant le mot courant
    char token[FILENAME_MAX];
    token[0] = '\0';
    int j = 0;

    // Parse (elimine les espaces pour recupere uniquement les mots)
    for (int i = 0;
         raw_input[i] != '\0' && k < BUFSIZ && j < (FILENAME_MAX - 1); i++) {

      if (!isspace((unsigned char)raw_input[i])) {

        token[j] = raw_input[i];

        j++;
      } else {

        if (token[0] != '\0') {

          token[j] = '\0';
          command[k] = strdup(token);
          k++;
        };

        j = 0;
      };
    };

    if (command[0] != NULL && command[0][0] != '\0')
      printf("%s: command not found\n", command[0]);

    printf("$ ");
  };
  return 0;
}
