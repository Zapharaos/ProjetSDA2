#include "dawg.h"

Dawg empty_dawg()
{
	Dawg dawg = malloc(sizeof(struct dawg));
	dawg->id = 0; // unknown
	dawg->lang = 0;
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

		free_trie(dawg->neighbors[i]->from);
		free_trie(dawg->neighbors[i]->to);
	}
		
	if (dawg->lang != NULL)
		free(dawg->lang);
	
	free(dawg->neighbors);
	free(dawg);
}
