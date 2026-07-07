#include <ctype.h>
#include <stdio.h>
#include <string.h>

// determine la commande a executer
typedef enum {
  EXIT,
  NOT_FOUND,
} Keywords;

Keywords get_command(char *name);

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

    if (command[0] != NULL && command[0][0] != '\0') {

      switch (get_command(command[0])) {
      case EXIT:
        return 0;
      case NOT_FOUND:
        printf("%s: command not found\n", command[0]);
      }
    };

    printf("$ ");
  };
  return 0;
}

/*
 * @brief Compare le nom en entree a une liste de command
 * @return le numero de la command a execute
 */
Keywords get_command(char *name) {
  if (strcmp(name, "exit") == 0)
    return EXIT;
  return NOT_FOUND;
};
