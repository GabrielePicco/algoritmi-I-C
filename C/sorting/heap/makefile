include ../makefile.vars

all: record test

record: heap_sort_test_record.o heap_sort.o test.o record_utility.o
	$(CC) $(CFLAGS)  -o record heap_sort_test_record.o heap_sort.o test.o record_utility.o

test: heap_sort_unit_test.o heap_sort.o test.o unit_test_utility.o
	$(CC) $(CFLAGS) -o test heap_sort_unit_test.o heap_sort.o test.o unit_test_utility.o

heap_sort_unit_test.o: heap_sort_unit_test.c heap_sort.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c heap_sort_unit_test.c

heap_sort_test_record.o: heap_sort_test_record.c heap_sort.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c heap_sort_test_record.c

heap_sort.o: heap_sort.c heap_sort.h
	$(CC) $(CFLAGS) -c heap_sort.c

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
