#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * The function copy the remaining elements of sub-array array[left..center]
 * or of sub-array array[center+1..right] in the queue of the vector "temp", if there are any.
 */
void insert (void** array, void** temp, int index_left_or_right, int center, int* index, CompFunction compare){
  while (index_left_or_right <= center) {
    temp[*index] = array[index_left_or_right];
    index_left_or_right++;
    (*index)++;
  }
}

/*
 * The function copy the temporary vector temp in array.
 */
void copy (void** array, void** temp, int left, int right, CompFunction compare){
  for (int i=left; i <= right; ++i) {
    array[i] = temp[i-left];
  }
}

/*
 * The function merges two sub-arrays of array moving into temporary vector temp
 * the minimum element between the two parties,
 * calls the functions insert and copy.
 * First subarray is array[left..center]
 * Second subarray is array[center+1..right]
 */
void merge(void** array, void** temp, int left, int center, int right, CompFunction compare) {
  int index_left = left, index_cen = center+1, index = 0;
    while (index_left <= center && index_cen <= right) {
      if ((compare(array[index_left],array[index_cen])<=0)) {
        temp[index] = array[index_left];
        index_left++;
      } else {
      temp[index] = array[index_cen];
      index_cen++;
      }
     index++;
    }

  insert (array, temp, index_left, center, &index, compare);
  insert (array, temp, index_cen, right, &index, compare);
  copy (array, temp, left, right, compare);
}

/*
 * The function divides the "array" vector in two parts,
 * sorts first and second halves,
 * calls the function merge.
 * array: vector on which to operate
 * temp: temporary vector
 * left: left index of sub-array of vector "array"
 * right: right index of sub-array of vector "array"
 * compare: comparison function between two elements of the array
 */
void merge_sort_ric(void** array, void** temp, int left, int right, CompFunction compare) {
  if (left < right) {
        int center = (left + right) / 2;
        merge_sort_ric(array, temp, left, center, compare);
        merge_sort_ric(array, temp, center+1, right, compare);
        merge(array, temp, left, center, right, compare);
  }
}

/*
 * Support function for the temporary vector create.
 * array: vector on which to operate
 * length: array length
 * compare: comparison function between two elements of the array
 */
void merge_sort(void** array, int length, CompFunction compare){
    void** temp = (void**) malloc (sizeof(void*)*(length));
    merge_sort_ric(array, temp, 0, (length-1), compare);
    free(temp);
}
