#ifndef __LIST_H_
#define __LIST_H_

typedef struct _node {
    void *elem;
    struct _node *next, *prev;
} Node;

Node * add_node(Node *list, void * elem);
Node * delete_node(Node *list, Node *node);
Node * append_list(Node *initial, Node *append);

void print_list(Node *list, void (*print_elem)(void*));

#endif // __LIST_H_
