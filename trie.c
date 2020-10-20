#include "trie.h"
#include <stdbool.h>
#include <stdlib.h>

struct trie
{
	Trie trie[26];
	enum lang lang;
};

// temp
int main(int argc, char**argv){}

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
	
	for (int i = 0; i < 26; ++i)
		free_trie(trie->trie[i]);
}

void insert_sentence(Trie trie, const char* sentence, enum lang lang, size_t index)
{

	const char element = sentence[index];

	if (element == '\0')
		return;

	// char - 97 == index

	size_t i = 'a' - element;

	if(trie->trie[i] == NULL)
		trie->trie[i] = empty_trie();

	trie->trie[i]->lang = sentence[index + 1] == '\0' ? lang : UNKNOWN;

	insert_sentence(trie, sentence, lang, index + 1);
	
}
