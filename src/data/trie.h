#ifndef _TRIE_H
#define _TRIE_H

#define ALPHABET_SIZE 26

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct trie* Trie;

typedef struct lang* Lang;

struct lang
{
    bool fr;
    bool de;
    bool en;
};

struct trie
{
    Trie* data;
    Lang lang;
};

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

void count_lang(Trie trie, char** sentence, size_t* n, int count[]);

#endif // !_TRIE_H
