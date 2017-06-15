#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "list.h"

typedef struct Graph {
	Node* root;
	// 0 = directed, 1 = undirected
	int direction;
} Graph;

Graph* graph_create(int size, int direction);
Node* graph_find_node(const Graph*, int id);
List* graph_find_edge(const Graph* graph, int id, int neighbour);
void graph_insert_node(Graph* graph, int id);
void graph_remove_node(Graph* graph, int id);
void graph_add_edge(Graph* graph, int id, int neighbour);
void graph_remove_edge(Graph* graph, int id, int neighbour);
Graph* graph_copy(const Graph* graph);
Graph* graph_transpose_copy(const Graph* graph);
void graph_free(Graph* graph);
void graph_print(const Graph* graph);
int graph_find_direction(const Graph* graph);

// Funções para resolver o problema

// Visita todos os nós usando DFS (busca em profundidade) e insere eles na lista de nós visitados.
void graph_dfs_visit(const Graph* graph, List** visited, int id);

// Exatamente a mesma coisa que a graph_dfs_visit porém além de inserir os nós em uma lista, printa os nós inseridos na mesma linha.
void graph_dfs_visit_print(const Graph* graph, List** visited, int id);

// Funções somente para grafo não orientado

// Utiliza a função graph_dfs_visit em todos os nós não visitados e conta quantas componentes o grafo possui.
int graph_connected_components(const Graph* graph);

// Exatamente a mesma coisa que a função graph_connected_components porém usa a graph_dfs_visit_print para printar as componentes.
void graph_print_connected_components(const Graph* graph);

// É feita uma cópia do grafo para não modificar o endereço dos ponteiro do grafo original.
// Para cada aresta do grafo é feito o teste de retirar essa aresta da cópia do grafo, se o número de componentes do grafo
// aumentar, essa aresta era uma ponte e então ela é printada, e então a aresta é adicionada ao grafo cópia novamente.
void graph_print_bridges(const Graph* graph);

// É feita uma cópia do grafo para não modificar o endereço dos ponteiros do grafo original.
// Para cada nó do grafo é feito o teste de retirar esse nó da cópia do grafo, se o número de componentes do grafo
// aumentar, esse vertice era um vertice de articulação e então é printado, e todas as arestas relacionadas a esse nó
// são adicionadas devolta.
void graph_print_art_vertices(const Graph* graph);

// Funções somente para grafo orientado

// Algoritmo de Kosaraju. Primeiro é feita uma forward traverse para obter os nós em post-order
// e depois uma backward traverse na ordem obtida para printar as componentes fortemente conexas.
// A ordem é dada pela função graph_topo_sort e o backward traverse é uma DFS no grafo transposto (direção das arestas trocadas)
void graph_print_strongly_connected_components(const Graph* graph);

// Exatamente a mesma coisa que a função graph_dfs_visit porém ao terminar de visitar todos os vizinhos, insere o nó na
// lista que serve como uma stack.
void graph_dfs_topo_sort(const Graph* graph, List** visited, List** stack, int id);

// Utiliza a funçao graph_dfs_topo_sort em todos os nós não visitados. O nome da função esta como
// topo sort visto que o algoritmo é o mesmo do topological sort, porém só estamos interessados na
// ordem post-order dos nós visto que o grafo poderia ter ciclos e deixaria de ser um topological sort.
List* graph_topo_sort(const Graph* graph);

#endif
