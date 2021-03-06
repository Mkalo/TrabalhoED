#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List* list_create(void) {
	return NULL;
}

List* list_insert_begin(List* list, int id) {
	List* head = (List*) malloc(sizeof(List));
	head->id = id;
	head->next = list;
	return head;
}

List* list_insert_begin_unique(List* list, int id) {
	if (!list_find(list, id)) return list_insert_begin(list, id);
	return list;
}

List* list_find(List* list, int id) {
	if (!list) return NULL;

	if (list->id == id) {
		return list;
	} else {
		return list_find(list->next, id);
	}
}

List* list_remove(List* list, int id) {
	List* before = NULL;
	List* it = list;
	while ((it) && it->id != id) {
		before = it;
		it = it->next;
	}
	if (!it) return list;
	if (!before) list = list->next;
	else before->next = it->next;
	free(it);
	return list;
}

void list_free(List* list) {
	if (list) {
		list_free(list->next);
		free(list);
	}
}

void list_print(const List* list) {
	if (list) {
		printf("%d", list->id);
		if (list->next) printf(", ");
		list_print(list->next);
	} else {
		printf("\n");
	}
}
