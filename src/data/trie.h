#ifndef _TRIE_H
#define _TRIE_H

#include <stdlib.h>
#include "lang.h"

typedef struct trie* Trie;

struct trie
{
    Trie* data;
    Lang lang;
};

Trie empty_trie();

void insert_word(Trie trie, const char* word, enum language lang, size_t index);

void free_trie(Trie trie);

void display(Trie trie);

Lang search_lang_trie(Trie trie, const char* word, size_t index);

bool match_lang_trie(Trie trie, const char* word, enum language lang, size_t index);

// lang

void count_lang_trie(Trie trie, char** sentence, const size_t* n, int count[]);

#endif // !_TRIE_H
