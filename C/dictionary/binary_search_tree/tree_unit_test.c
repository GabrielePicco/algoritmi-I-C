#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "binary_search_tree.h"
#include "../../utility/test.h"
#include "../../utility/unit_test_utility.h"

/* -------HELPER FUNCTIONS------- */
void deallocNode(Tree tree){
  if(tree!=NULL) {
    free(tree);
  }
}

void print_int_ptr(void* ptr1) {
  if(ptr1!=NULL)printf("- %d -",*(int*)ptr1);
}

/* -------TESTS------- */
void test_tree_insertion_on_int_ptr() {
  Tree tree = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(23);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  tree_dealloc(tree,deallocNode);
}

void test_tree_min_on_int_ptr() {
  Tree tree = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(23);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  assert(compare_int_ptr(tree_find_min(tree)->cargo,new_int(12)) == 0);

  tree_dealloc(tree,deallocNode);
}

void test_tree_max_on_int_ptr() {
  Tree tree = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(23);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  assert(compare_int_ptr(tree_find_max(tree)->cargo,new_int(75)) == 0);

  tree_dealloc(tree,deallocNode);
}

void test_tree_succ_on_int_ptr() {
  Tree tree = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(63);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  // root
  assert(compare_int_ptr(tree_successor(tree)->cargo,new_int(63)) == 0);
  // left child with no right child
  assert(compare_int_ptr(tree_successor(tree_search_element(tree,new_int(12),compare_int_ptr))->cargo,new_int(57)) == 0);
  // right child with no right child
  assert((tree_successor(tree_search_element(tree,new_int(75),compare_int_ptr))) == NULL);

  tree_dealloc(tree,deallocNode);
}

void test_tree_search_on_int_ptr() {
  Tree tree = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(23);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  assert(compare_int_ptr(tree_search_element(tree,new_int(75),compare_int_ptr)->cargo,new_int(75)) == 0);
  assert(tree_search_element(tree,new_int(755),compare_int_ptr)==NULL);

  tree_dealloc(tree,deallocNode);
}

void test_tree_delete_on_int_ptr() {
  Tree tree = NULL;
  Tree temp = NULL;
  int* i = new_int(57);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(12);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(75);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(63);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);
  i = new_int(81);
  assert(compare_int_ptr(tree_insert_element(&tree,i,i,compare_int_ptr)->cargo,i) == 0);

  //node with two child
  assert((temp = tree_delete_element(&tree,new_int(75),compare_int_ptr))!= NULL);
  deallocNode(temp);
  //one child
  assert((temp = tree_delete_element(&tree,new_int(81),compare_int_ptr))!= NULL);
  deallocNode(temp);
  //right leap
  assert((temp = tree_delete_element(&tree,new_int(63),compare_int_ptr))!= NULL);
  deallocNode(temp);
  //left leap
  assert((temp = tree_delete_element(&tree,new_int(12),compare_int_ptr))!= NULL);
  deallocNode(temp);
  //root
  assert((temp = tree_delete_element(&tree,new_int(57),compare_int_ptr))!= NULL);
  deallocNode(temp);

  tree_dealloc(tree,deallocNode);
}


int main(int argc, char const *argv[]) {
  start_tests("Tree structure");

  test(test_tree_insertion_on_int_ptr);
  test(test_tree_min_on_int_ptr);
  test(test_tree_max_on_int_ptr);
  test(test_tree_succ_on_int_ptr);
  test(test_tree_search_on_int_ptr);
  test(test_tree_delete_on_int_ptr);

  end_tests();
  return 0;
}
