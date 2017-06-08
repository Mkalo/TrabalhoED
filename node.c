#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Node* node_create(void) {
	return NULL;
}

Node* node_find(Node* node, int id) {
	if (!node) return NULL;

	if (node->id == id) {
		return node;
	} else {
		return node_find(node->next, id);
	}
}

Node* node_insert(Node* node, int id) {
	Node* head = node;
	if (!node_find(head, id)) {
		head = (Node*) malloc(sizeof(Node));
		head->id = id;
		head->next = node;
		head->neighbours = NULL;
	}
	return head;
}

Node* node_remove(Node* node, int id) {
	Node* it = node, *ant = NULL;
	while (it && it->id != id) {
		ant = it;
		it = it->next;
	}

	if (!it) return node;
	
	if (ant) {
		ant->next = it->next;
	} else {
		node = it->next;
	}
	
	it->next = NULL;
	node_free(it);

	return node;
}

Node* node_add_neighbour(Node* node, int id, int neighbour) {
	Node* f = node_find(node, id);
	if (!f) {
		node = node_insert(node, id);
		f = node;
	}
	f->neighbours = list_insert_begin_unique(f->neighbours, neighbour);
	return node;
}

int node_length(Node* node) {
	int ret = 0;
	while (node) {
		node = node->next;
		ret++;
	}
	return ret;
}

void node_free(Node* node) {
	if (node) {
		node_free(node->next);
		list_free(node->neighbours);
		free(node);
	}
}

void node_print(Node* node) {
	if (node) {
		printf("ID: %d, Neighbours:", node->id);
		list_print(node->neighbours);
		node_print(node->next);
	}
}
