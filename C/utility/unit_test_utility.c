#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "unit_test_utility.h"

/* -------RECORD HELPER FUNCTION */
int compare_int_ptr(void* ptr1, void* ptr2) {
  int i1 =  *(int*)ptr1;
  int i2 =  *(int*)ptr2;

  if(i1<i2) {
    return -1;
  }

  if(i1==i2) {
    return 0;
  }

  return 1;
}

int* new_int(int value) {
  int* result = (int*) malloc(sizeof(int));
  *result = value;
  return result;
}

/*
 * The function verifies the correctness and deallocate structures
 */
void assert_and_dealloc_test(void** array, int size){
 for(int i=0; i<size; ++i) {
   if (i < (size-1)){
   assert(compare_int_ptr(array[i], array[i+1])<= 0);
   }
  free(array[i]);
 }
 free(array);
}
