#include "heap_sort.h"

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
* This function returns, using the properties of the heap, the left index
* of the child node.
*/
int heap_left_child(int i){
    return (2*i)+1;
}

/*
* This function returns, using the properties of the heap, the right index
* of the child node.
*/
int heap_right_child(int i){
    return (2*i)+2;
}

/*
* This functions returns the maximum element index between the node,
* the right child and left child
*/
int max_index_center_left_right(void** array,int i,int size,CompFunction compare){
    int left = heap_left_child(i);
    int right = heap_right_child(i);
    int max;
    if(left < size && compare(array[left],array[i]) > 0){
        max = left;
    }else{
        max = i;
    }
    if(right < size && compare(array[right],array[max]) > 0){
        max = right;
    }
    return max;
}

/*
*  This function fix the element in the i position into the heap.
*/
void heapify(void** array,int i,int size,CompFunction compare){
  int largest = max_index_center_left_right(array,i,size,compare);
  if(largest != i){
    swap(&array[i],&array[largest]);
    heapify(array,largest,size,compare);
  }
}

/*
* Converts the array into a heap
*/
void build_heap(void** array,int size,CompFunction compare){
  for(int i=size/2;i >= 0; --i){
    heapify(array,i,size,compare);
  }
}

/*
 * Heapsort divides its input into a sorted and an unsorted region,
 * and it iteratively shrinks the unsorted region by extracting the largest element
 * and moving that to the sorted region.
 * The improvement consists of the use of a
 * heap data structure rather than a linear-time search to find the maximum
 * array: vector on which to operate
 * size: array size
 * compare: comparison function between two elements of the array
 */
void heap_sort(void** array, int size, CompFunction compare) {
  if(size > 0){
    build_heap(array,size,compare);
    for(int i=size-1;i>=0;--i){
      swap(&array[0],&array[i]);
      heapify(array,0,i,compare);
    }
  }
}
