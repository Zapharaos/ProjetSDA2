#include "dawg.h"
#include <stdlib.h>

Vertex empty_vertex(char label, Node from, Node to)
{
	Vertex vertex = malloc(sizeof(struct vertex));
	vertex->label = label;
	vertex->from = from;
	vertex->to = to;
	
	return vertex;
}

Node empty_node(Dawg dawg)
{
	Node root = malloc(sizeof(struct node));

	root->id = dawg->current_node_index++;
	root->is_word = false;
	root->neighbors = malloc(sizeof(struct vertex) * ALPHABET_SIZE);

	// on initialise le tableau avec des pointeurs nuls
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		root->neighbors[i] = NULL;

	return root;
}

void free_node(Node root)
{
	if(root == NULL)
		return;

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if(root->neighbors[i] == NULL)
			continue;

		free_node(root->neighbors[i]->from);
		free_node(root->neighbors[i]->to);
	}
    
    free(root->neighbors);
	free(root);
}

Dawg empty_dawg()
{
	Dawg dawg = malloc(sizeof(struct dawg));

	dawg->current_node_index = 0;
	dawg->last_word = malloc(sizeof(char) * WORD_MAX_SIZE);
	dawg->stack = new_stack(1000000); // à voir plus tard
	hashmap_create(2, &dawg->hashmap);
	dawg->root = empty_node(dawg);
	
	return dawg;
}

void free_dawg(Dawg dawg)
{
	if (dawg == NULL)
		return;

	free(dawg->last_word);
	// + free dawg->stack
	hashmap_destroy(&dawg->hashmap);
	free_node(dawg->root);

	free(dawg);
}

size_t search_prefix_length(char* word1, char* word2){

    if(word1 == NULL || word2 == NULL)
        return 0;

    size_t index = 0;
    size_t max = max(strlen(word1), strlen(word2));

	for (size_t i = 0; i < strlen(word1); i++)
	{
		/* code */
		printf("%c ", word1[i] == '\0' ? 'F' : word1[i]);
	}
	printf("\nSizeof word1: %ld\n", strlen(word1));
	
	for (size_t i = 0; i < strlen(word2); i++)
	{
		/* code */
		printf("%c ", word2[i] == '\0' ? 'F' : word2[i]);
	}
	printf("\nSizeof word2: %ld\n", strlen(word2));

	for (index = 0; index < max; index++)
		if(word1[index] != word2[index])
			return index;
	
	return index;
/*
    while((index < max) && (word1[index] == word2[index])){
    	index++;
	}

	return index; */
}

void minimize(Dawg dawg, size_t p)
{
	printf("Minimise a la hautueur: %ld\n", p);
	while(stack_size(dawg->stack) > p)
	{
		Vertex a = (Vertex) stack_pop(dawg->stack);
		char* serialized = serialize(a->to);
		Node sommet = (Node) hashmap_get(&dawg->hashmap, serialized, p);
		printf("while: %s\n", serialized);
		
		if(sommet == HASHMAP_NULL)
		{
			a->from = sommet;
			continue;
		} 
		
		// on insere 
		hashmap_put(&dawg->hashmap, serialized, strlen(serialized), a->to); // changer key et p ?
			
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
void insert_dawg(Dawg dawg, char* word)
{
	printf("Word: %s\n", word);
	printf("Lastword: %s\n", dawg->last_word == 0 ? "NULL" : dawg->last_word);
	// Etape 1
	size_t n = dawg->last_word != 0 ? search_prefix_length(word, dawg->last_word) : 0;
	printf("DAWG N: %ld\n", n);
	// Etape 2
	minimize(dawg, n);
	printf("2\n");
	// Etape 3
	Node found;

	if(stack_size(dawg->stack) == 0)
	{
		printf("avant dawg root\n");
		found = dawg->root;
		printf("apres dawg root\n");
	} else {
		printf("avant stack_peek\n");
		Vertex v = ((Vertex)stack_peek(dawg->stack));
		printf("V: %p\n", v);
		printf("V->from: %p\n", v->from);
		printf("V->to: %p\n", v->to);
		found = v->to;
		printf("apres stack_peek\n");
	}
	//Node found = stack_size(dawg->stack) == 0 ? dawg->root : ;
	printf("3\n");
	for (size_t i = n; i < strlen(word); i++)
	{
		size_t index = ascii_to_index(word[i]);

		if(found->neighbors[index] == NULL)
		{
			Vertex vertex = empty_vertex(word[i], found, empty_node(dawg));
			found->neighbors[index] = vertex;
			found = vertex->from;
			stack_push(dawg->stack, vertex);
			continue;
		}

		found = found->neighbors[index]->to;
		stack_push(dawg->stack, found->neighbors[index]);

	}

	found->is_word = true;
	
	dawg->last_word = word;

}

char* serialize(Node node)
{
	if(node == NULL)
		return 0;

	char* result = malloc(SERIALIZE_MAX_SIZE);
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