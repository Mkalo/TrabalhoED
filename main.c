#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

typedef void (*menu_function)(Graph*);

Graph* read_graph_from_file(const char* dir) {
	// Abrir arquivo informado
	FILE* file = fopen(dir, "r");
	
	if (!file) {
		printf("Couldn't open file.\n");
		return NULL;
	}

	// Ler tamanho do grafo do arquivo
	int tamanho;
	if (fscanf(file, "%d ", &tamanho) != 1) {
		printf("Failed to read graph size from file.\n");
		fclose(file);
		return NULL;
	}

	// Assumir que o grafo é orientado
	Graph* graph = graph_create(tamanho, 0);

	// Ler arestas
	int a, b;
	while (fscanf(file, "%d %d ", &a, &b) == 2) {
		graph_add_edge(graph, a, b);
	}

	fclose(file);

	// Update na orientação de acordo com as arestas.
	graph->direction = graph_find_direction(graph);

	return graph;
}

void menu_special_function(Graph* graph) {
	if (graph->direction) {
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
	} else {
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
	if (scanf("%d", &a) == 1 && (a == 0 || a == 1)) {
		if (a == 1 && graph_find_direction(graph) != 1) {
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

int main(int argc, char** argv) {
	Graph* graph;

	if (argc >= 2) {
		graph = read_graph_from_file(argv[1]);
		if (!graph) return 1;
	} else {
		graph = graph_create(0, 0);
	}

	const menu_function menu[9] = {menu_special_function, menu_print_graph, menu_insert_node, menu_remove_node, menu_find_node, menu_insert_edge, menu_remove_edge, menu_find_edge, menu_set_direction};
	const char* names[9] = {"Special function", "Print graph", "Insert node", "Remove node", "Find node", "Insert edge", "Remove edge", "Find edge", "Change orientation"}; 
	
	execute_menu(graph, menu, names, 9);
	
	graph_free(graph);
	return 0;
}
