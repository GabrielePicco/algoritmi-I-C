#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quick_sort.h"
#include "../../utility/test.h"
#include "../../utility/record_utility.h"

#define ARRAY_LENGTH 20000000

/* -------TESTS------- */
void test_quick_sort_on_Record_array(int field) {
  int size;
  Record** array = read_data(&size,ARRAY_LENGTH);

  start_timer(" Quick sort");
  if(field == 1){
    quick_sort((void**) array, size, compare_field1_ptr);
  }else if(field == 2){
    quick_sort((void**) array, size, compare_field2_ptr);
  }else if(field == 3){
    quick_sort((void**) array, size, compare_field3_ptr);
  }
  end_timer();

  assert_and_dealloc_record((void**) array, field, size);
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

  test_quick_sort_on_Record_array(field);
  printf("\n<<-- Sorted by field%d-->>\n\n",field);
  return 0;
}
