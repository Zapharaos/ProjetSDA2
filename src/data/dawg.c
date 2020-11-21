#include "dawg.h"
#include <stdlib.h>

/**
 * Creates an empty vertex structure
 */
Vertex empty_vertex(char label, Node from, Node to)
{
	// allocate memory for the structure
	Vertex vertex = malloc(sizeof(struct vertex));

	// init elements
	vertex->label = label;
	vertex->from = from;
	vertex->to = to;
	
	// returns the vertex
	return vertex;
}

/**
 * Creates an empty node structure
 */
Node empty_node(Dawg dawg)
{
	// allocate memory for the structure
	Node root = malloc(sizeof(struct node));

	// init elements
	root->id = dawg->current_node_index++;
	root->is_word = false;
	root->neighbors = malloc(sizeof(struct vertex) * ALPHABET_SIZE);

	// init the tab with null pointers (valgrind issue)
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
		root->neighbors[i] = NULL;

	// returns the node
	return root;
}

/**
 * Creates an empty dawg structure
 */
Dawg empty_dawg()
{
	// allocate memory for the structure
	Dawg dawg = malloc(sizeof(struct dawg));

	// init elements
	dawg->current_node_index = 0;
	dawg->last_word = malloc(WORD_MAX_SIZE);
	dawg->last_word[0] = '\0';
	dawg->stack = new_stack(1000000); // à voir plus tard
	hashmap_create(2, &dawg->hashmap);
	dawg->root = empty_node(dawg);

	// returns the dawg
	return dawg;
}

/**
 * Free a node structure
 */
void free_node(Node root)
{
	// if : node is empty
	if(root == NULL)
		return;

	// while vertex also has vertex
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if(root->neighbors[i] == NULL)
			continue;

		// free : vertex
		free_node(root->neighbors[i]->from);
		free_node(root->neighbors[i]->to);
		free(root->neighbors[i]);
	}
    
	// free : vertex
    free(root->neighbors);

	// free : node
	free(root);
}

/**
 * Free a dawg structure
 */
void free_dawg(Dawg dawg)
{
	// if : dawg is empty
	if (dawg == NULL)
		return;

	// free : char*
	free(dawg->last_word);

	// free : vertex (node)
	free_node(dawg->root);

	// free : hashmap
	hashmap_destroy(&dawg->hashmap);

	// free : stack
	free(dawg->stack->items);
	free(dawg->stack);

	// free : dawg
	free(dawg);
}

/**
 * Gets the size of the biggest common prefix of the words
 */
size_t search_prefix_length(char* word1, char* word2){

	// if : either one word is empty
    if(word1 == NULL || word2 == NULL)
        return 0;

	// from 0 to the shortest size
    size_t index = 0;
    size_t max = max(strlen(word1), strlen(word2));

	// increment the size
    while((index < max) && (word1[index] == word2[index]))
	{
    	index++;
	}

	// return size
	return index;
}

/**
 * Minimize a dawg structure to a given depth
 */
void minimize(Dawg dawg, size_t p)
{
	// while the stack's size is bigger than the given depth
	while(stack_size(dawg->stack) > p)
	{
		// pop the top of the stack
		Vertex a = (Vertex) stack_pop(dawg->stack);

		// get the peak
		char serialized[SERIALIZE_MAX_SIZE] = "";
		serialize(a->to, serialized);
		Node sommet = (Node) hashmap_get(&dawg->hashmap, serialized, p);

		// check if the peak is already in the hashmap
		if(sommet == HASHMAP_NULL)
		{
			// then we link it to the vertex
			a->from = sommet;
			continue;
		} 
		
		// else : we add it to the hashmap
		hashmap_put(&dawg->hashmap, serialized, strlen(serialized), a->to);
	}
}

/**
 * Inserts a word inside a dawg
 */
void insert_dawg(Dawg dawg, char* word)
{
	// Step 1 : size of biggest prefix between the new word and the last word inserted
	size_t n = dawg->last_word != 0 ? search_prefix_length(word, dawg->last_word) : 0;

	// Step 2 : minimize the dawg until depth n
	minimize(dawg, n);

	// Step 3 : add the suffix to the dawg, from root or from the last inserted
	Node found = stack_size(dawg->stack) == 0 ? dawg->root : ((Vertex)stack_peek(dawg->stack))->to;
	
	// from end of prefix : to end of word
	for (size_t i = n; i < strlen(word); i++)
	{
		// get ascii value of char at positon i inside the word
		size_t index = ascii_to_index(word[i]);

		// if : the letter doesnt exist yet
		if(found->neighbors[index] == NULL)
		{
			// creates a node and adds the letter to the stack
			Vertex vertex = empty_vertex(word[i], found, empty_node(dawg));
			found->neighbors[index] = vertex;
			found = vertex->from;
			stack_push(dawg->stack, vertex);

			continue;
		}

		// adds the letter to the stack
		stack_push(dawg->stack, found->neighbors[index]);
		found = found->neighbors[index]->to;
	}

	// Step 4 : the last peak is the end of the word
	found->is_word = true;
	
	// create last word
	if(snprintf(dawg->last_word, WORD_MAX_SIZE, "%s%s", word, "\0") < 0)
        perror("snprintf create last word");
}

void serialize(Node node, char* result)
{
	if(node == NULL)
		return;

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
}

/**
 * Checks if a word exists inside a dawg structure
 */
bool word_exists(Node node, const char* word, size_t index)
{
	printf("a");

	// if : node is empty
	if(node == NULL)
	{
		printf("\n");
		return false;
	}
	
	printf("b");

	// if : at the end of the word
	if(word[index] == '\0')
	{
		printf("\n");
		return node->is_word;
	}

	printf("c");

	// next node is at the index of the char (at word index)
	Vertex v = node->neighbors[ascii_to_index(word[index])];
	
	// if : vertex is empty
	if(v == NULL)
	{
		printf("\n");
		return false;
	}

	printf("%c => %ld\n", v->label, v->to->id);

	// recursiv call on the next node and next index
	return word_exists(v->to, word, index+1);
}

/**
 * Displays a Node structure inside a dawg
 */
void display_node(Node node)
{

	printf("Node id: %ld (%s)\n", node->id, node->is_word ? "Oui" : "Non");
	
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		if(node->neighbors[i] == NULL)
			break;
		printf("%c : ", node->neighbors[i]->label);
		display_node(node->neighbors[i]->to);
	}

}