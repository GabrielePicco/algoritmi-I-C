#ifndef __HEAPMIN_H_KEIXJ4PDU3__
#define __HEAPMIN_H_KEIXJ4PDU3__

/* -------POINTER TO FUNCTION------- */
#ifndef __COMPFUNCTION_KEIXJ4PDU3__
#define __COMPFUNCTION_KEIXJ4PDU3__
typedef int (*CompFunction)(void*, void*);
#endif

/* -------HEAPMIN STRUCT------- */
typedef struct HeapMin{
    int inserted_elem_count;
    void** array;
    CompFunction compare;
}HeapMin_t,*HeapMin_p;

/* -------PROTOTYPES------- */
// Function to initialize the heap
void heap_min_init(HeapMin_p* heap,int heapArraySize,size_t dim,CompFunction compare);
// The function inserts an element in the heap.
void heap_insert(HeapMin_p heap,void* date);
// Converts the array into a heap
void heap_build(HeapMin_p heap);
// Function for extracting the minimum element from the heap
void* heap_extract_min(HeapMin_p heap);
// Function for deallocate the heap
void heap_delete(HeapMin_p heap);
#endif
