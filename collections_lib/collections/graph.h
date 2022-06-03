#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
typedef struct List;
typedef struct Node;

typedef struct {
  List* nodes;
} Graph;


void graph_initialize(Graph* graph);
void graph_findPath(Graph* graph, Node* starting_state, Node* end_state);

#endif
