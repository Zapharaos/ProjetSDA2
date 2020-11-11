#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "../utils/utils.h"
#include "../utils/errors.h"

/**
 * Creates an empty Trie structure
 */
Trie empty_trie()
{
	Trie trie = malloc(sizeof(struct trie));
	if(trie == NULL)
		print_err("malloc trie empty_trie");
	trie->lang = 0; // unknown
	trie->data = malloc(sizeof(struct trie) * ALPHABET_SIZE);
	if(trie->data == NULL)
		print_err("malloc trie->data empty_trie");

	// on initialise le tableau avec des pointeurs nuls
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		trie->data[i] = NULL;
	
	return trie;
}

/**
 * Free a Trie structure
 */
void free_trie(Trie trie)
{
	if (trie == NULL)
		return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		free_trie(trie->data[i]);

	if (trie->lang != NULL)
		free(trie->lang);
	free(trie->data);
	free(trie);
}

/**
 * Displays a Trie structure
 */
void display_trie(Trie trie)
{
	if (trie == NULL) return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		display_trie(trie->data[i]);
	}
}

/**
 *  Inserts a word inside a Trie structure
 */
void insert_word_trie(Trie trie, const char* word, enum language lang, const size_t index)
{
	const char element = word[index];

	if (element == '\0')
		return;

	const size_t i = ascii_to_index(element);

	if(trie->data[i] == NULL)
		trie->data[i] = empty_trie();

	if(word[index+1] == '\0')
	{
		if (trie->data[i]->lang == 0)
			trie->data[i]->lang = empty_lang();

		switch (lang)
		{
			case EN:
				trie->data[i]->lang->en = true;
				break;
			case FR:
				trie->data[i]->lang->fr = true;
				break;
			case DE:
				trie->data[i]->lang->de = true;
				break;
			default:
				break;
		}
		
	}

	insert_word_trie(trie->data[i], word, lang, index + 1);
}

/**
 * Searchs the language of a word
 */
Lang search_lang_trie(Trie trie, const char* word, size_t index)
{
	if (trie == NULL)
		return 0;

	if (word[index] == '\0')
		return trie->lang;

	if (word[index] < 97 || word[index] > 122) {
		printf("Invalid char: %d\n", word[index]);
		exit(1);
	}
	
	return search_lang_trie(trie->data[ascii_to_index(word[index])], word, index + 1);
}

/**
 * Count how many times a language is used inside a sentence
 */
void count_lang_trie(Trie trie, char** sentence, const size_t n, int count[]) {
	for(size_t i = 0; i < n; i++) {
        Lang word = search_lang_trie(trie, sentence[i], 0);
        if(word->fr)
            count[0]++;
        if(word->de)
            count[1]++;
        if(word->en)
            count[2]++;
    }
}
