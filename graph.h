#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "list.h"

typedef struct Graph {
	Node* root;
	// 0 = directed, 1 = undirected
	int direction;
} Graph;

Graph* graph_create(int size, int direction);
Node* graph_find_node(Graph*, int id);
List* graph_find_edge(Graph* graph, int id, int neighbour);
void graph_insert_node(Graph* graph, int id);
void graph_remove_node(Graph* graph, int id);
void graph_add_edge(Graph* graph, int id, int neighbour);
void graph_remove_edge(Graph* graph, int id, int neighbour);
Graph* graph_copy(Graph* graph);
Graph* graph_transpose_copy(Graph* graph);
void graph_free(Graph* graph);
void graph_print(Graph* graph);
int graph_find_direction(Graph* graph);

// Funções para resolver o problema
void graph_dfs_visit(Graph* graph, List** visited, int id);
void graph_dfs_visit_print(Graph* graph, List** visited, int id);

// Funções somente para grafo não orientado
int graph_connected_components(Graph* graph);
void graph_print_connected_components(Graph* graph);
void graph_print_bridges(Graph* graph);
void graph_print_art_vertices(Graph* graph);

// Funções somente para grafo orientado
void graph_print_strongly_connected_components(Graph* graph);
void graph_dfs_topo_sort(Graph* graph, List** visited, List** stack, int id);
List* graph_topo_sort(Graph* graph);

#endif
