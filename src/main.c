#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Entree
  char raw_input[BUFSIZ];

  puts(" Initialisation de la boucle");
  printf("$ ");
  while (fgets(raw_input, sizeof(raw_input), stdin)) {

    // Tableau contenant les mots dans l'entree
    char *command[BUFSIZ];
    int k = 0;

    // Chaine de charactere representant le mot courant
    char token[FILENAME_MAX];
    token[0] = '\0';
    int j = 0;

    puts("Command, token, j et k initialises");

    // Parse (elimine les espaces pour recupere uniquement les mots)
    for (int i = 0;
         raw_input[i] != '\0' && k < BUFSIZ && j < (FILENAME_MAX - 1); i++) {

      puts("=== Parsing ===");
      printf("Round %d\n", i);

      if (!isspace((unsigned char)raw_input[i])) {

        printf(" Symbole rencontree: %c\n", raw_input[i]);

        token[j] = raw_input[i];

        // ####################################
        printf("token : ");
        for (int idx = 0; idx < j; idx++) {
          printf("%c", token[idx]);
        }
        puts(" ");
        printf("j = %d\n", j);
        // ##################################

        j++;
      } else {

        puts("Espace rencontree");

        if (token[0] != '\0') {

          puts("Nouveau mot ajoutee a commande");

          token[j] = '\0';
          command[k] = strdup(token);
          k++;

          printf("k = %d\n", k);

          // #################
          printf(" commande = {");
          for (int idx = 0; idx < k; idx++) {
            printf("%s, ", command[idx]);
          }
          printf("}\n");
          // #######################
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
