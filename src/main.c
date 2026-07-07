#include <ctype.h>
#include <stdio.h>
#include <string.h>

// determine la commande a executer
typedef enum {
  EXIT,
  NOT_FOUND,
  ECHO,
  TYPE,
} Keywords;

// Arguments recu de l'entree
typedef struct {
  char *argv[BUFSIZ];
  int argc;
} args;

// --- Les functions (Prototypes) ---
Keywords get_command(char *name);
char *echo(int argc, char *argv[]);
char *type(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Entree
  char raw_input[BUFSIZ];

  printf("$ ");
  while (fgets(raw_input, sizeof(raw_input), stdin)) {

    // Structure contenant les arguments dans l'entree
    args command;

    command.argv[0] = strdup("\0");

    // Chaine de charactere representant le mot courant
    char token[FILENAME_MAX];
    token[0] = '\0';
    int j = 0;

    // Parse (elimine les espaces pour recupere uniquement les mots)
    for (int i = 0, k = 0;
         raw_input[i] != '\0' && k < BUFSIZ && j < (FILENAME_MAX - 1); i++) {

      if (!isspace((unsigned char)raw_input[i])) {
        token[j] = raw_input[i];
        j++;
      } else {

        if (token[0] != '\0') {
          token[j] = '\0';
          command.argv[k] = strdup(token);
          k++;
        };

        command.argc = k;
        j = 0;
      };
    };

    if (command.argv[0] != NULL && command.argv[0][0] != '\0') {
      // Execute
      switch (get_command(command.argv[0])) {
      case EXIT:
        return 0;
      case NOT_FOUND:
        printf("%s: command not found\n", command.argv[0]);
        break;
      case ECHO:
        echo(command.argc, command.argv);
        break;
      case TYPE:
        type(command.argc, command.argv);
        break;
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
  if (strcmp(name, "echo") == 0)
    return ECHO;
  if (strcmp(name, "type") == 0)
    return TYPE;
  return NOT_FOUND;
};

/*
 * @brief affiche tour a tour les mots recu en arguments
 */
char *echo(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++)
    printf("%s ", argv[i]);
  printf("\n");
  return 0;
}

/*
 * @brief donne le type d'une commande
 */
char *type(int argc, char *argv[]) {
  if (argc <= 1)
    return 0;
  if (get_command(argv[1]) == NOT_FOUND) {
    printf("%s: not found\n", argv[1]);
  } else {
    printf("%s is a shell builtin\n", argv[1]);
  };
  return 0;
}
