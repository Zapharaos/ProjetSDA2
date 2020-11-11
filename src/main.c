#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include "data/trie.h"
#include "utils/io.h"

int handle_args(int argc, char* argv[])
{
    // if : too few arguments
    // return : failed
	if (argc <= 1)
		return 1;

    // if : help
    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("------------ Language detector help ------------");
        print_msg("Tips: type <make install> to use <ald> instead of <./ald>");
	    print_msg("Get sentence: ./ald -sentence <-trie,-dawg>");
	    print_msg("Test trie data structure: ./ald -trie");

        // return : success
		return 0;
    }

    // if : sentence
	if (strcmp(argv[1], "-sentence") == 0)
    {
        // init : sentence entered by user
        size_t n = 0;
	    char** sentence = get_sentence(&n);
        show_sentence(sentence,n);
        
        // if : trie
	    if (strcmp(argv[2], "-trie") == 0)
        {

            // init : new structure Trie
            Trie trie = empty_trie();

            // loading the dictionnarys inside the Trie structure
            fill_trie(trie, "dict/german-wordlist.txt", DE);
            fill_trie(trie, "dict/english-wordlist.txt", EN);
            fill_trie(trie, "dict/french-wordlist.txt", FR);
            
            // count : how many words per language in the sentence
            int count[3] = {0,0,0};
            count_lang_trie(trie, sentence, n, count);
            
            // print : how many words per language + detection result
            char* result = sentence_lang(count);
            fprintf(stdout,"Il y a %d mot(s) en français.\n", count[0]);
            fprintf(stdout,"Il y a %d mot(s) en allemand.\n", count[1]);
            fprintf(stdout,"Il y a %d mot(s) en anglais.\n", count[2]);
            fprintf(stdout,"\nLe langage principal est : %s.\n", result);
            
            // free : structure and sentence
            free_trie(trie);
            free_sentence(sentence);

            // return : success
            return 0;
        }

        // if : dawg
        if (strcmp(argv[2], "-dawg") == 0)
        {
            //todo :

            // free : structure and sentence
            free_sentence(sentence);

            // return success
            return 0;
        }

        // free : sentence
        free_sentence(sentence);

        // return : failed
		return 1;
    }
	
    // else : failed
	print_err("Argument not found: type ./ald -help to display help");

    // return : failed
    return 1;
}

int main(int argc, char* argv[]) {

    // if : checking the arguments
    if(handle_args(argc, argv) == 1)
    {
        // return : program success
        return 0;
    }

    // else : 

    // return : program failed
    print_err("Options not found: type ./ald -help to display help");
    return 1;
}
