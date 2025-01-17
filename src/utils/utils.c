#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "utils.h"
#include "errors.h"

/**
 * Creates a sentence given by the user
 */
char** get_sentence(size_t* n)
{
    
    // print : sentence to user
    if(fprintf(stdout, "\nYour sentence :\n") < 0)
        raler("fprintf in get_sentence");
    
    // get : the sentence of his choice
    char s[SENTENCE_MAX_SIZE] = "";
    if(fgets(s, SENTENCE_MAX_SIZE, stdin) == NULL)
        raler("fgets in get_sentence");

    // prepare : variables for strtok_r
    char* save; 
    const char* separators = " ,.?!\n";

    char* token;
    if((token = strtok_r(s, separators, &save)) == NULL)
        raler("strtok_r in get_sentence");

    // init : double pointer char array
    char** sentence = init_sentence();

    // insert : the sentence in the array
    do {

        to_lower(token);
        if(snprintf(sentence[(*n)++], WORD_MAX_SIZE, "%s", token) < 0)
            raler("snprintf in get_sentence");
        
        errno = 0;

    } while ((token = strtok_r(NULL, separators, &save)) != NULL );
    
    if(errno != 0)
        raler("strtok_r in get_sentence");

    // return : sentence
    return sentence;
}

/**
 * Creates a sentence from a file
 */
char** get_sentence_from_file(char* path, size_t* n)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;

    // init : double pointer char array
    char** sentence = init_sentence();
    
    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(path, "r")) == NULL)
        raler("fopen in fill_trie");

    // reset errno var at 0
    errno = 0;

    // read : file given as paramater (i.e. a dictionnary)
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // remove newline
        size_t length = strlen(line);
        if ((length > 0) && (line[length - 1] == '\n'))
        {
            line[length - 1] = '\0';
        }

        // parsing the word
        parse_word(line);
        if(snprintf(sentence[(*n)++], WORD_MAX_SIZE, "%s", line) < 0)
            raler("snprintf in get_sentence");

        // reset errno var at 0
        errno = 0;
    }

    // if : error using getline
    if(errno != 0)
        raler("getline in fill_trie");

    // free : line
    free(line);
    
    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        raler("fclose in fill_trie");

    // print : sentence to user
    if(fprintf(stdout, "\nThe sentence is :\n") < 0)
        raler("fprintf in get_sentence_from_file");

    show_sentence(sentence, (*n));

    // return : sentence
    return sentence;
}

/**
 * Displays every words inside a given sentence
 */
void show_sentence(char** sentence, size_t n)
{
    // from 0 to size of the sentence
    for (size_t i = 0; i < (n); i++)
        print_msg(sentence[i]);
}

/**
 * Allocates memory to store a sentence
 */
char** init_sentence(void)
{
    // allocate memory for the structure
    char** sentence = malloc(sizeof(char*) * NB_WORD_MAX);

    // if : malloc failed
    if(sentence == NULL)
        raler("malloc in init_sentence");

    // from 0 to size max of a sentence
    for(size_t i=0; i < NB_WORD_MAX; ++i)
    {
        // allocate memory for the structure
        sentence[i] = malloc(sizeof(char) * WORD_MAX_SIZE);

        // if : malloc failed
        if(sentence[i] == NULL)
            raler("malloc in init_sentence");
    }

    // returns the structure
    return sentence;
}

/**
 * Free memory allocated to a double char array
 */
void free_sentence(char** sentence)
{ 
    for (int i = 0; i < NB_WORD_MAX; i++ )
        free(sentence[i]);
    free(sentence);
}

char* get_random_line(char* path, size_t max)
{
    // prepare : random number generator
    time_t t;
    srand((unsigned) time(&t));

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    size_t i = 0;
    size_t index = rand() % max;

    FILE* fd = fopen(path, "r");

    while ((read = getline(&line, &len, fd)) != -1)
    {
        if(i == index)
            break;
        i++;
    }
    
    fclose(fd);

    size_t length = strlen(line);
    if ((length > 0) && (line[length - 1] == '\n'))
    {
        line[length - 1] = '\0';
    }

    // parsing the word
    parse_word(line);

    

    return line;
}

/**
 * Transform every char in a string into lower cases
 */
void to_lower(char* entry)
{
    // go trough the whole string
    for (size_t i = 0; entry[i] != '\0'; i++)
    {
        // if the char isnt in caps
        if (entry[i] < 'A' || entry[i] > 'Z')
	        continue;
    	
        // if the car is in caps, we transform it into not caps
        entry[i] = (char) (entry[i] - ('A' - 'a'));
    }
}

/**
 * Change ASCII char (a-z) to array index
 * a -> 0, b -> 1, c -> 2, ..., z -> 25
 */
size_t ascii_to_index(char c)
{
    size_t index = (size_t)c;

    if (index < 97 || index > 122)
    {
        if (fprintf(stdout, "Invalid char: %d\n", c) < 0)
            raler("fprintf in ascii_to_index");
        print_error("ascii_to_index function can only read lowercase letter a-z.\n");
        exit(1);
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
    for (size_t i = 0; i < strlen(word); i++)
    {
        size_t index = (size_t)word[i];

        if (index < 97 || index > 122)
        {
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
        raler("malloc in concat");

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

/**
 * Search the biggest value in an array
 */
int array_max(int* lang)
{
    int k = 0, max = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (lang[i] > max)
        {
            max = lang[i];
            k = i+1;
        }
    }
    return k;
}

/**
 * Gives the language that has the biggest iterator
 */
char* sentence_lang(int count[])
{
    switch(array_max(count))
    {
        case 1:
            return "french";
        case 2:
            return "german";
        case 3:
            return "english";
        default:
            return "unknown (empty)";
    }
}