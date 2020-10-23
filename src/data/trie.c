#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

struct trie
{
	Trie* data;
	enum lang lang;
};

// temp test
//int main(int argc, char**argv)
//{
//	Trie trie = empty_trie();
//	insert_word(trie, "bonjour", FR, 0);
//	display(trie);
//	free_trie(trie);
//}

Trie empty_trie()
{
	Trie trie = malloc(sizeof(Trie));
	trie->lang = UNKNOWN;
	trie->data = malloc(sizeof(Trie) * ALPHABET_SIZE);
	return trie;
}

void free_trie(Trie trie)
{
	if (trie == NULL)
		return;
	
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		free_trie(trie->data[i]);
}

void display(Trie trie)
{
	if (trie == NULL) return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		printf("Trie %ld [%c] lang: %d\n", i, (char)i + 'a', trie->data[i] == NULL ? -1 : trie->data[i]->lang);
		display(trie->data[i]);
	}
	
}

void insert_word(Trie trie, const char* word, enum lang lang, size_t index)
{

	const char element = word[index];

	if (element == '\0')
		return;

	// char - 97 == index

	const size_t i = element - 'a';

	if(trie->data[i] == NULL)
		trie->data[i] = empty_trie();

	trie->data[i]->lang = word[index + 1] == '\0' ? lang : UNKNOWN;

	insert_word(trie->data[i], word, lang, index + 1);
	
}
