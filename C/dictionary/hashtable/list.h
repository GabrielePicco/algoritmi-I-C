#ifndef __LIST_H__KJAHC38DJ__
#define __LIST_H__KJAHC38DJ__
#include <stdio.h>
#include <stdlib.h>

/* -------LIST STRUCT------- */
struct NodeType {
  void* key;
  void* cargo;
  struct NodeType *next,*prev;
} Node;

typedef struct NodeType* List;

/* -------POINTERS TO FUNCTION------- */
// Pointer to function for comparisons
#ifndef __COMPFUNCTION_KEIXJ4PDU3__
#define __COMPFUNCTION_KEIXJ4PDU3__
typedef int (*CompFunction)(void*, void*);
#endif
// Pointer to function for deallocation of the nodes
typedef void (*DeallocFunction)(List);
// Function pointer for iterate over the table
typedef void (*IteratorFunction)(void*,void*);

/* -------PROTOTYPES------- */
// Function to insert a node in a list.
List list_insert_head(List list, List node);
// The function creates and inserts, calling the function insert_head_list(), in front of the list a new node
List list_create_and_insert(List list, void* key, void* cargo);
// the function searches a node from the list by key
List list_find_key_node(List list, void* elem, CompFunction compare);
// The function removes a node from the list
List list_delete_node(List list, List node);
// Function for deallocation of all nodes into the list
void list_dealloc_all_node(List list, DeallocFunction dealloc);
// This function will be called for scroll through all element in the list.
// parameter is a generic element for any use. Set it to NULL if it does not serve
void list_iterator(List list, void* parameter, IteratorFunction iterator);
#endif
