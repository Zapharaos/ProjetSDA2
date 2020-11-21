#include "dawg.h"
#include <stdlib.h>
#include "utils.h"

Dawg empty_dawg()
{
	Dawg dawg = malloc(sizeof(struct dawg));

	dawg->root->id = 0; // unknown
	dawg->root->is_word = false;
	dawg->root->neighbors = malloc(sizeof(struct vertex) * ALPHABET_SIZE);
	
	// on initialise le tableau avec des pointeurs nuls
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		dawg->root->neighbors[i] = NULL;
	
	return dawg;
}

void free_dawg(Dawg dawg)
{
	if (dawg == NULL)
		return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if(dawg->root->neighbors[i] == NULL)
			continue;

		free_dawg(dawg->root->neighbors[i]->from);
		free_dawg(dawg->root->neighbors[i]->to);
	}
		
	free(dawg->root->neighbors);
	free(dawg);
}

size_t search_prefix_length(char* word1, char* word2){

    if(word1 == NULL || word2 == NULL)
        return 0;

    size_t index = 0;
    size_t max = max(strlen(word1), strlen(word2));

    while((index < max) && (word1[index] == word2[index])){
    	index++;
	}

	return index;
}

void minimize(Dawg dawg, size_t p)
{
	
	while(stack_size(dawg->stack) > p)
	{
		Vertex a = (Vertex) stack_pop(dawg->stack);
		char* serialized = serialize(a->to);
		Node sommet = (Node) hashmap_get(dawg->hashmap, serialized, p);
		
		if(sommet == HASHMAP_NULL)
		{
			a->from = sommet;
			continue;
		} 
		
		// on insere 
		hashmap_put(dawg->hashmap, serialized, strlen(serialized), a->to); // changer key et p ?
			
	}

}

/* trouver taille n du plus grand préfixe (commun)
	entre le dernier mot inséré et word */

	/* minimiser jusq'à profondeur n */

	/* ajouter suffixe (non commun) au graphe
	si (pile vide) : racine
	else  : sommet droit de dernière arete empilée */

	/* Pour chaque lettre du suffixe ajoutée au graphe, empiler l’arête correspondante.*/

	/* marquer le dernier sommet ajouté comme étant final */
void insert_dawg(Dawg dawg, const char* word)
{
	// Etape 1
	size_t n = dawg->last_word != 0 ? search_prefix_length(word, dawg->last_word) : 0;

	// Etape 2
	minimize(dawg, n);

	// Etape 3
	Node found = stack_size(dawg->stack) > 0 ? dawg->root : ((Vertex)stack_peek(dawg->stack))->to;
	
	for (size_t i = n; i < strlen(word); i++)
	{
		size_t index = ascii_to_index(word[i]);

		if(found->neighbors[index] == NULL)
		{
			Vertex vertex = malloc(sizeof(struct vertex));
			vertex->from = found;
			vertex->to = empty_node(dawg);
			vertex->label = word[i];
			found->neighbors[index] = vertex;
			found = vertex->from;
			stack_push(dawg->stack, vertex);
			continue;
		}

		found = found->neighbors[index]->to;
		stack_push(dawg->stack, found->neighbors[index]);

	}

	found->is_word = true;

}

char* serialize(Node node)
{
	if(node == NULL)
		return 0;

	char result[SERIALIZE_MAX_SIZE];
	size_t index = 0;
	result[index++] = node->is_word ? '1' : '0';

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		Vertex vertex = node->neighbors[i];
		if(vertex == NULL)
			continue;
		if(vertex->to == NULL)
			continue;
		result[index++] = ';';
				
		char nb_str[16]; // on suppose que l'uid ne sera jamais plus grand que 16
		sprintf(nb_str, "%ld", vertex->to->id);

		for (size_t j = 0; j < 16; j++)
		{
			if(nb_str[j] == '\0')
				break;
			result[index++] = nb_str[j];
		}

	}

	result[index] = '\0';

	return result;
}