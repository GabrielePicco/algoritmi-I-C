#ifndef __HASHTABLE_H_KEIXJ4PDU3__
#define __HASHTABLE_H_KEIXJ4PDU3__
#include "list.h"

// Function pointer for the calculation of the hash function
typedef int (*HashFunction)(void*, int);

/* -------HASHTABLE STRUCT------- */
struct HashTableStruct{
  int size;
  int inserted_elem_count;
  List* table;
  HashFunction hash;
  CompFunction compare;
} HashTableType;

typedef struct HashTableStruct* HashTable;

/* -------PROTOTYPES------- */
// Function for crate and initialize the table
// PRE-CONDITION: the table must be NULL to be initialized
void hash_table_init_struct(HashTable* hash_table,int size,HashFunction hash,CompFunction compare);
// The function searches the element with key "key" in the table
List hash_table_find(HashTable hash_table, void* key);
// The function inserts an element in the table and reallocates the table when the number
// of the inserted element becomes greater than half of the table
List hash_table_insert(HashTable hash_table, void* key, void* cargo);
// The function prints all the elements of the table
void hash_table_print(HashTable hash_table,IteratorFunction iterator);
// The function removes from the table the element with key "key" and reallocates
// the table when the number of the inserted element becomes lower of three-eighths of the table
List hash_table_delete(HashTable hash_table, void* key);
// The function deletes all the elements of the table
void hash_table_deallocation(HashTable hash_table,DeallocFunction dealloc);
 // This function will be called for scroll through all element in the list.
 // parameter is a generic element for any use. Set it to NULL if it does not serve
void hash_table_iterator(HashTable hash_table, void* parameter,IteratorFunction iterator);
#endif
