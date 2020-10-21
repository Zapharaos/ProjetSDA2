#ifndef _TRIE_H
#define _TRIE_H

#define ALPHABET_SIZE 26

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

void insert_word(Trie trie, const char* word, enum lang lang, size_t index);

void free_trie(Trie trie);

void display(Trie trie);

#endif // !_TRIE_H
