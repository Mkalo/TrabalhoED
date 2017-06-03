#include <stdlib.h>
#include <stdio.h>

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

void graph_remove_edge(Graph* graph, int id, int neighbour) {
	Node* node = graph_find_node(graph, id);
	Node* node2 = graph_find_node(graph, neighbour);
	if (!node || !node2) return;

	if (!graph->orientation) {
		node2->neighbours = list_remove(node2->neighbours, id);
	}
	node->neighbours = list_remove(node->neighbours, neighbour);
}

Graph* graph_copy(Graph* graph) {
	Graph* ret = graph_create(graph->size, graph->orientation);
	for (Node* it = graph->root; it != NULL; it = it->next) {
		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			ret->root = node_add_edge(ret->root, it->id, it2->id);
		}
	}
	return ret;
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

void graph_dfs_visit_print(Graph* graph, int* visited, int id) {
	Node* node = graph_find_node(graph, id);
	if (visited[id] || !node) return;

	visited[id] = 1;
	printf("%d ", id);
	for (List* it = node->neighbours; it != NULL; it = it->next) {
		graph_dfs_visit_print(graph, visited, it->id);
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

void graph_print_connected_sets(Graph* graph) {
	int* visited = (int*) calloc((graph->size + 1), sizeof(int));

	for (int i = 1; i <= graph->size; i++) {
		if (!visited[i]) {
			graph_dfs_visit_print(graph, visited, i);
			printf("\n");
		}
	}
	free(visited);
}

void graph_print_bridges(Graph* graph) {
	Graph* copy = graph_copy(graph);
	int* tested = (int*) calloc((graph->size + 1), sizeof(int));

	for (Node* it = graph->root; it != NULL; it = it->next) {
		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			int a = it->id, b = it2->id;
			if (!tested[a]) {
				tested[a] = 1;
				if (!graph->orientation) tested[b] = 1;

				graph_remove_edge(copy, a, b);
				if (graph_connected_sets(copy) > 1) {
					printf("%d %d\n", a, b);
				}
				graph_add_edge(copy, a, b);
			}
		}
	}
	free(tested);
	graph_free(copy);
}
