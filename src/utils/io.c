#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "utils.h"
#include "errors.h"
#include "test.h"
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
    if (fprintf(stdout, "Successfully loaded %s into trie in %f s.\n", dict, (double)(clock() - start) / (double)CLOCKS_PER_SEC) < 0)
        raler("fprintf in fill_trie");
}

/**
 * Loading the dictionnaries inside
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

    free_test(dawg);

    // close : file given as paramater (i.e. a dictionnary)
    if(fclose(fp) != 0)
        raler("fclose in construct_dawg");

    // print : success + time needed to load it
    if (fprintf(stdout, "Successfully loaded %s into dawg in %f s.\n", dict, (double)(clock() - start) /(double) CLOCKS_PER_SEC) < 0)
        raler("fprintf in construct_dawg");

    return dawg;
}

/**
 * Starts the program depending of the number and list of arguments
 */
int handle_args(char* argv[])
{

    // if : help
    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("--------------------- Language detector help ---------------------");
        print_msg("- Type <make list> to check out the list of possibilities");
	    print_msg("- Start : ./bin/ald -sentence <-trie,-dawg>");
        print_msg("\t Also : <make trie> or <make dawg>");
        print_msg("- Run the test : ./bin/ald -test");
        print_msg("\t Also : <make test>");
        print_msg("- Run the counting test : <make count>");
        print_msg("\t Also : ./bin/ald count <-trie,-dawg>");
        print_msg("- Run the perf test : <make perf>");
        print_msg("\t Also : ./bin/ald -perf <-trie,-dawg>");
        print_msg("------------------------------------------------------------------");

        // return : success
		return 0;
    }

    if(strcmp(argv[1], "-t") == 0)
    {

        Dawg t = construct_dawg("dict/french-wordlist.txt");

        printf("Display hashmap: \n");
        /*
        if (0 != hashmap_iterate_pairs(&t->hashmap, log_and_free_all, NULL)) {
            fprintf(stderr, "failed to deallocate hashmap entries\n");
        } */

        //display_node(t->root);

        free_dawg(t);

        return 0;
    }

    // if : sentence
	if (strcmp(argv[1], "-sentence") == 0)
    {
        
        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            print_msg("\nYou chose : Trie \n");

            Trie trie = empty_trie();
            construct_trie(trie);
            start_trie(trie);
    	    free_trie(trie);

            // return : success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            
            print_msg("\nYou chose : Dawg \n");

            Dawg en = construct_dawg("dict/english-wordlist.txt");
            Dawg de = construct_dawg("dict/german-wordlist.txt");
            Dawg fr = construct_dawg("dict/french-wordlist.txt");
            /*
            if (0 != hashmap_iterate_pairs(&fr->hashmap, log_and_free_all, NULL)) {
                fprintf(stderr, "failed to deallocate hashmap entries\n");
            } */

            printf("Taille dawg_en : %ld\n", dfs(en));
            printf("Taille dawg_de : %ld\n", dfs(de));
            printf("Taille dawg_fr : %ld\n", dfs(fr));

            start_dawg(en, de, fr);

            free_dawg(en);
            free_dawg(de);
            free_dawg(fr);

            // return success
            return 0;
        }

        // else : failed
    	print_error("Arguments not found: type ./bin/ald -help to display help");
		return 1;
    }

    // if : test
	if (strcmp(argv[1], "-test") == 0)
    {

        // Trie

        print_msg("\nLanguage : english - Trie : 274411");
        test_trie("dict/english-wordlist.txt", EN);

        print_msg("\nLanguage : german - Trie : 685620");
        test_trie("dict/german-wordlist.txt", DE);

        print_msg("\nLanguage : french - Trie : 336528");
        test_trie("dict/french-wordlist.txt", FR);

        // Dawg

        print_msg("\nLanguage : english - Dawg : 274411");
        test_dawg("dict/english-wordlist.txt");

        print_msg("\nLanguage : german - Dawg : 685620");
        test_dawg("dict/german-wordlist.txt");

        print_msg("\nLanguage : french - Dawg : 336528");
        test_dawg("dict/french-wordlist.txt");

        // return success
        return 0;
    }

    // if : count
    if (strcmp(argv[1], "-count") == 0)
    {

        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        { 
            print_msg("How many nodes in Trie : \n");

            Trie trie = empty_trie();

            fill_trie(trie, "dict/french-wordlist.txt", FR);
            print_msg("French should have : 623994");
            if (fprintf(stdout, "\tit has : %zu\n\n", count(trie)) < 0)
                raler("fprintf");

            free_trie(trie);
            trie = empty_trie();

            fill_trie(trie, "dict/german-wordlist.txt", DE);
            print_msg("German should have : 1229117");
            if (fprintf(stdout, "\tit has : %zu\n\n", count(trie)) < 0)
                raler("fprintf");

            free_trie(trie);
            trie = empty_trie();

            fill_trie(trie, "dict/english-wordlist.txt", EN);
            print_msg("English should have : 606879");
            if (fprintf(stdout, "\tit has : %zu\n\n", count(trie)) < 0)
                raler("fprintf");

            free_trie(trie);
            trie = empty_trie();
            construct_trie(trie);

            print_msg("All Trie together makes : 2 459 990");
            if (fprintf(stdout, "All Trie into a single Trie has : %zu\n", count(trie)) < 0)
                raler("fprintf");

            free_trie(trie);

            // return success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {

            print_msg("\nHow many nodes in Dawg : \n");

            // Dawg dawg = empty_dawg();
            // dawg = construct_dawg("dict/french-wordlist.txt");
            // print_msg("French should have : 34202");
            // if (fprintf(stdout, "\tit has : %zu\n\n", profondeur(dawg)) < 0)
            //     raler("fprintf");
            // free_dawg(dawg);

            // dawg = construct_dawg("dict/german-wordlist.txt");

            // print_msg("German should have : 146205");
            // if (fprintf(stdout, "\tit has : %zu\n\n", profondeur(dawg)) < 0)
            //     raler("fprintf");

            // free_dawg(dawg);
            // dawg = construct_dawg("dict/english-wordlist.txt");

            // print_msg("English should have : 80075");
            // if (fprintf(stdout, "\tit has : %zu\n\n", profondeur(dawg)) < 0)
            //     raler("fprintf");

            // free_dawg(dawg);

            // return success
            return 0;
        }

        // else : failed
    	print_error("Arguments not found: type ./bin/ald -help to display help");
		return 1;

    }

     // if : perf
	if (strcmp(argv[1], "-perf") == 0)
    {
        
        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            print_msg("\nInsert in Trie");

            time_insert("dict/english-wordlist.txt", "tests/times/insert/trie-en.txt", EN, 0);
            time_insert("dict/german-wordlist.txt", "tests/times/insert/trie-de.txt", DE, 0);
            time_insert("dict/french-wordlist.txt", "tests/times/insert/trie-fr.txt", FR, 0);

            print_msg("\nSearch in Trie");

            time_search("dict/english-wordlist.txt", "tests/times/search/trie-en.txt", EN, 0);
            time_search("dict/german-wordlist.txt", "tests/times/search/trie-de.txt", DE, 0);
            time_search("dict/french-wordlist.txt", "tests/times/search/trie-fr.txt", FR, 0);

            // return : success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            
            print_msg("\nInsert in Dawg");

            time_insert("dict/english-wordlist.txt", "tests/times/insert/dawg-en.txt", EN, 1);
            time_insert("dict/german-wordlist.txt", "tests/times/insert/dawg-de.txt", DE, 1);
            time_insert("dict/french-wordlist.txt", "tests/times/insert/dawg-fr.txt", FR, 1);

            print_msg("\nSearch in Dawg");

            time_search("dict/english-wordlist.txt", "tests/times/search/dawg-en.txt", EN, 1);
            time_search("dict/german-wordlist.txt", "tests/times/search/dawg-de.txt", DE, 1);
            time_search("dict/french-wordlist.txt", "tests/times/search/dawg-fr.txt", FR, 1);

            // return success
            return 0;
        }

        // else : failed
    	print_error("Arguments not found: type ./bin/ald -help to display help");
		return 1;
    }
	
    // else : failed
	print_error("Arguments not found: type ./bin/ald -help to display help");
    return 1;
}