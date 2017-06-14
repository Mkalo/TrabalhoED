#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

Graph* graph_create(int nodes, int direction) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->direction = direction;
	graph->root = node_create();
	for (int i = 1; i <= nodes; i++) {
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

void graph_remove_node(Graph* graph, int id) {
	graph->root = node_remove(graph->root, id);
	for (Node* it = graph->root; it != NULL; it = it->next) {
		it->neighbours = list_remove(it->neighbours, id);
	}
}

void graph_add_edge(Graph* graph, int id, int neighbour) {
	graph->root = node_add_neighbour(graph->root, id, neighbour);

	if (graph->direction) {
		graph->root = node_add_neighbour(graph->root, neighbour, id);
	} else {
		graph_insert_node(graph, neighbour);
	}
}

void graph_remove_edge(Graph* graph, int id, int neighbour) {
	Node* node = graph_find_node(graph, id);
	Node* node2 = graph_find_node(graph, neighbour);
	if (!node || !node2) return;

	if (graph->direction) {
		node2->neighbours = list_remove(node2->neighbours, id);
	}
	node->neighbours = list_remove(node->neighbours, neighbour);
}

Graph* graph_copy(Graph* graph) {
	Graph* ret = graph_create(0, 0);
	for (Node* it = graph->root; it != NULL; it = it->next) {
		graph_insert_node(ret, it->id);
		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			graph_add_edge(ret, it->id, it2->id);
		}
	}
	ret->direction = graph->direction;
	return ret;
}

Graph* graph_transpose_copy(Graph* graph) {
	Graph* ret = graph_create(0, 0);
	for (Node* it = graph->root; it != NULL; it = it->next) {
		graph_insert_node(ret, it->id);
		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			graph_add_edge(ret, it2->id, it->id);
		}
	}
	ret->direction = graph->direction;
	return ret;
}

void graph_free(Graph* graph) {
	node_free(graph->root);
	free(graph);
}

void graph_print(Graph* graph) {
	node_print(graph->root);
}

int graph_find_direction(Graph* graph) {
	for (Node* it = graph->root; it != NULL; it = it->next) {
		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			if (!graph_find_edge(graph, it2->id, it->id)) {
				return 0;
			}
		}
	}
	return 1;
}

// Funções para resolver o problema

void graph_dfs_visit(Graph* graph, List** visited, int id) {
	Node* node = graph_find_node(graph, id);
	if (!node) return;

	*visited = list_insert_begin_unique(*visited, id);
	for (List* it = node->neighbours; it != NULL; it = it->next) {
		if (!list_find(*visited, it->id)) {
			graph_dfs_visit(graph, visited, it->id);
		}
	}
}

void graph_dfs_visit_print(Graph* graph, List** visited, int id) {
	Node* node = graph_find_node(graph, id);
	if (!node) return;

	*visited = list_insert_begin_unique(*visited, id);
	printf("%d ", id);
	for (List* it = node->neighbours; it != NULL; it = it->next) {
		if (!list_find(*visited, it->id)) {
			graph_dfs_visit_print(graph, visited, it->id);
		}
	}
}

int graph_connected_components(Graph* graph) {
	if (!graph->direction) return 0;

	List* visited = list_create();

	int groups = 0;
	for (Node* it = graph->root; it != NULL; it = it->next) {
		if (!list_find(visited, it->id)) {
			graph_dfs_visit(graph, &visited, it->id);
			groups++;
		}
	}

	list_free(visited);
	return groups;
}

void graph_print_connected_components(Graph* graph) {
	if (!graph->direction) return;

	List* visited = list_create();

	for (Node* it = graph->root; it != NULL; it = it->next) {
		if (!list_find(visited, it->id)) {
			graph_dfs_visit_print(graph, &visited, it->id);
			printf("\n");
		}
	}

	list_free(visited);
}

void graph_print_bridges(Graph* graph) {
	if (!graph->direction) return;

	Graph* copy = graph_copy(graph);
	List* visited = list_create();
	int components = graph_connected_components(graph);

	for (Node* it = graph->root; it != NULL; it = it->next) {
		visited = list_insert_begin_unique(visited, it->id);

		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			int a = it->id, b = it2->id;
			if (!list_find(visited, b)) {
				graph_remove_edge(copy, a, b);
				if (graph_connected_components(copy) > components) {
					printf("%d %d\n", a, b);
				}
				graph_add_edge(copy, a, b);
			}
		}
	}
	
	list_free(visited);
	graph_free(copy);
}

void graph_print_art_vertices(Graph* graph) {
	if (!graph->direction) return;

	int components = graph_connected_components(graph);

	Graph* copy = graph_copy(graph);

	for (Node* it = graph->root; it != NULL; it = it->next) {
		List* aux = list_create();

		for (List* it2 = it->neighbours; it2 != NULL; it2 = it2->next) {
			aux = list_insert_begin(aux, it2->id);
		}

		graph_remove_node(copy, it->id);
		if (graph_connected_components(copy) > components) {
			printf("%d ", it->id);	
		}

		for (List* it2 = aux; it2 != NULL; it2 = it2->next) {
			graph_add_edge(copy, it->id, it2->id);
		}

		list_free(aux);
	}

	graph_free(copy);
	printf("\n");
}

void graph_dfs_topo_sort(Graph* graph, List** visited, List** stack, int id) {
	Node* node = graph_find_node(graph, id);
	if (!node) return;

	*visited = list_insert_begin_unique(*visited, id);
	for (List* it = node->neighbours; it != NULL; it = it->next) {
		if (!list_find(*visited, it->id)) {
			graph_dfs_topo_sort(graph, visited, stack, it->id);
		}
	}
	*stack = list_insert_begin_unique(*stack, id);
}

List* graph_topo_sort(Graph* graph) {
	List* visited = list_create();
	List* stack = list_create();

	for (Node* it = graph->root; it != NULL; it = it->next) {
		if (!list_find(visited, it->id)) {
			graph_dfs_topo_sort(graph, &visited, &stack, it->id);
		}
	}

	list_free(visited);
	return stack;
}

void graph_print_strongly_connected_components(Graph* graph) {
	if (graph->direction) return;

	List* order = graph_topo_sort(graph);
	List* visited = list_create();

	Graph* transpose = graph_transpose_copy(graph);

	for (List* it = order; it != NULL; it = it->next) {
		if (!list_find(visited, it->id)) {
			graph_dfs_visit_print(transpose, &visited, it->id);
			printf("\n");
		}
	}

	graph_free(transpose);
	list_free(visited);
	list_free(order);
}
