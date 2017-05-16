#include <stdlib.h>
#include "heap_min.h"

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
 * Function to initialize the heap
 */
void heap_min_init(HeapMin_p* heap,int heapArraySize,size_t dim,CompFunction compare){
    *heap = (HeapMin_p)malloc(sizeof(HeapMin_t));
    (*heap)->inserted_elem_count = 0;
    (*heap)->compare = compare;
    (*heap)->array = (void**)malloc(sizeof(dim)*heapArraySize);
}

/*
 * This function returns, using the properties of the heap, the index
 * of the left child node.
 */
int heap_left_child(int i){
    return (2*i)+1;
}

/*
 * This function returns, using the properties of the heap, the index
 * of the right child node.
 */
int heap_right_child(int i){
    return (2*i)+2;
}

/*
 * This functions returns the maximum index between the index of the node,
 * the index of the right child and the index of the left child
 */
int min_index_center_left_right(void** array,int i,int size,CompFunction compare){
    int left = heap_left_child(i);
    int right = heap_right_child(i);
    int min;
    if(left < size && compare(array[left],array[i]) < 0){
        min = left;
    }else{
        min = i;
    }
    if(right < size && compare(array[right],array[min]) < 0){
        min = right;
    }
    return min;
}

/*
 *  This function fix the element in the i position with the heap properties.
 */
void heapify(void** array,int i,int size,CompFunction compare){
    int smallest = min_index_center_left_right(array,i,size,compare);
    if(smallest != i){
        swap(&array[i],&array[smallest]);
        heapify(array,smallest,size,compare);
    }
}

/*
 * Converts the array into a heap
 */
void heap_build(HeapMin_p heap){
    for(int i=heap->inserted_elem_count/2;i >= 0; --i){
        heapify(heap->array,i,heap->inserted_elem_count,heap->compare);
    }
}

/*
 * The function inserts an element in the heap.
 * heap: the heap
 * date: generic pointer that contains the element to be inserted_elem_count
 */
void heap_insert(HeapMin_p heap,void* date){
    heap->array[heap->inserted_elem_count++] = date;
}

/*
 * Function for extracting the minimum element from the heap.
 * return: generic pointer that contains the minimum element
 */
void* heap_extract_min(HeapMin_p heap){
    void* tmp = heap->array[--heap->inserted_elem_count];
    heap->array[heap->inserted_elem_count] = heap->array[0];
    heap->array[0] = tmp;
    tmp = heap->array[heap->inserted_elem_count];
    heapify(heap->array,0,heap->inserted_elem_count,heap->compare);
    return tmp;
}

/*
 * Function for deallocate the heap
 */
void heap_delete(HeapMin_p heap){
    free(heap->array);
}
