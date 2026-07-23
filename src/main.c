#include "logger.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#ifdef _WIN32
#define PATH_LIST_SEPARATOR ';'
#else
#define PATH_LIST_SEPARATOR ':'
#endif

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
int type(int argc, char *argv[]);

int main(void) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Entree
  char raw_input[BUFSIZ];

  printf("$ ");
  while (fgets(raw_input, sizeof(raw_input), stdin)) {
    log_info("Input received");
    // Structure contenant les arguments dans l'entree
    args command;

    command.argv[0] = strdup("\0");

    // Chaine de charactere representant le mot courant
    char token[FILENAME_MAX];
    token[0] = '\0';
    int j = 0;

    // Parse (elimine les espaces pour recupere uniquement les mots)
    log_info("Parsing ...");
    for (int i = 0, k = 0;
         raw_input[i] != '\0' && k < BUFSIZ && j < (FILENAME_MAX - 1); i++) {

      if (!isspace((unsigned char)raw_input[i])) {
        log_info("token num°%d: %c", j, raw_input[i]);
        token[j] = raw_input[i];
        j++;
      } else {
        log_info("space detected");
        if (token[0] != '\0') {
          token[j] = '\0';
          command.argv[k] = strdup(token);
          log_success("Arg num°%d successfully parsed: %s", i, token);
          token[0] = '\0';
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
  log_success("Program successfully terminated");
  return 0;
}

/*
 * @brief get substring ss of length l starting
 * at index pos.
 * Parce strcpy() est insecure
 */
void getSub(char *s, char *ss, int pos, int l) {
  int i = 0;

  // Copy substring into ss
  while (i < l) {
    ss[i] = s[pos + i];
    i++;
  }

  // Null terminate the substring
  ss[i] = '\0';
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
int type(int argc, char *argv[]) {
  char *PATH = getenv("PATH");
  struct dirent *dir_descriptor;
  char entry[FILENAME_MAX];
  DIR *directory;
  int i = 1;
  int j = 0;

  if (argc <= 1) {
    printf("Insuficient number of arguments\n");
    return 1;
  };

  if (get_command(argv[1]) == NOT_FOUND && PATH != NULL) {

    // printf("Command is not buitins. Searching Path.\n");

    while (PATH[i] != '\0') {

      // printf("%d character encountered: %c\n", i, PATH[i]);

      if (PATH[i] == PATH_LIST_SEPARATOR) {
        getSub(PATH, entry, j, (i - j));

        // printf("New entry: %s\n", entry);

        // Ouvrir le dossier
        if ((directory = opendir(entry)) == NULL) {

          // printf("Can't open %s\n", entry);

          j = i + 1;
          i++;

          // printf("i = %d \n j = %d", i, j);

          continue;
        };

        // Itérer sur chaque fichier du dossier
        // Et vérifier s'il est égale a argv[1] et
        // est exécutable
        while ((dir_descriptor = readdir(directory)) != NULL) {
          char filename[FILENAME_MAX + 256];

          // Est-ce le fichier rechercher ?
          if (strcmp((dir_descriptor->d_name), argv[1]) != 0) {
            continue;
          };

          snprintf(filename, FILENAME_MAX + 256, "%s/%s", entry,
                   dir_descriptor->d_name);

          // Checks
          if (access(filename, F_OK | X_OK) == 0) {
            printf("%s is %s\n", argv[1], filename);

            return 0;
          };
        };
        j = i + 1;
      };
      i++;
    };
  } else {
    printf("%s is a shell builtin\n", argv[1]);
    return 0;
  };

  printf("%s: not found\n", argv[1]);
  return 0;
}
