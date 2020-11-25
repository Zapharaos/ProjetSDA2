#include <stdio.h>
#include <errno.h>

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

void test_dawg(char* path, enum language lang)
{
    // init : main dawg
    Dawg dawg = construct_dawg(path);

    // init : empty dawg
    Dawg empty = empty_dawg();

    // init : sentence from file
    size_t n = 0;
    char** sentence = get_sentence_from_file(path, &n);

	// treat : sentence
    switch(lang){
        case EN:
            treat_dawg(dawg, empty, empty, sentence, n);
            break;
        case DE:
            treat_dawg(empty, dawg, empty, sentence, n);
            break;
        case FR:
            treat_dawg(empty, empty, dawg, sentence, n);
            break;
        default:
            treat_dawg(empty, empty, empty, sentence, n);
            break;
    }

	// free : sentence and dawg
    free_sentence(sentence);
    free_dawg(empty);
    free_dawg(dawg);
}

void time_insert(char* dict, char* file, enum language lang, int boolean)
{

    size_t max;

    switch(lang)
    {
        case EN:
            max = EN_NB_WORDS;
            print_msg("\nLanguage : english\n");
            break;
        case DE:
            max = DE_NB_WORDS;
            print_msg("\nLanguage : german\n");
            break;
        case FR:
            max = FR_NB_WORDS;
            print_msg("\nLanguage : french\n");
            break;
        default:
            max = 0;
            break;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE * fd;
    FILE * fp;

    if((fd = fopen(file, "w+")) == NULL)
        raler("fopen time_insert");

    double count = 0; // var to stock the amount of seconds

    for(size_t n = 10; n <= max; n*=2)
    {
        for(size_t i = 0; i < 10; i++)
        {

            Trie trie = empty_trie();
            Dawg dawg = empty_dawg();

            size_t j = 0;
            errno = 0;

            // open : file given as paramater (i.e. a dictionnary)
            if ((fp = fopen(dict, "r")) == NULL)
                raler("fopen in time_insert");

            while(j < n && (read = getline(&line, &len, fp)) != -1)
            {

                // remove newline
                size_t length = strlen(line);
                if ((length > 0) && (line[length - 1] == '\n'))
                {
                    line[length - 1] = '\0';
                }

                // parsing the word
                parse_word(line);

                clock_t start = clock(); // clock start

                if(boolean == 0)
                {
                    // insert : word inside the Trie structure given as paramater
                    insert_trie(trie, line, lang, 0);
                }
                else
                {
                    // insert : word inside the Dawg structure given as paramater
                    insert_dawg(dawg, line);
                }

                count += (double) (clock() -  start) / (double)CLOCKS_PER_SEC;

                // reset errno var at 0
                errno = 0;
                j++;
            }

            // if : error using getline
            if(errno != 0)
                raler("getline in time_insert");

            free_dawg(dawg);
            free_trie(trie);

            fclose(fp);
        }

        // average time in seconds
        if(fprintf(stdout, "%zu %f\n",n,count/10) < 0)
            raler("fprintf time_insert");
        if(fprintf(fd, "%zu %f\n",n,count/10) < 0)
            raler("fprintf time_insert");
        
        // resetting count at 0
        count = 0;
    }

    // free : line
    free(line);

    fclose(fd);
}

void time_search(char* dict, char* file, enum language lang, int boolean)
{
    
    size_t max;

    switch(lang)
    {
        case EN:
            max = EN_NB_WORDS;
            print_msg("\nLanguage : english\n");
            break;
        case DE:
            max = DE_NB_WORDS;
            print_msg("\nLanguage : german\n");
            break;
        case FR:
            max = FR_NB_WORDS;
            print_msg("\nLanguage : french\n");
            break;
        default:
            max = 0;
            break;
    }

    Trie trie = empty_trie();
    Dawg dawg = empty_dawg();

    if(boolean == 0)
        fill_trie(trie, dict, lang);
    else
        dawg = construct_dawg(dict);

    FILE * fd;
    if((fd = fopen(file, "w+")) == NULL)
        raler("fopen time_search");

    double count = 0; // var to stock the amount of seconds

    for(size_t n = 10; n <= 20971520; n*=2)
    {
        for(size_t i = 0; i < 10; i++)
        {
            char* word = get_random_line(dict, max);
            clock_t start = clock();

            for(size_t j = 0; j < n; j++)
            {
                if(boolean == 0) // Trie
                    search_trie(trie, word, 0);
                else // Dawg
                    word_exists(dawg->root, word, 0);
            }

            count += (double) (clock() -  start) / (double) CLOCKS_PER_SEC;
            free(word);
        }

        // average time in seconds
        if(fprintf(stdout, "%zu %f\n",n,count/10) < 0)
            raler("fprintf time_search");
        if(fprintf(fd, "%zu %f\n",n,count/10) < 0)
            raler("fprintf time_search");
        
        // resetting count at 0
        count = 0;
    }

    fclose(fd);

    free_trie(trie);
    free_dawg(dawg);
}