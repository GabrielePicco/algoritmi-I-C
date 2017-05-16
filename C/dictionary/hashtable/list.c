#include "list.h"
#include <string.h>

/*
 * The function creates and allocates a new node
 * list: node pointer
 * key: key node
 * cargo: node value
 * return: the pointer of the new node
 */
List new_node(void* key, void* cargo){
  List node = (List) malloc(sizeof(Node));
  node->key = key;
  node->cargo = cargo;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

/*
 * Function to insert a node in a list.
 * list: node pointer
 * node: node to be insert in the head
 * return: the pointer to the list obtained
 */
List list_insert_head(List list, List node){
  node->next = list;
  node->prev = NULL;
  if (list != NULL){
    list->prev = node;
  }
  return node;
}

/*
 * The function creates and inserts in front of the list a new node.
 * list: node pointer
 * key: key node
 * cargo: node value
 * return: the pointer to the list obtained
 */
List list_create_and_insert(List list, void* key, void* cargo){
 List new_head = new_node(key, cargo);
 return list_insert_head(list, new_head);
}

/*
 * The function searches a node from the list by key.
 * list: node pointer
 * key: key node
 * compare: the function for comparison
 * return: the pointer of the searched element or NULL
 */
List list_find_key_node(List list, void* key, CompFunction compare){
  while(list != NULL){
    if (compare(list->key, key) == 0){
      return list;
    }
    list = list->next;
  }
  return NULL;
}

/*
 * The function removes a node from the list.
 * list: node pointer
 * node: node to be deleted
 * dealloc: dealloc: the function for deallocation of the node
 * return: the pointer to list obtained
 */
List list_delete_node(List list, List node){
  if (node->prev != NULL){  // node is not the first element
    node->prev->next = node->next;
  } else {
    list = node->next;  // the head of the list changes
  }
  if (node->next != NULL){  // node is not the last element
    node->next->prev = node->prev;
  }
  return list;
}

/*
 * The function removes all node of the list.
 * list: node pointer
 * dealloc: the function for deallocation of the node
 */
void list_dealloc_all_node(List list, DeallocFunction dealloc){
  List temp = list;
  while (temp != NULL){
    list = temp->next;
    dealloc(temp);
    temp = list;
  }
}

/*
 * This function will be called for scroll through all element in the list.
 * list: node pointer
 * parameter: generic element for any use. If it is null it means that it does not serve
 * iterator: generic function that acts on the nodes
 */
void list_iterator(List list, void* parameter, IteratorFunction iterator){
  while (list != NULL){
    iterator(list->cargo, parameter);
    list = list->next;
  }
}
