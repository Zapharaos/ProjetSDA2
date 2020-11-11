#include "utils.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * Creates a sentence given by the user
 */
char** get_sentence(size_t* n) {
    
    // print : sentence to user
    if(fprintf(stdout, "Votre phrase : ") < 0)
        print_perr();
    
    // get : the sentence of his choice
    char s[SENTENCE_MAX_SIZE] = "";
    if(fgets(s, SENTENCE_MAX_SIZE, stdin) == NULL)
        print_err("fgets sentence");

    // prepare : variables for strtok_r
    char* save; 
    const char* separators = " ,.?!\n";

    char* token;
    if((token = strtok_r(s, separators, &save)) == NULL)
        print_err("token sentence empty");

    // init : double pointer char array
    char** sentence = initSentence();

    // insert : the sentence in the array
    do {
        to_lower(token);
        if(snprintf(sentence[(*n)++], WORD_MAX_SIZE, "%s", token) < 0)
            print_err("snprintf create sentence");
    } while ((token = strtok_r(NULL, separators, &save)) != NULL );
    
    // return : sentence
    return sentence;
}

/**
 * Displays every words inside a given sentence
 */
void show_sentence(char** sentence, size_t n) {
    for (size_t i = 0; i < (n); i++)
        print_msg(sentence[i]);
}

/**
 * Allocates memory to store a sentence
 */
char** initSentence(void){
    char** sentence = malloc(sizeof(char*) * NB_WORD_MAX);
    if(sentence == NULL)
        print_err("malloc initSentence");
    for(size_t i=0; i < NB_WORD_MAX; ++i) {
        sentence[i] = malloc(sizeof(char) * WORD_MAX_SIZE);
        if(sentence[i] == NULL)
            print_err("malloc initSentence");
    }
    return sentence;
}

/**
 * Free memory allocated to a double char array
 */
void free_sentence(char** sentence) { 
    for (int i = 0; i < NB_WORD_MAX; i++ )
        free(sentence[i]);
    free(sentence);
}

/**
 * Transform every char in a string into lower cases
 */
void to_lower(char* entry)
{
    for (size_t i = 0; entry[i] != '\0'; i++)
    {
        if (entry[i] < 'A' || entry[i] > 'Z')
	        continue;
    	
        entry[i] = (char) (entry[i] - ('A' - 'a'));
    }
}

/**
 * Change ASCII char (a-z) to array index
 * a -> 0, b -> 1, c -> 2, ..., z -> 25
 */
size_t ascii_to_index(char c) {
    size_t index = (size_t)c;

    if (index < 97 || index > 122) {
        printf("Invalid char: %d\n", c);
        perror("ascii_to_index function can only read lowercase letter a-z.\n");
        exit(EXIT_FAILURE);
    }

    return index - 97;
}

/**
 * Remove char from string at the given index
 */
void remove_char(char* word, size_t index) {
    memmove(&word[index], &word[index + 1], strlen(word) - index);
}

/**
 * Remove all char from given string that aren't a-z
 */
void parse_word(char* word) {
    for (size_t i = 0; i < strlen(word); i++) {
        size_t index = (size_t)word[i];
        if (index < 97 || index > 122) {
            remove_char(word, i);
        }
    }
}

/**
 * Concat two strings together
 */
char* concat(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if(result == NULL)
        print_err("malloc concat");
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/**
 * Search the biggest value in an array
 */
int max(int* lang)
{
    int k = 0, max = 0;
    for (int i = 0; i < 3; ++i){
        if (lang[i] > max) {
            max = lang[i];
            k = i;
        }
    }
    return k;
}

/**
 * Gives the language that has the biggest iterator
 */
char* sentence_lang(int count[]) {
    switch(max(count)) {
        case 0:
            return "french";
        case 1:
            return "german";
        default:
            return "english";
    }
}

