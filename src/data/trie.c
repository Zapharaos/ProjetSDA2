#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "../utils/utils.h"
#include "../utils/errors.h"

Trie empty_trie()
{
	Trie trie = malloc(sizeof(struct trie));
	trie->lang = 0; // unknown
	trie->data = malloc(sizeof(struct trie) * ALPHABET_SIZE);

	// on initialise le tableau avec des pointeurs nuls
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		trie->data[i] = NULL;
	
	return trie;
}

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

void display_trie(Trie trie)
{
	if (trie == NULL) return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		//printf("Trie %ld [%c] lang: %d\n", i, (char)i + 'a', trie->data[i] == NULL ? -1 : trie->data[i]->lang);
		display_trie(trie->data[i]);
	}
	
}

Lang search_lang_trie(Trie trie, const char* word, size_t index)
{

	//printf("Index: %d | Lang : %d | Character: %c | C+1: %c\n", index, trie == NULL ? -1 : trie->lang, word[index], word[index + 1] == '\0' ? 'Z' : word[index+1]);

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


bool match_lang_trie(Trie trie, const char* word, enum language lang, size_t index)
{
	Lang f_lang = search_lang_trie(trie, word, index);

	if (f_lang == NULL)
		return UNKNOWN;

	switch (lang)
	{
		case EN:
			return f_lang->en;

		case FR:
			return f_lang->fr;

		case DE:
			return f_lang->de;
			
		default:
			return false;
	}
	
}

void insert_word(Trie trie, const char* word, enum language lang, const size_t index)
{
	const char element = word[index];

	if (element == '\0')
		return;

	// char - 97 == index

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
		
	insert_word(trie->data[i], word, lang, index + 1);
	
}

void count_lang_trie(Trie trie, char** sentence, const size_t* n, int count[]) {
	for(size_t i = 0; i < *n; i++) {
        Lang word = search_lang_trie(trie, sentence[i], 0);
        if(word->fr)
            count[0]++;
        if(word->de)
            count[1]++;
        if(word->en)
            count[2]++;
    }
}
