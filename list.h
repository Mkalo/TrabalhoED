#ifndef LIST_H
#define LIST_H

typedef struct NeighbourList {
	int id;
	struct NeighbourList* next;
} List;

List* list_create(void);
List* list_insert_begin(List* list, int id);
List* list_insert_begin_unique(List* list, int id);
List* list_find(List* list, int id);
List* list_remove(List* list, int id);
int list_length(List* list);
void list_free(List* list);
void list_print(List* list);

#endif
