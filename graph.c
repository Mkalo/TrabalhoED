#include <stdlib.h>

#include "graph.h"

Graph* graph_create(int orientation) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->orientation = orientation;
	graph->root = node_create();
	return graph;
}

List* graph_find_edge(Graph* graph, int id, int neighbour) {
	Node* node = node_find(graph->root, id);
	if (!node) return NULL;
	return list_find(node->neighbours, neighbour);
}

void graph_insert_node(Graph* graph, int id) {
	graph->root = node_insert(graph->root, id);
}

void graph_add_edge(Graph* graph, int id, int neighbour) {
	graph->root = node_add_edge(graph->root, id, neighbour);

	if (!graph->orientation) {
		graph->root = node_add_edge(graph->root, neighbour, id);
	} else {
		graph_insert_node(graph, neighbour);
	}
}

int graph_vertices(Graph* graph) {
	return node_length(graph->root);
}

void graph_free(Graph* graph) {
	node_free(graph->root);
	free(graph);
}

void graph_print(Graph* graph) {
	node_print(graph->root);
}
