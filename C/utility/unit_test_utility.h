#ifndef __UNIT_TEST_UTILITY_H__KJAHC38DJ__
#define __UNIT_TEST_UTILITY_H__KJAHC38DJ__

// Compare two integer
int compare_int_ptr(void* ptr1, void* ptr2);
// Return a pointer to new int
int* new_int(int value);
// The function verifies the correctness and deallocate structures
void assert_and_dealloc_test(void** array, int size);
#endif
