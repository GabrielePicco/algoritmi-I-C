#ifndef __HEAP_SORT_H_KEIXJ4PDU3__
#define __HEAP_SORT_H_KEIXJ4PDU3__

// Pointer to function for comparisons
typedef int (*CompFunction)(void*, void*);

/* -------PROTOTYPES------- */
/* Heapsort divides its input into a sorted and an unsorted region,
 * and it iteratively shrinks the unsorted region by extracting the largest element
 * and moving that to the sorted region.
 */
void heap_sort(void** array, int size, CompFunction compare);
#endif
