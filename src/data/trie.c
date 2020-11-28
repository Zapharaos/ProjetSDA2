#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "trie.h"
#include "../utils/utils.h"
#include "../utils/errors.h"

/**
 * Creates an empty Trie structure
 */
Trie empty_trie()
{
	// allocate memory for the structure
	Trie trie = malloc(sizeof(struct trie));

	// if : malloc failed
	if(trie == NULL)
		raler("malloc in empty_trie");

	// init elements
	//trie->lang = 0; // unknown

	// allocate memory for the structure
	trie->data = malloc(sizeof(struct trie) * ALPHABET_SIZE);

	// if : malloc failed
	if(trie->data == NULL)
		raler("malloc in empty_trie");

	// init : array with null pointer
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		trie->data[i] = NULL;
	
	// returns the trie
	return trie;
}

/**
 * Free a Trie structure
 */
void free_trie(Trie trie)
{
	// if : trie is empty
	if (trie == NULL)
		return;

	// free each childs
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		free_trie(trie->data[i]);

	// free : lang if not empty
//	if (trie->lang != NULL)
//		free(trie->lang);
		
	// free : data
	free(trie->data);

	// free : trie
	free(trie);
}

/**
 * Displays a Trie structure
 */
void display_trie(Trie trie)
{
	// if : trie is empty
	if (trie == NULL) return;

	// from 0 to 26
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		if(fprintf(stdout, "[%c] %d\n", (char)i + 'a', trie->data[i] == NULL ? -1 : 0) < 0)
			raler("fprintf in display_trie");
		// keep displaying with recursivity
		display_trie(trie->data[i]);
	}
}

/**
 *  Inserts a word inside a Trie structure
 */
void insert_trie(Trie trie, const char* word, enum language lang, const size_t index)
{
	// place at position index inside word
	const char element = word[index];

	// if : end of word
	if (element == '\0')
		return;

	// get ascii value of element
	const size_t i = ascii_to_index(element);

	// if the letter doesnt exists yet
	if(trie->data[i] == NULL)
		trie->data[i] = empty_trie();

	// if next index is the end of the word
	if(word[index+1] == '\0')
	{
		//if (trie->data[i]->lang == '0')
		//	trie->data[i]->lang = empty_lang();

		// set language of the word
		switch (lang)
		{
			case EN:
				trie->data[i]->en = 1;
				break;
			case FR:
				trie->data[i]->fr = 1;
				break;
			case DE:
				trie->data[i]->de = 1;
				break;
			default:
				break;
		}
		
	}

	// recursive call
	insert_trie(trie->data[i], word, lang, index + 1);
}

/**
 * Searchs the language of a word
 */
Trie search_trie(Trie trie, const char* word, size_t index)
{
	// if : trie is empty
	if (trie == NULL)
		return 0;

	// if : end of the word
	if (word[index] == '\0')
		return trie;

	// else if char isnt a letter
	if (word[index] < 97 || word[index] > 122)
	{
		if(fprintf(stdout, "Invalid char: %d\n", word[index]) < 0 )
			raler("fprintf search_trie");
		exit(1);
	}
	
	// recursive call
	return search_trie(trie->data[ascii_to_index(word[index])], word, index + 1);
}

/**
 * Count how many times a language is used inside a sentence
 */
void count_trie(Trie trie, char** sentence, const size_t n, int count[])
{
	// from 0 to number of words inside the sentence
	for(size_t i = 0; i < n; i++)
	{
		// get the language of the word at position i inside the sentence
        Trie t = search_trie(trie, sentence[i], 0);

		// if : unknown
		if(t == NULL) continue;

		// else : increment its value
        if(t->fr == 1)
            count[0]++;
        if(t->de == 1)
            count[1]++;
        if(t->en == 1)
            count[2]++;
    }
}

/**
 * Treats a sentence
 */
void treat_trie(Trie trie, char** sentence, size_t n)
{
	clock_t start = clock(); // clock start
    
    // count : how many words per language in the sentence
    int count[3] = {0,0,0};
    count_trie(trie, sentence, n, count);
    
    // print : how many words per language + detection result
    char* result = sentence_lang(count);
    if(fprintf(stdout,"\n%d word(s) in french.\n", count[0]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"%d word(s) in german.\n", count[1]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"%d word(s) in english.\n", count[2]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"\nMain language is : %s.\n", result) < 0)
		raler("fprintf treat_trie");
    
    // print : time needed to treat the sentence
    if (fprintf(stdout, "It took %f seconds to treat this sentence\n", (double)(clock() - start) / CLOCKS_PER_SEC) < 0)
        raler("fprintf treat_trie");
}

/**
 * start the langue detector using the Trie structure
 */
void start_trie(Trie trie)
{

    // init : sentence entered by user
    size_t n = 0;
    char** sentence = get_sentence(&n);

	// treat : sentence	
    treat_trie(trie, sentence, n);
    
    // free : sentence
    free_sentence(sentence);

    print_msg("\nType y to restart (anything else will end the programm) :");

    if (getchar() == 'y')
	{
        // issue : in fgets due to \n character after using getchar
        int c;
        while ( (c = getchar()) != EOF && c != '\n') {}

        // start : re starting
        print_msg("\nStarting again...");
        start_trie(trie);
    }
	else
	{
		print_msg("\nEnd of program. Ending here.");
	}
}
