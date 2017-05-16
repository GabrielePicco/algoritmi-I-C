#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "record_utility.h"

/* -------RECORD HELPER FUNCTION------- */
void print_record_ptr(void* ptr1){
  printf("\nField1: %s",((Record*)ptr1)->field1);
  printf("\nField2: %d",((Record*)ptr1)->field2);
  printf("\nField3: %f\n",((Record*)ptr1)->field3);
}

int compare_field1_ptr(void* ptr1, void* ptr2) {
  char* i1 = ((Record*)ptr1)->field1;
  char* i2 = ((Record*)ptr2)->field1;
  int str = strcmp(i1,i2);
  if(str > 0){
    return 1;
  }else if(str < 0){
    return -1;
  }
  return 0;
}

int compare_field2_ptr(void* ptr1, void* ptr2) {
  int i1 = ((Record*)ptr1)->field2;
  int i2 = ((Record*)ptr2)->field2;
  if(i1 < i2) {
    return -1;
  }
  if(i1 == i2) {
    return 0;
  }
  return 1;
}

int compare_field3_ptr(void* ptr1, void* ptr2) {
  float i1 =  ((Record*)ptr1)->field3;
  float i2 =  ((Record*)ptr2)->field3;
  if(i1<i2) {
    return -1;
  }
  if(i1==i2) {
    return 0;
  }
  return 1;
}

int compare_float(void* ptr1, void* ptr2) {
  float i1 =  *(float*)ptr1;
  float i2 =  *(float*)ptr2;
  if(i1<i2) {
    return -1;
  }
  if(i1==i2) {
    return 0;
  }
  return 1;
}

int compare_int(void* ptr1, void* ptr2) {
  int i1 =  *(int*)ptr1;
  int i2 =  *(int*)ptr2;
  if(i1<i2) {
    return -1;
  }
  if(i1==i2) {
    return 0;
  }
  return 1;
}

int compare_string(void* ptr1, void* ptr2) {
  char* i1 =  (char*)ptr1;
  char* i2 =  (char*)ptr2;
  int str = strcmp(i1,i2);
  if(str > 0){
    return 1;
  }else if(str < 0){
    return -1;
  }
  return 0;
}

 /*
 * The function reads the Records.cvs file
 * size: the effective size
 * desired_size: desired size, size = desidered_size if the records.csv file contains enough lines
 */
Record** read_data(int* size,int desired_size) {
  char* filename = "../../records.csv";
  char buf[STRING_LENGTH];
  Record** array = (Record**) malloc(sizeof(Record*)*desired_size);

  FILE* stream = fopen(filename, "r");
  if(stream == NULL){
    printf("ERROR. File records.csv not found !\n");
    exit(0);
  }

  int i = 0;
  int read_byte = 0;

  printf("\nLoading file Records.csv\n");
  while (i < desired_size && read_byte != -1){
    Record* result = (Record*) malloc(sizeof(Record));
    read_byte = fscanf(stream,"%d,%[^,],%d,%f",&result->id,buf,&result->field2,&result->field3);
    result->field1 = strdup(buf);
    if(read_byte!=-1){   // read_byte != EOF
      array[i] = result;
    }else{
      --i;
    }
    ++i;
  }
  fclose(stream);
  printf("\nDone loading file Records.csv !\n");
  *size = i;
  return array;
}

/*
 * This function is used by sorting algorithm. It verifies the correctness and deallocates the structures
 */
void assert_and_dealloc_record(void** array, int field, int size){
  for (int index = 0; index < size; ++index){
    if ((index+1) < size){
      if (field == 1){
        assert(compare_field1_ptr(array[index], array[index+1])<= 0);
      } else if (field == 2){
        assert(compare_field2_ptr(array[index], array[index+1])<= 0);
      } else if (field == 3){
        assert(compare_field3_ptr(array[index], array[index+1])<= 0);
      }
    }
    free(array[index]);
  }
  free(array);
}

/*
 * This function is used by dictonary. It deallocates the structures
 */
void dictonary_dealloc_record(void** array, int size){
 for (int i = 0; i < size; ++i){
   Record* result = (Record*)array[i];
   free(result->field1);
   free(result);
 }
 free(array);
}
