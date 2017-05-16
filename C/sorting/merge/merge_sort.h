#ifndef __MERGE_SORT_H_KEIXJ4PDU3__
#define __MERGE_SORT_H_KEIXJ4PDU3__

// Pointer to function for comparisons
typedef int (*CompFunction)(void*, void*);

/* -------PROTOTYPES------- */
// Function to starts merge sort
void merge_sort(void** array, int length, CompFunction compare);
#endif
