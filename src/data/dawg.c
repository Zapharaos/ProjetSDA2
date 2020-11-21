#include "dawg.h"
#include <stdlib.h>

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
    size_t max = strlen(word1) > strlen(word2) ? strlen(word2) : strlen(word1);

    while((index < max) && (word1[index] == word2[index])){
    	index++;
	}

	return index;
}

/* TANT QUE la taille de la pile est supérieure à p
	FAIRE : Dépiler la pile, l’arête dépilée sera nommée a.
		Vérifier si un sommet équivalent au sommet droit de l’arête a est déjà présent dans la hashmap.
    	SI c’est le cas
    		ALORS : Relier le sommet gauche de l’arête a à ce sommet
    	SINON
			Enregistrer ce sommet dans la hashmap. FIN SI
	FIN TANT QUE */
void minimiser(Dawg dawg, size_t p){
	while(stack_size(dawg->stack) > p){
		void *a = stack_peek(dawg->stack); // changer le type de a ?
		stack_pop(dawg->stack); 
		if(HASHMAP_NULL == hashmap_get(dawg->hashmap, "jesaispasquoimettre", p)) // changer key et p ?
			hashmap_remove(dawg->hashmap, "toujourspas", p); // changer key et p ?
		else
			hashmap_put(dawg->hashmap, "encore?mdr", p, a); // changer key et p ?
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
	// minimiser(dawg, n);
}