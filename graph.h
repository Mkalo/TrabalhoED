#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "list.h"

typedef struct Graph {
	int size;
	int orientation;
	Node* root;
} Graph;

Graph* graph_create(int size, int orientation);
Node* graph_find_node(Graph*, int id);
List* graph_find_edge(Graph* graph, int id, int neighbour);
void graph_insert_node(Graph* graph, int id);
void graph_add_edge(Graph* graph, int id, int neighbour);
void graph_remove_edge(Graph graph, int id);
int graph_vertices(Graph* graph);
void graph_free(Graph* graph);
void graph_print(Graph* graph);

// Methods to solve the problem
void graph_dfs_visit(Graph* graph, int* visited, int id);
int graph_connected_sets(Graph* graph);

#endif
