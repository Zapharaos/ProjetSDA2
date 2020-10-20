#include "utils.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strtok()

#define nb_word_max 64
#define SENTENCE_MAX_SIZE 256

 /**
  * \fn      void err_print()
  * \brief   Erreur avec la fonction bibliothèque fprintf
  */
void err_print() {
    perror("fprintf failed"); //exception use of perror
    exit(1);
}

 /**
  * \fn      void pas_content(char *message)
  * \brief   Erreur avec une fonction bibliothèque
  * \param   message Le message à afficher
  */
void pas_content(char *message) {
    if (fprintf(stderr, "%s", message) < 0)
        err_print();
    exit(1);
}

/**
 * \fn      char** get_sentence(size_t* n)
 * \brief   Retourne un tableau 2D de la phrase
 * \param   *n Le nombre de mots dans la phrase
 */
char** get_sentence(size_t* n) {
    
    char s[SENTENCE_MAX_SIZE] = "";
    const char * separators = " ,.?!\n"; // split at this chars
    
    if(fprintf(stdout, "Votre phrase : ") < 0)
        err_print();
    
    if(fgets(s, SENTENCE_MAX_SIZE, stdin) == NULL)
        pas_content("fgets sentence");
    
    char** sentence = (char**) malloc(sizeof(char*) * (*n)); // sizeof(char) = 1
    char* token = strtok(s, separators);
    
    do {
        to_lower(token);
        sentence[(*n)++] = token;
    } while ((token = strtok(NULL, separators)) != NULL );

    return sentence;
}

int main(int argc, char* argv[]) {
    
    if(argc != 1) {}
    
    size_t n = 0; // number of words
    char** sentence = get_sentence(&n); // 2D tab with the words
    
    for(size_t i=0; i<n; i++)
        if(fprintf(stdout, "%s\n", sentence[i]) < 0)
            err_print();
    
    return 0;
}
// --help
