#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "quick_sort.h"
#include "../../utility/test.h"
#include "../../utility/unit_test_utility.h"

#define TESTDIM 20000000

/* -------TESTS------- */
void test_quick_sort_on_null_array() {
  int* array = NULL;
  quick_sort((void**) array,0,compare_int_ptr);
  assert(array == NULL);
}

void test_quick_sort_on_empty_array() {
  int array[1];
  quick_sort((void**) array, 0, compare_int_ptr);
}

void test_quick_sort_on_full_ptr_array() {
  int** array = (int**)malloc(sizeof(int*)*TESTDIM);
  srand(time(NULL));
  for(int i=0;i<TESTDIM;++i){
    array[i] = new_int(rand());
  }

  quick_sort((void**) array,TESTDIM, compare_int_ptr);

  assert_and_dealloc_test((void**) array, TESTDIM);

}

int main(int argc, char const *argv[]) {
  start_tests("Quick sort");

  test(test_quick_sort_on_null_array);
  test(test_quick_sort_on_empty_array);
  test(test_quick_sort_on_full_ptr_array);

  end_tests();
  return 0;
}
