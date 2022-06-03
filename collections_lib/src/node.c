#include "collections/node.h"

Node* node_new(void* data) {
  Node* node = malloc(sizeof(Node));
  node->children = malloc(sizeof(List));
  node->data = data;
  list_init(node->children);
}

void node_delete(Node* node) {
  list_clear(node->children);
  free(node->children);
  free(node);
}

Node* node_get_child(Node* node, size_t child_number) {
  List* children = node->children;
  ListNode* runner = children->head;
  size_t counter = 0;
  while (runner != NULL) {
    if (counter == child_number) {
      return (Node*)runner->data;
    }
    ++counter;
  }
  return NULL;
}

void* node_get_data(Node* node) {
  return node->data;
}

int node_push_child_front(Node* node, Node* child) {
  list_insert_element_front(node->children, child);
  #if CHECK_OK == 1
  if (node_ok(node) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

int node_push_child_back(Node* node, Node* child) {
  list_insert_element_back(node->children, child);
  #if CHECK_OK == 1
  if (node_ok(node) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

void node_for_each_child_forward(Node* node, IteratorFunction func, void* accumulator) {
  list_for_each_forward(node->children, func, accumulator);
}

void node_for_each_child_backward(Node* node, IteratorFunction func, void* accumulator) {
  list_for_each_backward(node->children, func, accumulator);
}

size_t node_num_children(Node* node) {
  return list_length(node->children);
}

int node_ok(Node* node) {
  return list_ok(node->children);
}
