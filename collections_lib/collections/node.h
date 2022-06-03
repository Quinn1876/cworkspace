#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "list.h"
#include "common.h"

typedef struct node_t {
  void* data;
  List* children;
} Node;

/**
 * @brief Allocate a new Node which stores data
 *        The node does not own the data, so it will not
 *        free the data on cleanup
 *
 * @param data
 * @return Node*
 */
Node* node_new(void* data);

/**
 * @brief Cleanup the node once you are done with it
 *
 * @param node
 */
void node_delete(Node* node);

/**
 * @brief Return the node that is the *child_number*th child of the node
 *
 * @param node
 * @param child_number
 * @return Node*
 */
Node* node_get_child(Node* node, size_t child_number);

/**
 * @brief Return the data stored in the node
 *
 * @param node
 * @return void*
 */
void* node_get_data(Node* node);

/**
 * @brief Insert a node into the front of the children list
 *
 * @param node
 * @param child
 *
 * @returns OK => ok
 *          EDATOKFAIL => function left structure in improper state
 */
int node_push_child_front(Node* node, Node* child);

/**
 * @brief Insert a node into the back of the children list
 *
 * @param node
 * @param child
 *
 * @returns OK => ok
 *          EDATOKFAIL => function left structure in improper state
 */
int node_push_child_back(Node* node, Node* child);

/**
 * @brief Run a function on each child of the node
 *
 * @param node
 * @param func
 */
void node_for_each_child_forward(Node* node, IteratorFunction func, void* accumulator);

/**
 * @brief Run a function on each child of the node
 *
 * @param node
 * @param func
 */
void node_for_each_child_backward(Node* node, IteratorFunction func, void* accumulator);

/**
 * @brief Returns the number of children that the node has
 *
 * @param node
 * @return size_t
 */
size_t node_num_children(Node* node);

/**
 * @brief Checks that the node is structured properly.
 *        Should be called during tests. Optionally,
 *        if CHECK_OK is set to 1, this function will be called at the end of
 *        every operation.
 *
 * @param node
 * @return int 1 => ok
 *             0 => Error
 */
int node_ok(Node* node);

#endif
