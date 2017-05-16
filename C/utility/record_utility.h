#ifndef __RECORD_UTILITY_H__KJAHC38DJ__
#define __RECORD_UTILITY_H__KJAHC38DJ__

#define STRING_LENGTH 30

/* -------RECORD STRUCT------- */
typedef struct{
  int id;
  char* field1;
  int field2;
  float field3;
}Record;

/* -------RECORD HELPER FUNCTION------- */
void print_record_ptr(void* ptr1);
int compare_field1_ptr(void* ptr1, void* ptr2);
int compare_field2_ptr(void* ptr1, void* ptr2);
int compare_field3_ptr(void* ptr1, void* ptr2);
int compare_float(void* ptr1, void* ptr2);
int compare_int(void* ptr1, void* ptr2);
int compare_string(void* ptr1, void* ptr2);
// The function reads the Records.cvs file
Record** read_data(int* size,int desiredSize);
// This function is used by sorting algorithm. It verifies the correctness and deallocates the structures
void assert_and_dealloc_record(void** array, int field, int size);
// This function is used by dictonary. It deallocates the structures
void dictonary_dealloc_record(void** array, int size);
#endif
