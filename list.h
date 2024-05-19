//
// Created by Aube on 04/05/2024.
//

#ifndef CDATAFRAMEL1_LIST_H
#define CDATAFRAMEL1_LIST_H

typedef struct column COLUMN;

/**
* Élément lnode
*/
typedef struct lnode_ {
    COLUMN* data;
    struct lnode_ *prev;
    struct lnode_ *next;
} lnode;

/**
* Une liste
*/
typedef struct list_ {
    lnode *head;
    lnode *tail;
} list;



/**
* create a node
*/
lnode *lst_create_lnode(void *dat);

/**
* create a list a return the pointer on it
*/
list *lst_create_list();

/**
* delete the list lst
*/
void lst_delete_list(list * lst);

/**
* insert a node at the head of the list lst
*/
void lst_insert_head(list * lst, lnode * pnew);

/**
* insert a node at the end of the list st
*/
void lst_insert_tail(list * lst, lnode * pnew);

/**
* insert a node after the node pointed by ptr in the list lst
*/
void lst_insert_after(list * lst, lnode * pnew, lnode * ptr);

/**
* delete the head of the list lst
*/
void lst_delete_head(list * lst);

/**
* delete the tail of the list lst
*/
void lst_delete_tail(list * lst);

/**
* delete the node pointed by ptr
*/
void lst_delete_lnode(list * lst, lnode * ptr);

/**
* delete all elements of the list lst
*/
void lst_erase(list * lst);

/**
* return the first node if it exits, else NULL
*/
lnode *get_first_node(list * lst);

/**
* return the last node if it exits, else NULL
*/
lnode *get_last_node(list * lst);

/**
* return the next node
*/
lnode *get_next_node(list * lst, lnode * lnode);

/**
* return the previous node
*/
void *get_previous_elem(list * lst, lnode * lnode);


#endif //CDATAFRAMEL1_LIST_H
