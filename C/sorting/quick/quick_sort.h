#ifndef __QUICK_SORT_H_KEIXJ4PDU3__
#define __QUICK_SORT_H_KEIXJ4PDU3__

// Pointer to function for comparisons
typedef int (*CompFunction)(void*, void*);

/* -------PROTOTYPES------- */
// Function to starts quick sort
void quick_sort(void** array, int size, CompFunction compare);
#endif
