#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "binary_search_tree.h"
#include "../../utility/test.h"
#include "../../utility/record_utility.h"

#define CASUAL_KEY_LENGTH 1000000
#define RECORD_LENGTH 20000000

/* -------HELPER FUNCTIONS------- */
void swap(void** e1, void** e2) {
  void* tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}

void dealloc_record(Tree tree){
  if(tree!=NULL) {
    free(tree);
  }
}

/* -------TESTS------- */
Tree test_tree_insert(Record** array,int size,int field){
  Tree tree = NULL;
  for(int i=0;i<size;++i){
    if(field == 1)  tree_insert_element(&tree,array[i]->field1,array[i],compare_string);
    else if(field == 2) tree_insert_element(&tree,&(array[i]->field2),array[i],compare_int);
    else if(field == 3) tree_insert_element(&tree,&(array[i]->field3),array[i],compare_float);
  }
  return tree;
}

void test_tree_find_on_record_file(Tree tree,Record** array,int field,int size){
  int ind;
  int casualLength = CASUAL_KEY_LENGTH-1;
  if (CASUAL_KEY_LENGTH > size) casualLength = size-1;
  srand(time(NULL));
  for(int i = casualLength;i >= 0;--i){
    ind = rand()%size;
    if(field == 1){
      tree_search_element(tree,array[ind]->field1,compare_string);
    }else if(field == 2){
      tree_search_element(tree,&(array[ind]->field2),compare_int);
    }else if(field == 3){
      tree_search_element(tree,&(array[ind]->field3),compare_float);
    }
    --size;
    swap((void**)&(array[ind]),(void**)&(array[size]));
  }
}

void test_tree_delete_on_record_file(Tree* tree,Record** array,int field,int size){
  Tree temp = NULL;
  int ind;
  int casualLength = CASUAL_KEY_LENGTH-1;
  if (CASUAL_KEY_LENGTH > size) casualLength = size-1;
  for(int i = casualLength;i >= 0;--i){
    ind = rand()%size;
    if(field == 1){
      temp = tree_delete_element(tree,array[ind]->field1,compare_string);
    }else if(field == 2){
      temp = tree_delete_element(tree,&(array[ind]->field2),compare_int);
    }else if(field == 3){
      temp = tree_delete_element(tree,&(array[ind]->field3),compare_float);
    }
    --size;
    swap((void**)&(array[ind]),(void**)&(array[size]));
    dealloc_record(temp);
  }
}

void test_tree_on_record_file(int field) {
  Record** array;
  int size;
  array = read_data(&size,RECORD_LENGTH);

  start_timer("\tInsert");
  Tree tree = test_tree_insert(array,size,field);
  end_timer();

  start_timer("\tFind");
  test_tree_find_on_record_file(tree,array,field,size);
  end_timer();

  start_timer("\tDelete");
  test_tree_delete_on_record_file(&tree,array,field,size);
  end_timer();

  dictonary_dealloc_record((void**) array, size);
  tree_dealloc(tree,dealloc_record);
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

  test_tree_on_record_file(field);

  return 0;
}
