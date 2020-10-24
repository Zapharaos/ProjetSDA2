#ifndef _IO_H
#define _IO_H
#include "../data/trie.h"

void fill_trie(Trie trie, char* dict, enum language lang);

void construct_dawg(char* dict);

#endif
