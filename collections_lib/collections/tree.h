#ifndef TREE__H
#define TREE__H
#include "node.h"
#include "memory.h"
#include "common.h"

/**
 * @brief Returns a hash of the data in a.
 *        The hash is used to compare equality of nodes
 *        and thus should return a unique value.
 *
 */
typedef int (*Hash)(void* a);

/**
 * @brief A red black tree
 *
 */
typedef struct {
  Node* head;
  Hash hash;
} Tree;

/**
 * @brief Given a pointer to a valid tree, initialize it.
 * Only call this function after allocating a location for the tree.
 * Do not call this function after inserting nodes into the tree because
 * it can lead to a memory leak.
 *
 * @param tree
 * @param hash
 */
void tree_init(Tree* tree, Hash hash);

/**
 * @brief Free any memory allocated by the tree and return it to an empty state
 *
 * @param tree
 * @returns OK => ok
 *          EDATOKFAIL => function left structure in improper state
 */
int tree_clear(Tree* tree);

/**
 * @brief Insert data into the tree based on the comparator function
 *        provided during initialization. It is an error if the item exists already
 *
 * @param data
 * @returns OK => ok
 *          EDATOKFAIL => function left structure in improper state
 *          EDATAFOUND => hash of data was equal to the hash of data already in the tree
 */
int tree_insert(Tree* tree, void* data);

/**
 * @brief Traverse the Tree inorder, calling func on each node.
 *        Pass the accumulator to func each time to generate a result.
 *
 * @param tree
 * @param func
 * @param accumulator
 */
void tree_traverse_inorder(Tree* tree, IteratorFunction func, void* accumulator);

/**
 * @brief Searches the tree by comparing results of the hash function
 *        to the key.
 *
 * @param tree
 * @param key
 * @return void* data
 */
void* tree_find(Tree* tree, int key);

/**
 * @brief Checks that the tree is structured properly.
 *        Should be called during tests. Optionally,
 *        if CHECK_OK is set to 1, this function will be called at the end of
 *        every operation.
 *
 * @param node
 * @return int DATASTRUCT_OK => ok
 *             DATASTRUCT_ERROR => Error
 */
int tree_ok(Tree*);

#endif
