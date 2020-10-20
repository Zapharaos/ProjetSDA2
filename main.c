#include "utils.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strtok()

#define NB_WORD_MAX 64
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
    
    if(fprintf(stdout, "Votre phrase : ") < 0)
        err_print();
    
    char s[SENTENCE_MAX_SIZE] = "";
    if(fgets(s, SENTENCE_MAX_SIZE, stdin) == NULL)
        pas_content("fgets sentence");
    
    char *save; // to maintain context between successive calls that parse the same string
    const char * separators = " ,.?!\n"; // split at this chars
    char* token = strtok_r(s, separators, &save); // POSIX (strtok is not)
    
    char** sentence = (char**) malloc(sizeof(char*) * NB_WORD_MAX); // sizeof(char) = 1
    
    do {
        to_lower(token);
        sentence[(*n)++] = token; // each word
    } while ((token = strtok_r(NULL, separators, &save)) != NULL );
    
    return sentence;
}

int main(int argc, char* argv[]) {
    
    if(argc != 1) {}
    
    size_t n = 0; // number of words
    char** sentence = get_sentence(&n);
    
    for(size_t i=0; i<n; i++)
        if(fprintf(stdout, "%s\n", sentence[i]) < 0)
            err_print();
    
    return 0;
}
// --help
