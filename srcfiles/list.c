
/* VISUALSTUDIO branch (c) 2021 by dbj@dbj.org */

#include "list.h"

Node* last(Node* list)
{
	while (list->next != NULL)
		list = list->next;

	return list;
}

Node* add_node(Node* list, void* elem)
{
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		//         printf("Malloc error");
		exit(EXIT_FAILURE);
	}

	if (elem == NULL)
		return list;
	new_node->elem = elem;
	new_node->next = NULL;

	if (list == NULL) {
		list = new_node;
		new_node->prev = NULL;
	}
	else {
		new_node->prev = last(list);
		new_node->prev->next = new_node;
	}
	return list;
}

Node* delete_node(Node* list, Node* node)
{
	Node* tmp = list;
	while (tmp != NULL) {
		if (tmp == node) {
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;

			if (tmp == list) {
				list = NULL;
			}

			free(tmp);

			break;
		}
		tmp = tmp->next;
	}
	return list;
}

Node* append_list(Node* initial, Node* append) {

	if (initial == NULL) {
		return append;
	}
	else if (append == NULL) {
		return initial;
	}

	Node* initial_last = last(initial);
	initial_last->next = append;
	append->prev = initial_last;

	return initial;
}

/* DEBUGING
void print_list(Node *list, void (*print_elem)(void*))
{

	printf("[");
	for (Node *temp = list; temp != NULL; temp = temp->next) {
		print_elem(temp->elem);
		if(temp->next != NULL) {
			printf(", ");
		}
	}
	printf("]");
}  */
