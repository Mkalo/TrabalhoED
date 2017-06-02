#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "list.h"

typedef struct Graph {
	int orientation;
	Node* root;
} Graph;

Graph* graph_create(int orientation);
List* graph_find_edge(Graph* graph, int id, int neighbour);
void graph_insert_node(Graph* graph, int id);
void graph_add_edge(Graph* graph, int id, int neighbour);
void graph_remove_edge(Graph graph, int id);
int graph_vertices(Graph* graph);
void graph_free(Graph* graph);
void graph_print(Graph* graph);

#endif
