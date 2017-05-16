include ../makefile.vars

all: record test

record: merge_sort_test_record.o merge_sort.o test.o record_utility.o
	$(CC) $(CFLAGS)  -o record merge_sort_test_record.o merge_sort.o test.o record_utility.o

test: merge_sort_unit_test.o merge_sort.o test.o unit_test_utility.o
	$(CC) $(CFLAGS) -o test merge_sort_unit_test.o merge_sort.o test.o unit_test_utility.o

merge_sort_unit_test.o: merge_sort_unit_test.c merge_sort.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c merge_sort_unit_test.c

merge_sort_test_record.o: merge_sort_test_record.c merge_sort.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c merge_sort_test_record.c

merge_sort.o: merge_sort.c merge_sort.h
	$(CC) $(CFLAGS) -c merge_sort.c

test.o: ../../utility/test.c ../../utility/test.h
	$(CC) $(CFLAGS) -c ../../utility/test.c

record_utility.o: ../../utility/record_utility.c ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c ../../utility/record_utility.c

unit_test_utility.o: ../../utility/unit_test_utility.c ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c ../../utility/unit_test_utility.c

clean:
	rm -f record
	rm -f test
	rm -f *.o
