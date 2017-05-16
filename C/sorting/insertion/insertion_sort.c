#include "insertion_sort.h"
#include <stdio.h>

/*
 * Given two pointers, reverses the content
 * e1: pointer to the first value
 * e2: pointer to the second value
 */
void swap(void** e1, void** e2) {
    void* tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}

/*
 * The function sorts the array.
 * array: the array to search
 * size: size of the array
 * pos: position from which to begin the search
 * compare: comparison function between two elements of the array
 */
void insertion(void** array, int size, int pos, CompFunction compare) {
  for(int i=pos; i > 0 && (compare(array[i], array[i-1])<0); i--) {
    swap(&array[i-1], &array[i]);
  }
}

/*
 * Function to starts insertion sort.
 * array: the array to search
 * size: size of the array
 * compare: comparison function between two elements of the array
 */
void insertion_sort(void** array, int size, CompFunction compare) {
  for(int i=1; i<size; ++i) {
    insertion(array, size, i, compare);
  }
}
