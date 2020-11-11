#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include "data/trie.h"
#include "utils/io.h"

int handle_args(int argc, char* argv[])
{

	if (argc <= 1)
		return 0;

    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("------------ Language detector help ------------");
        print_msg("Tips: type <make install> to use <ald> instead of <./ald>");
	    print_msg("Get sentence: ./ald -sentence <-trie,-dawg>");
	    print_msg("Test trie data structure: ./ald -trie");
		return 1;
    }

	if (strcmp(argv[1], "-sentence") == 0)
    {
        size_t n = 0;
	    char** sentence = get_sentence(&n);
        show_sentence(sentence,n);
        
	    if (strcmp(argv[2], "-trie") == 0)
        {
            Trie trie = empty_trie();

            fill_trie(trie, "dict/german-wordlist.txt", DE);
            fill_trie(trie, "dict/english-wordlist.txt", EN);
            fill_trie(trie, "dict/french-wordlist.txt", FR);
            
            int count[3] = {0,0,0};
            count_lang_trie(trie, sentence, &n, count);
            
            print_result(sentence_lang(count), count);
            
            free_trie(trie);
            free_sentence(sentence);
            return 1;
        }

        if (strcmp(argv[2], "-dawg") == 0)
        {
            //todo:
            free_sentence(sentence);
            return 1;
        }

        free_sentence(sentence);
		return 0;
    }
	
	print_err("Argument not found: type ./ald -help (or make help) to display help");
    return 0;
}

int main(int argc, char* argv[]) {

    if(handle_args(argc, argv) == 1)
    {
        return 0;
    }

    print_err("Options not found: type ./ald -help to display help");
	
    return 1;
}

/*
if (strcmp(argv[1], "-trie") == 0)
    {
        Trie trie = empty_trie();

        fill_trie(trie, "dict/german-wordlist.txt", DE);
		fill_trie(trie, "dict/english-wordlist.txt", EN);
        fill_trie(trie, "dict/french-wordlist.txt", FR);
		
		print_msg("");

        printf("Recherche du lang pour poisson: ");
        print_lang(search_lang_trie(trie, "poisson", 0));

        printf("Recherche du lang pour bouffon: ");
        print_lang(search_lang_trie(trie, "bouffon", 0));

        printf("Recherche du lang pour pomme: ");
        print_lang(search_lang_trie(trie, "pomme", 0));

        printf("Recherche du lang pour kartoffel: ");
        //print_lang(search_lang_trie(trie, "kartoffel", 0));

        printf("Recherche du lang pour eat: ");
        print_lang(search_lang_trie(trie, "eat", 0));

        printf("Recherche du lang pour notebook: ");
        print_lang(search_lang_trie(trie, "notebook", 0));
		
		free_trie(trie);
		return 1;
    }
    */
