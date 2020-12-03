#include <stdlib.h>

#include "dawg.h"
#include "../utils/utils.h"
#include "../utils/errors.h"

/**
 * Creates an empty edge structure
 */
Edge empty_edge(char label, Node from, Node to)
{
	// allocate memory for the structure
	Edge edge = malloc(sizeof(struct edge));

	// if : malloc failed
	if(edge == NULL)
		raler("malloc empty_vertex");

	// init elements
	edge->label = label;
	edge->from = from;
	edge->to = to;
	
	// returns the edge
	return edge;
}

/**
 * Creates an empty node structure
 */
Node empty_node(Dawg dawg)
{
	// allocate memory for the structure
	Node root = malloc(sizeof(struct node));

	// if : malloc failed
	if(root == NULL)
		raler("malloc empty_node");

	// init elements
	root->id = dawg->current_node_index++;
	root->is_word = false;

	// init the tab with null pointers (valgrind issue)
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		root->edges[i] = NULL;

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

	// if : malloc failed
	if(dawg == NULL)
		raler("malloc empty_dawg");

	// init elements
	dawg->current_node_index = 0;
	dawg->last_word = malloc(WORD_MAX_SIZE);

	// if : malloc failed
	if(dawg->last_word == NULL)
		raler("malloc empty_dawg");

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
	
	struct hashmap_s hashmap;
	hashmap_create(2, &hashmap);
	
	rec_free_node(root, &hashmap);

	hashmap_destroy(&hashmap);
}

void rec_free_node(Node node, struct hashmap_s* const hashmap)
{
		// if : node is empty
	if(node == NULL)
		return;

	char nb_str[16]; // on suppose que l'uid + char ne sera jamais plus grand que 16
	if(sprintf(nb_str, "%ld", node->id) < 0)
		raler("snprintf rec_free_node");

	//printf("Str: %s ; len : %ld\n", nb_str, strlen(nb_str));

	if(hashmap_get(hashmap, nb_str, strlen(nb_str)) != HASHMAP_NULL)
		return;

	hashmap_put(hashmap, nb_str, strlen(nb_str), 0);

	// while edge also has edge
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if(node->edges[i] == NULL)
			continue;

		// free : edge
		rec_free_node(node->edges[i]->to, hashmap);
		free(node->edges[i]);
	}
    
	// free : node
	free(node);

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

	// free : edge (node)
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
size_t search_prefix_length(char* word1, char* word2)
{

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
void minimize(Dawg dawg, int p)
{

	// printf("Minimize to %d\n", p);
	// while the stack's size is bigger than the given depth
	while(stack_size(dawg->stack) > p)
	{
		// pop the top of the stack
		Edge a = (Edge) stack_pop(dawg->stack);
		
		// get the peak
		char serialized[SERIALIZE_MAX_SIZE] = "";
		serialize(a->to, serialized);

		size_t tt = strlen(serialized) + 1;
		char* test = malloc(tt);

		snprintf(test, tt, "%s", serialized);

		//strncpy(test, serialized, strlen(serialized) + 1);

	//	printf("Searching ('%c'->to) %s (%ld) in hashmap... ", a->label, test, tt);
		
		Node sommet = (Node) hashmap_get(&dawg->hashmap, test, tt);
		
	//	printf("%s!\n", sommet != HASHMAP_NULL ? "Found" : "Not found");
	//	printf("==> 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >> %s\n", HASHMAP_NULL != hashmap_get(&dawg->hashmap, "1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0", strlen("1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")) ? "Found" :"Not found");
	//	printf("==> 1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;s4;0;0;0;0;0;0;0 >> %s\n", HASHMAP_NULL != hashmap_get(&dawg->hashmap, "1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;s4;0;0;0;0;0;0;0", strlen("1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;s4;0;0;0;0;0;0;0")) ? "Found" :"Not found");
	//	printf("==> 0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;t3;0;0;0;0;0;0 >> %s\n", HASHMAP_NULL != hashmap_get(&dawg->hashmap, "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;t3;0;0;0;0;0;0", strlen("0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;t3;0;0;0;0;0;0")) ? "Found" :"Not found");

		// check if the peak is already in the hashmap
		if(sommet != HASHMAP_NULL)
		{
			/**
			 *  FREE NODE TO
			 */
				/**/
				/*
			for (size_t i = 0; i < ALPHABET_SIZE; i++)
			{
				if(a->to->edges[i] == NULL)
					continue;

				// free : edge
				//free_node(a->to->edges[i]->to);
				free(a->to->edges[i]);
			}
			
			// free : node
			free(a->to);  */

			char sss[SERIALIZE_MAX_SIZE] = "";
			serialize(sommet, sss);

	//		printf("%s (%ld), matches with %s (%ld)\n", serialized, strlen(serialized), sss, strlen(sss));

	//		printf("(%c) Connecting %ld to %ld (%s)\n", a->label, a->from->id, sommet->id, serialized);

			a->to = sommet;
			continue;
		}

		// printf("ADDING %s\n", test);
		
		// else : we add it to the hashmap
		hashmap_put(&dawg->hashmap, test, tt, a->to);

		free(test);
	}
}

/**
 * Inserts a word inside a dawg
 */
void insert_dawg(Dawg dawg, char* word)
{

//	printf("Inserting %s: ", word);

//	for (size_t i = 0; i < (size_t)stack_size(dawg->stack); i++)
//		printf("%c ", ((Edge)dawg->stack->items[i])->label);

//	printf("\n");

	// Step 1 : size of biggest prefix between the new word and the last word inserted
	size_t n = dawg->last_word != 0 ? search_prefix_length(word, dawg->last_word) : 0;
	
	// Step 2 : minimize the dawg until depth n
	minimize(dawg, n);

	// printf("After min: ");

	// for (size_t i = 0; i < (size_t)stack_size(dawg->stack); i++)
	// 	printf("%c ", ((Edge)dawg->stack->items[i])->label);

	//printf("\n\n");

	// Step 3 : add the suffix to the dawg, from root or from the last inserted
	Node found = stack_size(dawg->stack) == 0 ? dawg->root : ((Edge)stack_peek(dawg->stack))->to;
	
	// from end of prefix : to end of word
	for (size_t i = n; i < strlen(word); i++)
	{
		// get ascii value of char at positon i inside the word
		size_t index = ascii_to_index(word[i]);

		Edge edge = empty_edge(word[i], found, empty_node(dawg));
		found->edges[index] = edge;
		found = edge->to;
		stack_push(dawg->stack, edge);
	}

	// Step 4 : the last peak is the end of the word
	found->is_word = true;

	// create last word
	if(snprintf(dawg->last_word, WORD_MAX_SIZE, "%s%s", word, "\0") < 0)
        raler("snprintf insert_dawg");

}

size_t serialize(Node node, char* result)
{
	if(node == NULL)
		return -1;

	size_t index = 0;
	result[index++] = node->is_word ? '1' : '0';

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		Edge edge = node->edges[i];
		result[index++] = ',';

		if(edge == NULL || edge->to == NULL)
		{
			result[index++] = '0';
			continue;
		}	

		char nb_str[16]; // on suppose que l'uid + char ne sera jamais plus grand que 16
		if(sprintf(nb_str, "%c%ld", edge->label, edge->to->id) < 0)
			raler("snprintf serialize");

		for (size_t j = 0; j < 16; j++)
		{
			if(nb_str[j] == '\0')
				break;
			result[index++] = nb_str[j];
		}

	}

	result[index++] = '\0';

	return index;

}

/**
 * Displays a Node structure inside a dawg
 */
void display_node(Node node)
{

	if(fprintf(stdout, "Node id: %ld (%s)\n", node->id, node->is_word ? "Oui" : "Non") < 0)
		raler("fprintf display_node");

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		if(node->edges[i] == NULL)
			continue;
		if(fprintf(stdout, "Edge: %c\n", node->edges[i]->label) < 0)
			raler("fprintf display_node");
	}

	printf("\n");
	
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		if(node->edges[i] == NULL)
			continue;
	//	if(fprintf(stdout, "%c : ", node->edges[i]->label) < 0)
	//		raler("fprintf display_node");
		display_node(node->edges[i]->to);
	}

}

/**
 * Checks if a word exists inside a dawg structure
 */
bool word_exists(Node node, const char* word, size_t index)
{
	// if : node is empty
	if(node == NULL)
		return false;
	
	// if : at the end of the word
	if(word[index] == '\0')
		return node->is_word;

	// next node is at the index of the char (at word index)
	Edge v = node->edges[ascii_to_index(word[index])];
	
	// if : edge is empty
	// recursiv call on the next node and next index
	return v == NULL ? false : word_exists(v->to, word, index+1);
}

/**
 * Treats a sentence
 */
void treat_dawg(Dawg en, Dawg de, Dawg fr, char** sentence, size_t n)
{
	clock_t start = clock(); // clock start

	// count how many times a word exists in each dictionnary
	int count[3] = {0,0,0};

	for(size_t i = 0; i < n; i++)
	{
		if(word_exists(fr->root, sentence[i], 0))
			count[0]++;
		if(word_exists(de->root, sentence[i], 0))
			count[1]++;
		if(word_exists(en->root, sentence[i], 0))
			count[2]++;
	}

	// print : how many words per language + detection result
   char* result = sentence_lang(count);
    if(fprintf(stdout,"\n%d word(s) in french.\n", count[0]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"%d word(s) in german.\n", count[1]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"%d word(s) in english.\n", count[2]) < 0)
		raler("fprintf treat_trie");
    if(fprintf(stdout,"\nMain language is : %s.\n", result) < 0)
		raler("fprintf treat_trie");

	// print : time needed to treat the sentence
    if (fprintf(stdout, "It took %f seconds to treat this sentence\n", (double)(clock() - start) / (double)CLOCKS_PER_SEC) < 0)
        raler("fprintf treat_trie");
}

/**
 *  Starts the langue detector using the Dawg structure
 */
void start_dawg(Dawg en, Dawg de, Dawg fr)
{
	// init : sentence entered by user
    size_t n = 0;
    char** sentence = get_sentence(&n);

	// treat : sentence	
    treat_dawg(en, de, fr, sentence, n);

	// free : sentence
    free_sentence(sentence);

	print_msg("\nType y to restart (anything else will end the programm) :");

    if (getchar() == 'y')
	{
        // issue : in fgets due to \n character after using getchar
        int c;
        while ( (c = getchar()) != EOF && c != '\n') {}

        // start : re starting
        print_msg("\nStarting again...");
        start_dawg(en, de, fr);
    }
	else
	{
		print_msg("\nEnd of program. Ending here.");
	}
}