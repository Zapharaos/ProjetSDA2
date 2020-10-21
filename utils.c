#include "utils.h"

void to_lower(char* entry)
{

    for (size_t i = 0; entry[i] != '\0'; i++)
    {
        if (entry[i] < 'A' || entry[i] > 'Z')
	        continue;
    	
        entry[i] = (char) (entry[i] - ('A' - 'a'));
    }
}

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
    
    show_sentence(sentence, n);
    
    return sentence;
}

void show_sentence(char** sentence, size_t* n) {
    for(size_t i=0; i<(*n); i++)
        if(fprintf(stdout, "%s\n", sentence[i]) < 0)
            err_print();
}
