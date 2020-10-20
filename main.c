#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strtok()

#define nb_word_max 64
#define sentence_max_size 256

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

char** get_sentence(size_t* n) {
    
    const char * separators = " ,.?!\n";
    char s[sentence_max_size] = "";
    
    fprintf(stdout, "Votre phrase : ");
    if(fgets(s, sentence_max_size, stdin) == NULL) {
        pas_content("fgets sentence");
    }
    
    char** sentence = malloc(sizeof(char) * 64);
    char * token = strtok (s, separators);
    do {
        sentence[(*n)++] = token;
    } while ( (token = strtok (NULL, separators)) != NULL );
    
    return sentence;
}

int main(int argc, char* argv[]) {
    
    if(argc != 1) {}
    
    size_t n = 0;
    char** sentence = get_sentence(&n);
    
    for(size_t i=0; i<n; i++)
        printf("%s\n",sentence[i]);


    
    return 0;
}
// --help
