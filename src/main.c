#include <string.h>
#include <stdio.h>
#include "utils/errors.h"
#include "utils/utils.h"
#include "data/trie.h"


int handle_args(int argc, char* argv[])
{

	if (argc <= 1)
		return 0;

    if (strcmp(argv[1], "-help") == 0)
    {
	    print_msg("------------ Language detector help ------------");
	    print_msg("Get sentence: ./lg -sentence <-trie,-dawg>");
	    print_msg("Test trie data structure: ./lg -trie");
		return 1;
    }

	if (strcmp(argv[1], "-sentence") == 0)
    {
	    size_t n = 0; // number of words
	    char** sentence = get_sentence(&n);

	    if (argc <= 2)
	    {
			free(sentence);
			return 1;
	    }

	    if (strcmp(argv[2], "-trie") == 0)
	    {
	    	//todo:
			return 0;
	    }

		if (strcmp(argv[2], "dawg") == 0)
	    {
			//todo:
			return 0;
	    }

		return 0;

    }

	if (strcmp(argv[1], "-trie") == 0)
    {
	    Trie trie = empty_trie();
	    insert_word(trie, "bonjour", FR, 0);
	    display(trie);
	    free_trie(trie);
		return 1;
    }
	
	print_err("Argument not found: type ./lg -help to display help");

    return 0;
}

int main(int argc, char* argv[]) {

    if(handle_args(argc, argv) == 1)
    {
        return 0;
    }

    print_err("Options not found: type ./lg -help to display help");
	
    return 1;
}
// --help
