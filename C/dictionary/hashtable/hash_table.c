#include "hash_table.h"

/*
 * Function to initialize the table.
 * size: table dimension
 */
List* init_hash_table(int size){
  List* table = NULL;
  table = (List*) malloc(sizeof(List)*size);
  for (int i = 0; i < size; ++i){
    table[i] = NULL;
  }
  return table;
}

/*
 * Function for create and initialize the table.
 * PRE-CONDITION: the table must be NULL to be initialized
 * hash_table: Hashtable pointer
 * size: table dimension
 * hash: function to calculate in which position put the element
 * compare: the function for comparison
 * return: the initialized table
 */
void hash_table_init_struct(HashTable* hash_table, int size, HashFunction hash, CompFunction compare){
  if ((*hash_table) != NULL){
    printf("Initialization error. Hashtable already allocated\n");
    exit(1);
  }
  (*hash_table) = (HashTable) malloc(sizeof(HashTableType));
  (*hash_table)->size = size;
  (*hash_table)->inserted_elem_count = 0;
  (*hash_table)->hash = hash;
  (*hash_table)->compare = compare;
  (*hash_table)->table = init_hash_table(size);
}

/*
 * The function searches the element with key "key" in the table.
 * hash_table: HashTableStruct pointer
 * key: key element
 * return: the pointer of the searched element or NULL
 */
List hash_table_find(HashTable hash_table, void* key){
 return list_find_key_node(hash_table->table[hash_table->hash(key,hash_table->size)], key, hash_table->compare);
}

/*
 * The function inserts the values in the new table
 * during the reallocation.
 * table: new table
 * list: node pointer
 * new_size: new size of the table
 * return: the new table
 */
List* insert_new_table(HashTable hash_table,List* table,List list,int new_size){
  List temp_node;
  while(list != NULL){
    int new_hash = hash_table->hash(list->key,new_size);
    table[new_hash] = list_create_and_insert(table[new_hash],list->key,list->cargo);
    temp_node = list;
    list = list->next;
    free(temp_node);
  }
  return table;
}

/*
 * The function allocates a new table and calls the function insert_new_table()
 * to insert in it the values presents in the old table.
 * hash_table: HashTableStruct pointer
 * new_size: new table size
 */
void hash_table_dynamics_reallocation(HashTable hash_table,int new_size){
  List* new_table = init_hash_table(new_size);
  for (int i = 0; i < hash_table->size; ++i){
  new_table = insert_new_table(hash_table,new_table,hash_table->table[i],new_size);
  }
  free(hash_table->table);
  hash_table->size = new_size;
  hash_table->table = new_table;
}

/*
 * The function inserts an element in the table and
 * reallocates the table when the number of the inserted
 * elements becomes greater than half of the table.
 * hash_table: HashTableStruct pointer
 * key: key element
 * cargo: element value
 * return: the pointer to the new list inserted
 */
List hash_table_insert(HashTable hash_table, void* key, void* cargo){
 int index;
 List node_temp;
 if (hash_table->inserted_elem_count > (hash_table->size/2)){
   hash_table_dynamics_reallocation(hash_table,(hash_table->size)*2);
 }
 index = hash_table->hash(key, hash_table->size);
 if ((node_temp = list_find_key_node(hash_table->table[index],key,hash_table->compare)) == NULL){
  hash_table->table[index] = list_create_and_insert(hash_table->table[index], key, cargo);
  ++(hash_table->inserted_elem_count);
 } else {
  node_temp->cargo = cargo;
 }
 return hash_table->table[index];
}

/*
 * The function prints all the elements of the table.
 * hash_table: HashTableStruct pointer
 */
void hash_table_print(HashTable hash_table,IteratorFunction iterator){
 for (int i = 0; i < hash_table->size; ++i){
   if (hash_table->table[i] != NULL){
     printf("\nTabella[%d] --> ", i);
     list_iterator(hash_table->table[i], NULL,iterator);
   }
 }
}

/*
 * The function removes from the table the element with key "key" and
 * reallocates the table when the number of inserted elements becomes
 * lower then a quarter of the table.
 * hash_table: HashTableStruct pointer
 * key: key element
 * return: the deleted node
 */
List hash_table_delete(HashTable hash_table, void* key){
 if (hash_table->inserted_elem_count == 0) return NULL;
 if (hash_table->inserted_elem_count < (hash_table->size)/4){
   hash_table_dynamics_reallocation(hash_table,(hash_table->size)/2);
 }
 int index = hash_table->hash(key, hash_table->size);
 List temp;
 if ((temp = list_find_key_node(hash_table->table[index], key, hash_table->compare)) != NULL){
   hash_table->table[index] = list_delete_node(hash_table->table[index], temp);
   --(hash_table->inserted_elem_count);
 }
 return temp;
}

/*
 * The function deallocates the table and all the elements of it.
 * hash_table: HashTableStruct pointer
 */
void hash_table_deallocation(HashTable hash_table,DeallocFunction dealloc){
 for (int i = 0; i < hash_table->size; ++i){
   list_dealloc_all_node(hash_table->table[i],dealloc);
 }
 free(hash_table->table);
 free(hash_table);
}

/*
 * This function will be called for scroll through all element in the table.
 * hash_table: HashTableStruct pointer
 * parameter: generic element for any use. If it is null it means that it does not serve
 */
void hash_table_iterator(HashTable hash_table, void* parameter,IteratorFunction iterator){
  if(hash_table == NULL)return;
  for (int i = 0; i < hash_table->size; ++i){
    list_iterator(hash_table->table[i], parameter,iterator);
  }
}
