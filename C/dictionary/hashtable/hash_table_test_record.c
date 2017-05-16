#include <assert.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#include "../../utility/test.h"
#include "../../utility/record_utility.h"

#define HASHDIM 11
#define CASUAL_KEY_LENGTH 1000000
#define RECORD_LENGTH 20000000

/* -------HELPER FUNCTIONS------- */
/*
 * Hash function for string. The value val(word) of a word
 * is calculated adding the ASCII code of the characters.
 */
int hash_function_string(void* key, int size){
  char* word = (char*) key;
  int val = 0;
  for (int i = 0; i < strlen(word); ++i){
    val += abs((int)word[i]);
  }
  return val % size;
}

void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}

/*
 * Hash function for float. The value val(x), with x float, is calculated
 * by multiplying the value for 1000 in order to include the first three
 * decimal digits for a better distinction between values.
 */
int hash_function_float(void* key, int size){
  return ((int)((*(float*)key)*1000)) % size;
}

// Hash function for integer
int hash_function_int(void* key, int size){
  return *(int*)key % size;
}

void dealloc_record(List node){
  if(node != NULL) {
    free(node);
  }
}

void print_record(void* ptr1, void* ptr2){
  print_record_ptr(ptr1);
}

/* -------TESTS------- */
HashTable test_hashtable_insert(Record** array,int size,int field){
  HashTable hash_table = NULL;
  if(field == 1) hash_table_init_struct(&hash_table,HASHDIM,hash_function_string,compare_string);
  else if(field == 2) hash_table_init_struct(&hash_table,HASHDIM,hash_function_int,compare_int);
  else if(field == 3) hash_table_init_struct(&hash_table,HASHDIM,hash_function_float,compare_float);
  for(int i=0;i<size;++i){
    if(field == 1) hash_table_insert(hash_table,array[i]->field1,array[i]);
    else if(field == 2) hash_table_insert(hash_table,&(array[i]->field2),array[i]);
    else if(field == 3) hash_table_insert(hash_table,&(array[i]->field3),array[i]);
  }
  return hash_table;
}

void test_hashtable_find_on_record_file(HashTable hash_table,Record** array,int field,int size){
  int ind;
  int casualLength = CASUAL_KEY_LENGTH-1;
  if (CASUAL_KEY_LENGTH > size) casualLength = size-1;
  srand(time(NULL));
  for(int i = casualLength;i >= 0;--i){
    ind = rand()%size;
    if(field == 1){
      hash_table_find(hash_table,array[ind]->field1);
    }else if(field == 2){
      hash_table_find(hash_table,&(array[ind]->field2));
    }else if(field == 3){
      hash_table_find(hash_table,&(array[ind]->field3));
    }
    --size;
    swap((void**)&(array[ind]),(void**)&(array[size]));
  }
}

void test_hashtable_delete_on_record_file(HashTable hash_table,Record** array,int field,int size){
  List temp = NULL;
  int ind;
  int casualLength = CASUAL_KEY_LENGTH-1;
  if (CASUAL_KEY_LENGTH > size) casualLength = size-1;
  for(int i = casualLength;i >= 0;--i){
    ind = rand()%size;
    if(field == 1){
      temp = hash_table_delete(hash_table,array[ind]->field1);
    }else if(field == 2){
      temp = hash_table_delete(hash_table,&(array[ind]->field2));
    }else if(field == 3){
      temp = hash_table_delete(hash_table,&(array[ind]->field3));
    }
    --size;
    swap((void**)&(array[ind]),(void**)&(array[size]));
    dealloc_record(temp);
  }
}

void test_hashtable_on_record_file(int field) {
  Record** array;
  int size;
  array = read_data(&size,RECORD_LENGTH);

  start_timer("\tInsert");
  HashTable hash_table = test_hashtable_insert(array,size,field);
  end_timer();

  start_timer("\tFind");
  test_hashtable_find_on_record_file(hash_table,array,field,size);
  end_timer();

  start_timer("\tDelete");
  test_hashtable_delete_on_record_file(hash_table,array,field,size);
  end_timer();

  dictonary_dealloc_record((void**) array, size);
  hash_table_deallocation(hash_table,dealloc_record);
}

int main(int argc, char const *argv[]) {
  int field = -1;
  if (argc == 2){
    if (strcmp(argv[1], "field1") == 0){
      field = 1;
    } else if (strcmp(argv[1], "field2") == 0){
      field = 2;
    } else if (strcmp(argv[1], "field3") == 0){
      field = 3;
    }
  }
  if (field == -1) {
    printf("ERROR. Compile with paramater field1 (string) or field2 (integer) or field3 (float)\n");
    exit(1);
  }

  test_hashtable_on_record_file(field);

  return 0;
}
