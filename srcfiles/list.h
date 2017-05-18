#ifndef __LIST_H_
#define __LIST_H_

/**
 * @struct Node
 *
 * @brief One element of list which can be Point or Plain
 *
 * @var Node::elem
 * Member 'elem' is void - Point/Plain
 * @var Node::next
 * @var Node::prev
 * Members pointers to next and previous elements of list
 */
typedef struct _node {
    void *elem;
    struct _node *next, *prev;
} Node;

/** 
 * @brief Returns last element of list
 * 
 * @param list
 * List which is processed
 */
Node* last (Node *list);

/** 
 * @brief Adds new node to the list
 * 
 * @param list
 * List is list which adds new elem
 * 
 * @param elem
 * Element which is added to the list
 */
Node* add_node(Node *list, void * elem);

/**
 * @brief Deletes node from list
 * 
 * @param list
 * List from which node is deleted
 * @param elem
 * Element which should be deleted
 */
Node* delete_node(Node *list, Node *node);

/** 
 * @brief On existing list, we append new node;
 *
 * @param initial 
 * List which currently exisist or we create one
 * @param append
 * Element of a list which is about to be added 
 */
Node* append_list(Node *initial, Node *append);

/**
 * @brief Debug function which prints list
 * 
 void print_list(Node *list, void (*print_elem)(void*));
*/

#endif // __LIST_H_
