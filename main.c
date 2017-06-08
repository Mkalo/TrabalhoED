#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main(int argc, char** argv) {
	// Validação do argumento
	if (argc < 2) {
		printf("Invalid argument.\n");
		return 1;
	}
	
	// Abrir arquivo informado
	FILE* file = fopen(argv[1], "r");
	
	if (!file) {
		printf("Couldn't open file.\n");
		return 1;
	}

	// Ler tamanho do grafo do arquivo
	int tamanho;
	if (fscanf(file, "%d ", &tamanho) != 1) {
		printf("Failed to read graph size from file.\n");
		fclose(file);
		return 1;
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

	if (graph->direction) {
		printf("O grafo não é orientado.\n");
		
		int connectedSets = graph_connected_sets(graph);
		if (connectedSets == 1) {
			printf("O grafo é conexo.\nSuas pontes são:\n");
			graph_print_bridges(graph);
			printf("Seus vertices de articulação:\n");
			graph_print_art_vertices(graph);
		} else {
			printf("O grafo não é conexo.\nSuas componentes são:\n");
			graph_print_connected_sets(graph);
		}
	} else {
		printf("O grafo é orientado.\n");
		// TODO
	}

	graph_free(graph);
	return 0;
}
