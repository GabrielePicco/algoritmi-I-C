#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "insertion_sort.h"
#include "../../utility/test.h"
#include "../../utility/unit_test_utility.h"

#define TESTDIM 2000

/* -------TESTS------- */
void test_insertion_sort_on_null_array() {
  int* array = NULL;
  insertion_sort((void**) array, 0, compare_int_ptr);
  assert(array == NULL);
}

void test_insertion_sort_on_empty_array() {
  int array[1];
  insertion_sort((void**) array, 0, compare_int_ptr);
}

void test_insertion_sort_on_full_ptr_array() {
  int** array = (int**)malloc(sizeof(int*)*TESTDIM);
  srand(time(NULL));
  for(int i=0;i<TESTDIM;++i){
    array[i] = new_int(rand());
  }

  insertion_sort((void**) array, TESTDIM, compare_int_ptr);

  assert_and_dealloc_test((void**) array, TESTDIM);
}

int main(int argc, char const *argv[]) {
  start_tests("Insertion sort");

  test(test_insertion_sort_on_null_array);
  test(test_insertion_sort_on_empty_array);
  test(test_insertion_sort_on_full_ptr_array);

  end_tests();
  return 0;
}
