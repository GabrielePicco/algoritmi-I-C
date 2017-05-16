#include "quick_sort.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
 * About two pointers, reverses the content
 * e1: pointer to the first value
 * e2: pointer to the second value
 */
void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}

/*
 * Returns the index ind of the pivot such that all the elements in the array [0..(ind-1)] < pivot and array[1+ind..(size)] > pivot.
 * start: start address
 * end: the end of the array address
 * compare: comparison function between two elements of the array
 */
int partition(void** array, int start, int end, CompFunction compare) {
  int indPivot = start;
  void* pivot = array[indPivot];
  ++start;
  while(start <= end){
    if(compare(array[start],pivot) < 0){
      ++start;
    }else{
      if(compare(array[end],pivot) > 0){
        --end;
      }else{
        swap(&array[start],&array[end]);
        ++start;
        --end;
      }
    }
  }
  swap(&array[indPivot],&array[end]);
  return end;
}

/*
 * This function randomly selects a pivot and replaces it with
 * the first element that will be the pivot of the partition function
 */
int partition_randomized(void** array, int start, int end, CompFunction compare) {
  int pivot = (rand()%(end-start))+start;
  swap(&array[start],&array[pivot]);
  return partition(array,start,end,compare);
}

/*
 * Function to starts quick sort.
 * start: start address
 * end: the end of the array address
 * compare: comparison function between two elements of the array
 */
void quick_sort_r(void** array, int start, int end, CompFunction compare) {
  if(end>start) {
    int pivot;
    pivot = partition_randomized(array,start,end,compare);
    quick_sort_r(array,start,pivot-1,compare);
    quick_sort_r(array,pivot+1,end,compare);
  }
}

/*
 * Support function with simpler parameters to handle recursion
 */
void quick_sort(void** array, int size, CompFunction compare) {
  srand(time(NULL));
  quick_sort_r(array,0,size-1,compare);
}
