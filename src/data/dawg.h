#ifndef _DAWG_H
#define _DAWG_H

#define SERIALIZE_MAX_SIZE 512 // 1 + 26 * 8 + 26 ; où 8 est la longueur max d'une ID

#include "lang.h"
#include "stack.h"
#include "../utils/utils.h"
#include "hashmap.h"
#include <stddef.h>

typedef struct dawg* Dawg;
typedef struct node* Node;
typedef struct vertex* Vertex;

struct dawg {
	size_t current_node_index;
	char* last_word;
	struct stack *stack;
	struct hashmap_s hashmap;
	Node root;
};

struct node
{
	size_t id;
	bool is_word;
	Vertex* neighbors;
};

struct vertex
{
	char label;
	Node from; // sommet gauche
	Node to; // sommet droit
};

Dawg empty_dawg();

void minimize(Dawg dawg, size_t p);

void serialize(Node node, char* result);

void insert_dawg(Dawg dawg, char* word);

void free_dawg(Dawg dawg);

void display_dawg(Dawg dawg);

size_t search_prefix_length(char* word1, char* word2);

// Lang

Lang search_lang(Dawg dawg, const char* word, size_t index);

bool match_lang(Dawg dawg, const char* word, enum language lang, size_t index);

#endif // !_DAWG_H
