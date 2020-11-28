#ifndef _DAWG_H
#define _DAWG_H

#define SERIALIZE_MAX_SIZE 512 // 1 + 26 * 8 + 26 ; où 8 est la longueur max d'une ID

#include <time.h>
#include <stddef.h>

#include "lang.h"
#include "stack.h"
#include "hashmap.h"

typedef struct dawg* Dawg;
typedef struct node* Node;
typedef struct vertex* Vertex;

/** @struct dawg
 *  @brief This structure creates a dictionnary
 */
/** @var dawg::current_node_index
 *  Member 'current_node_index' contains the index of the last node
 */
/** @var dawg::last_word
 *  Member 'last_word' contains the last inserted word
 */
/** @var dawg::stack
 *  Member 'stack' contains a stack structure
 */
/** @var dawg::hashmap
 *  Member 'hashmap' contains a hashmap structure
 */
/** @var dawg::root
 *  Member 'root' contains a node structure
 */
struct dawg {
	size_t current_node_index;
	char* last_word;
	struct stack *stack;
	struct hashmap_s hashmap;
	Node root;
};

/** @struct node
 *  @brief This structure creates a node for a dawg structure
 */
/** @var node::id
 *  Member 'id' contains the node's id
 */
/** @var node::is_word
 *  Member 'is_word' contains a boolean (wether it contains a word or not)
 */
/** @var node::neighbors
 *  Member 'neighbors' contains a vertex structure
 */
struct node
{
	size_t id;
	bool is_word;
	Vertex neighbors[ALPHABET_SIZE];
};

/** @struct vertex
 *  @brief This structure creates a vertex for a node structure
 */
/** @var vertex::label
 *  Member 'label' contains the vertex's label
 */
/** @var vertex::from
 *  Member 'from' contains the current node
 */
/** @var vertex::to
 *  Member 'to' contains the next node
 */
struct vertex
{
	char label;
	/**
	 * @brief Sommet gauche
	 */
	Node from;
	/**
	 * @brief Sommet droit
	 */
	Node to;
};

/**
 * @fn      Vertex empty_vertex(char label, Node from, Node to)
 * @brief   Creates an empty vertex structure
 * @param   label value to set in the structure
 * @param   from value to set in the structure
 * @param   to value to set in the structure
 * @return	an empty vertex structure
 */
Vertex empty_vertex(char label, Node from, Node to);

/**
 * @fn      Node empty_dawg()
 * @brief   Creates an empty node structure
 * @param   dawg dawg to treat
 * @return	an empty node structure
 */
Node empty_node(Dawg dawg);

/**
 * @fn      Dawg empty_dawg()
 * @brief   Creates an empty dawg structure
 * @return	an empty dawg structure
 */
Dawg empty_dawg();

/**
 * @fn      void free_node(Node root)
 * @brief   Free a node structure using rec_free_node
 * @param   root node to treat
 */
void free_node(Node root);

/**
 * @fn      void rec_free_node(Node root)
 * @brief   Recursively free nodes
 * @param   root node to treat
 */
void rec_free_node(Node node, struct hashmap_s* const hashmap);

/**
 * @fn      void free_dawg(Dawg dawg)
 * @brief   Free a dawg structure
 * @param   dawg dawg to treat
 */
void free_dawg(Dawg dawg);

/**
 * @fn      size_t search_prefix_length(char* word1, char* word2)
 * @brief   Gets the size of the biggest common prefix of the words
 * @param   word1 first word to compare
 * @param	word2 second word to compare
 * @return	the size
 */
size_t search_prefix_length(char* word1, char* word2);

/**
 * @fn      void minimize(Dawg dawg, size_t p)
 * @brief   Minimize a dawg structure to a given depth
 * @param   dawg dawg to treat
 * @param	p the depth 
 */
void minimize(Dawg dawg, int p);

/**
 * @fn      void insert_dawg(Dawg dawg, char* word)
 * @brief   Inserts a word inside a dawg
 * @param   dawg dawg to treat
 * @param	word word to insert
 */
void insert_dawg(Dawg dawg, char* word);

/**
 * @fn		void serialize(Node node, char* result)
 * @brief	Serialization of a node
 *  All arguments are separated with a semicolon
 *  First argument is 0 or 1, if the node is a
 *  letter or not. The next arguments are the uid
 *  of the right node of the vertexes.
 * 
 * @param node Node in question
 * @param result A serialized string separated by semicolons
 */
void serialize(Node node, char* result);

/**
 * @fn      void display_node(Node node)
 * @brief   Displays a Node structure inside a dawg
 * @param   Node node to display
 */
void display_node(Node node);

// Lang

/**
 * @fn      bool word_exists(Node node, const char* word, size_t index)
 * @brief   Checks if a word exists inside a dawg structure
 * @param   Node node to treat
 * @param	word word to search
 * @param	index index of a char (from word) to treat
 * @return 	true if the word if found, false if not
 */
bool word_exists(Node node, const char* word, size_t index);


// Handle

/**
 * @fn      void treat_dawg(Dawg en, Dawg de, Dawg fr, char** sentence, size_t n)
 * @brief   Treats a sentence
 * @param   en english dictionnary
 * @param   de german dictionnary
 * @param   fr french dictionnary 
 * @param   sentence the sentence to treat
 * @param   n the size of the sentence
 */
void treat_dawg(Dawg en, Dawg de, Dawg fr, char** sentence, size_t n);

/**
 * @fn      void start_dawg(Dawg en, Dawg de, Dawg fr)
 * @brief   start the langue detector using the Dawg structure
 * @param   en english dictionnary
 * @param   de german dictionnary
 * @param   fr french dictionnary 
 */
void start_dawg(Dawg en, Dawg de, Dawg fr);

#endif // !_DAWG_H
