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

	// Ler orientaçao do grafo
	int orientado;
	if (fscanf(file, "%d ", &orientado) != 1) {
		printf("Failed to read graph orientation from file.\n");
		fclose(file);
		return 1;
	}

	Graph* graph = graph_create(tamanho, orientado);

	// Ler arestas
	int a, b;
	while (fscanf(file, "%d %d ", &a, &b) == 2) {
		graph_add_edge(graph, a, b);
	}

	fclose(file);


	printf("Connected sets: %d\n", graph_connected_sets(graph));
	graph_print(graph);
	graph_free(graph);
	return 0;
}
