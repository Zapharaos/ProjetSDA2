#include <stdio.h>

#include "test.h"
#include "utils.h"
#include "errors.h"
#include "io.h"
#include "../data/trie.h"
#include "../data/dawg.h"

void test_trie(char* path, enum language lang)
{
    // init : trie 
    Trie trie = empty_trie();
    fill_trie(trie, path, lang);
    
    // init : sentence from file
    size_t n = 0;
    char** sentence = get_sentence_from_file(path, &n);

	// treat : sentence	
    treat_trie(trie, sentence, n);
    
    // free : sentence and trie
    free_sentence(sentence);
    free_trie(trie);
}

void test_dawg(char* path)
{
    // init : main dawg
    Dawg dawg = construct_dawg(path);

    // init : empty dawg
    Dawg empty = empty_dawg();

    // init : sentence from file
    size_t n = 0;
    char** sentence = get_sentence_from_file(path, &n);

	// treat : sentence	
    treat_dawg(dawg, empty, empty, sentence, n);

	// free : sentence and dawg
    free_sentence(sentence);
    free_dawg(empty);
    free_dawg(dawg);
}

void time_insert(char* dict, char* file, enum language lang)
{

    (void) dict;

    size_t max;

    switch(lang)
    {
        case EN:
            max = EN_NB_WORDS;
            break;
        case DE:
            max = DE_NB_WORDS;
            break;
        case FR:
            max = FR_NB_WORDS;
            break;
        default:
            max = 0;
            break;
    }

    FILE * fd;
    if((fd = fopen(file, "w+")) == NULL)
        raler("fopen time insert trie");

    // prepare : random number generator
    time_t t;
    srand((unsigned) time(&t));

    double count = 0; // var to stock the amount of seconds

    for(size_t n = 10; n <= max; n*=2)
    {
        for(size_t i = 0; i < 10; i++)
        {
            clock_t start = clock(); // clock start
            // insérer le mot
            count += (double) (clock() -  start) / CLOCKS_PER_SEC;
        }

        if(fprintf(fd, "%zu %f\n",n,count/10) < 0)
            raler("frprintf time insert trie");
        
        // resetting count at 0
        count = 0;
    }

    if (fclose(fd) == -1) // in case there is a mistake
        raler("close time insert trie");
}

void time_search(char* dict, char* file, enum language lang)
{

    (void) dict;
    
    size_t max;

    switch(lang)
    {
        case EN:
            max = EN_NB_WORDS;
            break;
        case DE:
            max = DE_NB_WORDS;
            break;
        case FR:
            max = FR_NB_WORDS;
            break;
        default:
            max = 0;
            break;
    }

    FILE * fd;
    if((fd = fopen(file, "w+")) == NULL)
        raler("fopen time insert trie");

    // prepare : random number generator
    time_t t;
    srand((unsigned) time(&t));

    double count = 0; // var to stock the amount of seconds

    for(size_t n = 10; n <= max; n*=2)
    {
        for(size_t i = 0; i < 10; i++)
        {
            clock_t start = clock(); // clock start
            // x = random number entre 1 et max
            // search word at line x in dict
            count += (double) (clock() -  start) / CLOCKS_PER_SEC;
        }

        if(fprintf(fd, "%zu %f\n",n,count/10) < 0)
            raler("frprintf time insert trie");
        
        // resetting count at 0
        count = 0;
    }

    if (fclose(fd) == -1) // in case there is a mistake
        raler("close time insert trie");
}