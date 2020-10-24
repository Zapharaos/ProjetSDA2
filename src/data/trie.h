#ifndef _TRIE_H
#define _TRIE_H

#define ALPHABET_SIZE 26

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct trie* Trie;

typedef struct lang* Lang;

enum language {
	UNKNOWN,
	EN,
	FR,
	DE
};

Trie empty_trie();

void insert_word(Trie trie, const char* word, enum language lang, size_t index);

void free_trie(Trie trie);

void display(Trie trie);

Lang search_lang(Trie trie, const char* word, size_t index);

bool match_lang(Trie trie, const char* word, enum language lang, size_t index);


// LANG

Lang empty_lang();

void print_lang(Lang lang);

#endif // !_TRIE_H
