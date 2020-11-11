#include "dawg.h"
#include <stdlib.h>

Dawg empty_dawg()
{
	Dawg dawg = malloc(sizeof(struct dawg));
	dawg->id = 0; // unknown
	dawg->is_word = false;
	dawg->neighbors = malloc(sizeof(struct vertex) * ALPHABET_SIZE);

	// on initialise le tableau avec des pointeurs nuls
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		dawg->neighbors[i] = NULL;
	
	return dawg;
}

void free_dawg(Dawg dawg)
{
	if (dawg == NULL)
		return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if(dawg->neighbors[i] == NULL)
			continue;

		free_dawg(dawg->neighbors[i]->from);
		free_dawg(dawg->neighbors[i]->to);
	}
		
	free(dawg->neighbors);
	free(dawg);
}

void insert_word(Dawg dawg, const char* word, enum language lang, size_t index)
{

}