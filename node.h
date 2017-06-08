#ifndef NODE_H
#define NODE_H

#include "list.h"

typedef struct GraphNode {
	int id;
	List* neighbours;
	struct GraphNode* next;
} Node;

Node* node_create(void);
Node* node_find(Node* node, int id);
Node* node_insert(Node* node, int id);
Node* node_remove(Node* node, int id);
Node* node_add_neighbour(Node* node, int id, int neighbour);
int node_length(Node* node);
void node_free(Node* node);
void node_print(Node* node);

#endif
