#ifndef _DAWG_H
#define _DAWG_H

#include "lang.h"
#include "stack.h"
#include "hashmap.h"
#include <stddef.h>

typedef struct dawg* Dawg;
typedef struct vertex* Vertex;

struct dawg
{
	size_t id;
	bool is_word;
	Vertex* neighbors;
};

struct vertex
{
	char label;
	Dawg from; // sommet gauche
	Dawg to; // sommet droit
};

Dawg empty_dawg();

void minimiser(Dawg dawg, struct stack *stack, struct hashmap_s *hashmap, size_t p);

void insert_dawg(Dawg dawg, const char* word);

void free_dawg(Dawg dawg);

void display_dawg(Dawg dawg);

// Lang

Lang search_lang(Dawg dawg, const char* word, size_t index);

bool match_lang(Dawg dawg, const char* word, enum language lang, size_t index);

#endif // !_DAWG_H
