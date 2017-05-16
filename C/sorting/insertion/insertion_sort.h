#ifndef __INSERTION_SORT_H_KEIXJ4PDU3__
#define __INSERTION_SORT_H_KEIXJ4PDU3__

// Pointer to function for comparisons
typedef int (*CompFunction)(void*, void*);

/* -------PROTOTYPES------- */
// Function to starts insertion sort
void insertion_sort(void** array, int size, CompFunction compare);
#endif
