include ../makefile.vars

all: record test

record: quick_sort_test_record.o quick_sort.o test.o record_utility.o
	$(CC) $(CFLAGS)  -o record quick_sort_test_record.o quick_sort.o test.o record_utility.o

test: quick_sort_unit_test.o quick_sort.o test.o unit_test_utility.o
	$(CC) $(CFLAGS) -o test quick_sort_unit_test.o quick_sort.o test.o unit_test_utility.o

quick_sort_unit_test.o: quick_sort_unit_test.c quick_sort.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c quick_sort_unit_test.c

quick_sort_test_record.o: quick_sort_test_record.c quick_sort.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c quick_sort_test_record.c

quick_sort.o: quick_sort.c quick_sort.h
	$(CC) $(CFLAGS) -c quick_sort.c

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
