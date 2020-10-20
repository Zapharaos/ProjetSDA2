#ifndef _TRIE_H
#define _TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct trie* Trie;

enum lang {
	UNKNOWN,
	EN,
	FR,
	DE
};

/*
 * 
 */
Trie empty_trie();

void insert_sentence(Trie trie, const char* sentence, enum lang lang, size_t index);

void free_trie(Trie trie);

#endif // !_TRIE_H