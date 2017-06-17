#include <stdlib.h>
#include <stdio.h>

#include "menu.h"

void menu_special_function(Graph* graph) {
	if (graph->direction == UNDIRECTED) {
		printf("O grafo não é orientado.\n");
		
		int connectedSets = graph_connected_components(graph);
		if (connectedSets == 1) {
			printf("O grafo é conexo.\nSuas pontes são:\n");
			graph_print_bridges(graph);
			printf("Seus vertices de articulação:\n");
			graph_print_art_vertices(graph);
		} else {
			printf("O grafo não é conexo.\nSuas componentes são:\n");
			graph_print_connected_components(graph);
		}
	} else if (graph->direction == DIRECTED) {
		printf("O grafo é orientado.\nSuas componentes fortemente conexas são:\n");
		graph_print_strongly_connected_components(graph);
	}
}

void menu_print_graph(Graph* graph) {
	graph_print(graph);
}

void menu_insert_node(Graph* graph) {
	printf("Inform the node to insert in the graph: ");
	int a;
	if (scanf("%d", &a) == 1) {
		if (graph_find_node(graph, a)) {
			printf("Node %d is already in the graph.\n", a);
		} else {
			graph_insert_node(graph, a);
			printf("Node %d inserted successfully\n", a);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_remove_node(Graph* graph) {
	printf("Inform the node to remove from the graph: ");
	int a;
	if (scanf("%d", &a) == 1) {
		if (!graph_find_node(graph, a)) {
			printf("Node %d is not in the graph.\n", a);
		} else {
			graph_remove_node(graph, a);
			printf("Node %d removed successfully\n", a);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_find_node(Graph* graph) {
	printf("Inform the node to find in the graph: ");
	int a;
	if (scanf("%d", &a) == 1) {
		if (graph_find_node(graph, a)) {
			printf("Node %d is in the graph.\n", a);
		} else {
			printf("Node %d is not in the graph.\n", a);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_insert_edge(Graph* graph) {
	printf("Inform the edge to insert in the graph (u v): ");
	int a, b;
	if (scanf("%d %d", &a, &b) == 2) {
		if (graph_find_edge(graph, a, b)) {
			printf("Edge %d %d is already in the graph.\n", a, b);
		} else {
			graph_add_edge(graph, a, b);
			printf("Edge %d %d inserted successfully\n", a, b);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_remove_edge(Graph* graph) {
	printf("Inform the edge to remove from the graph (u v): ");
	int a, b;
	if (scanf("%d %d", &a, &b) == 2) {
		if (!graph_find_edge(graph, a, b)) {
			printf("Edge %d %d is not in the graph.\n", a, b);
		} else {
			graph_remove_edge(graph, a, b);
			printf("Edge %d %d removed successfully\n", a, b);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_find_edge(Graph* graph) {
	printf("Inform the edge to find in the graph (u v): ");
	int a, b;
	if (scanf("%d %d", &a, &b) == 2) {
		if (graph_find_edge(graph, a, b)) {
			printf("Edge %d %d is in the graph.\n", a, b);
		} else {
			printf("Edge %d %d is not in the graph.\n", a, b);
		}
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void menu_set_direction(Graph* graph) {
	printf("Inform the orientation for the graph (0 - directed, 1 - undirected): ");
	int a = -1;
	if (scanf("%d", &a) == 1 && (a == DIRECTED || a == UNDIRECTED)) {
		if (a == UNDIRECTED && graph_find_direction(graph) != UNDIRECTED) {
			printf("This graph cannot be changed to undirected. For every edge (u v) there must be an edge (v u)\n");
			return;
		}
		graph->direction = a;
		printf("Graph orientation updated!\n");
	} else {
		printf("Invalid input\n");
		exit(1);
	}
}

void execute_menu(Graph* graph, const menu_function* menu, const char** names, int size) {
	printf("-------------------------------------------------------\n");
	for (int i = 0; i < size; i++) {
		printf("%d - %s\n", i, names[i]);
	}
	printf("%d - Exit\n", size);

	printf("Select an operation to execute: ");
	int op = 0;
	if (scanf("%d", &op) == 1) {
		if (op < 0 || op >= size) return;

		printf("-------------------------------------------------------\n");
		menu[op](graph);
		execute_menu(graph, menu, names, size);
	}
}
