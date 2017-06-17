#include <stdlib.h>
#include <stdio.h>

#include "menu.h"
#include "graph.h"

int main(int argc, char** argv) {
	Graph* graph;

	if (argc >= 2) {
		graph = read_graph_from_file(argv[1]);
		if (!graph) return 1;
	} else {
		graph = graph_create(0, DIRECTED);
	}

	const menu_function menu[] = {menu_special_function, menu_print_graph, menu_insert_node, menu_remove_node, menu_find_node, menu_insert_edge, menu_remove_edge, menu_find_edge, menu_set_direction};
	const char* names[] = {"Special function", "Print graph", "Insert node", "Remove node", "Find node", "Insert edge", "Remove edge", "Find edge", "Change orientation"}; 
	
	execute_menu(graph, menu, names, sizeof(menu) / sizeof(menu_function));
	
	graph_free(graph);
	return 0;
}
