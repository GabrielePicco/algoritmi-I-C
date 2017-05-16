#include <assert.h>
#include <time.h>
#include "hash_table.h"
#include "../../utility/test.h"
#include "../../utility/unit_test_utility.h"

#define HASHDIM 11

/* -------HELPER FUNCTIONS------- */
void dealloc_node(List node){
  if (node != NULL){
      free(node);
  }
}

// Hash function for integers
int hash_function_int_ptr(void* key, int size){
  return *(int*)key % size;
}

void print_int(void* ptr1, void* ptr2){
  printf("%d ", *(int*)ptr1);
}

/* -------TESTS------- */
void test_hashtable_insert_on_int_ptr() {
 HashTable hash_table = NULL;
 hash_table_init_struct(&hash_table,HASHDIM,hash_function_int_ptr,compare_int_ptr);
 int* i = new_int(57);
 assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
 i = new_int(6);
 assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
 i = new_int(75);
 assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
 i = new_int(23);
 assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);

 hash_table_deallocation(hash_table,dealloc_node);
}

void test_hashtable_search_on_int_ptr() {
  HashTable hash_table = NULL;
   hash_table_init_struct(&hash_table,HASHDIM,hash_function_int_ptr,compare_int_ptr);
  int* i = new_int(57);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(23);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);

  assert(compare_int_ptr(hash_table_find(hash_table,new_int(75))->cargo,new_int(75)) == 0);
  assert(hash_table_find(hash_table,new_int(775))==NULL);

  hash_table_deallocation(hash_table,dealloc_node);
}

void test_hashtable_delete_on_int_ptr() {
  List temp;
  HashTable hash_table = NULL;
  hash_table_init_struct(&hash_table,HASHDIM,hash_function_int_ptr,compare_int_ptr);
  int* i = new_int(3);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(25);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(8);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);
  i = new_int(74);
  assert(compare_int_ptr(hash_table_insert(hash_table,i,i)->cargo,i) == 0);

  // list with one node
  assert((temp = hash_table_delete(hash_table,new_int(75))) != NULL);
  assert(hash_table_find(hash_table,new_int(75)) == NULL);
  dealloc_node(temp);

  // list with two node: deletion first node
  assert((temp = hash_table_delete(hash_table,new_int(25))) != NULL);
  assert(hash_table_find(hash_table,new_int(25)) == NULL);
  dealloc_node(temp);

  // list with two node: deletion second node
  assert((temp = hash_table_delete(hash_table,new_int(8))) != NULL);
  assert(hash_table_find(hash_table,new_int(8)) == NULL);
  dealloc_node(temp);

  hash_table_deallocation(hash_table,dealloc_node);
}

int main(int argc, char const *argv[]) {
  start_tests(" Hashtable");
  test(test_hashtable_insert_on_int_ptr);
  test(test_hashtable_search_on_int_ptr);
  test(test_hashtable_delete_on_int_ptr);
  end_tests();
  return 0;
}
