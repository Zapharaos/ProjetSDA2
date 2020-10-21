#include "trie.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct trie
{
	Trie trie[ALPHABET_SIZE];
	enum lang lang;
};

// temp test
int main(int argc, char**argv)
{
	Trie trie = empty_trie();
	insert_word(trie, "bonjour", FR, 0);
	display(trie);
	free_trie(trie);
}

Trie empty_trie()
{
	Trie trie = malloc(sizeof(Trie));
	trie->lang = UNKNOWN;
	return trie;
}

void free_trie(Trie trie)
{
	if (trie == NULL)
		return;
	
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		free_trie(trie->trie[i]);
}

void display(Trie trie)
{
	if (trie == NULL) return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		printf("Trie %ld [%c] lang: %d\n", i, (char)i + 'a', trie->trie[i] == NULL ? -1 : trie->trie[i]->lang);
		display(trie->trie[i]);
	}
	
}

void insert_word(Trie trie, const char* word, enum lang lang, size_t index)
{

	const char element = word[index];

	if (element == '\0')
		return;

	// char - 97 == index

	const size_t i = element - 'a';

	if(trie->trie[i] == NULL)
		trie->trie[i] = empty_trie();

	trie->trie[i]->lang = word[index + 1] == '\0' ? lang : UNKNOWN;

	insert_word(trie, word, lang, index + 1);
	
}
