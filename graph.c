#include <stdlib.h>

#include "graph.h"

Graph* graph_create(int size, int orientation) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->size = size;
	graph->orientation = orientation;
	graph->root = node_create();
	for (int i = 1; i <= size; i++) {
		graph_insert_node(graph, i);
	}
	return graph;
}

Node* graph_find_node(Graph* graph, int id) {
	return node_find(graph->root, id);
}

List* graph_find_edge(Graph* graph, int id, int neighbour) {
	Node* node = graph_find_node(graph, id);
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

void graph_dfs_visit(Graph* graph, int* visited, int id) {
	Node* node = graph_find_node(graph, id);
	if (visited[id] || !node) return;

	visited[id] = 1;

	for (List* it = node->neighbours; it != NULL; it = it->next) {
		graph_dfs_visit(graph, visited, it->id);
	}
}

int graph_connected_sets(Graph* graph) {
	int* visited = (int*) calloc((graph->size + 1), sizeof(int));

	int groups = 0;
	for (int i = 1; i <= graph->size; i++) {
		if (!visited[i]) {
			graph_dfs_visit(graph, visited, i);
			groups++;
		}
	}
	free(visited);
	return groups;
}
