/*
 * Copy this function template to construct either a DAWG or a trie
 * based on the dictionary filename given
 *
 * Don't forget to change the void return type of this function
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "errors.h"
#include <time.h>
#include "utils.h"
#include "../data/trie.h"
#include "../data/dawg.h"

/**
 * Creates a trie structure and stores a dictionnary
 */
void fill_trie(Trie trie, char* dict, enum language lang)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();

    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(dict, "r")) == NULL)
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

        // insert : word inside the Trie structure given as paramater
        insert_trie(trie, line, lang, 0);

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

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into trie in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        raler("fprintf in fill_trie");
}

/**
 * Loading the dictionnarys inside
 */
void construct_trie(Trie trie)
{
    // loading : dictionnary
    fill_trie(trie, "dict/german-wordlist.txt", DE);
    fill_trie(trie, "dict/english-wordlist.txt", EN);
    fill_trie(trie, "dict/french-wordlist.txt", FR);
}

/**
 * Creates a dawg structure and stores a dictionnary
 */
Dawg construct_dawg(char* dict)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* fp;
    clock_t start = clock();
    Dawg dawg = empty_dawg();

    // open : file given as paramater (i.e. a dictionnary)
    if ((fp = fopen(dict, "r")) == NULL)
        raler("fopen in construct_dawg");

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
        
        // insert : word inside the Dawg structure given as paramater
        insert_dawg(dawg, line);

        // reset errno var at 0
        errno = 0;
    }
    
    // if : error using getline
    if(errno != 0)
        raler("getline in construct_dawg");

    // free : line
    free(line);

    // minimiser to depth 0
    minimize(dawg, 0);

    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        raler("fclose in construct_dawg");

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into dawg in %f s.\n", dict, (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        raler("fprintf in construct_dawg");

    return dawg;
}
