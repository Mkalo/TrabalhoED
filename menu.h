#ifndef MENU_H
#define MENU_H

#include "graph.h"

typedef void (*menu_function)(Graph*);

void menu_special_function(Graph* graph);
void menu_print_graph(Graph* graph);
void menu_insert_node(Graph* graph);
void menu_remove_node(Graph* graph);
void menu_find_node(Graph* graph);
void menu_insert_edge(Graph* graph);
void menu_remove_edge(Graph* graph);
void menu_find_edge(Graph* graph);
void menu_set_direction(Graph* graph);
void execute_menu(Graph* graph, const menu_function* menu, const char** names, int size);

#endif