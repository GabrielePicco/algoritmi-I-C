include ../makefile.vars

all: record test

record: insertion_sort_test_record.o insertion_sort.o test.o record_utility.o
	$(CC) $(CFLAGS)  -o record insertion_sort_test_record.o insertion_sort.o test.o record_utility.o

test: insertion_sort_unit_test.o insertion_sort.o test.o unit_test_utility.o
	$(CC) $(CFLAGS) -o test insertion_sort_unit_test.o insertion_sort.o test.o unit_test_utility.o

insertion_sort_unit_test.o: insertion_sort_unit_test.c insertion_sort.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c insertion_sort_unit_test.c

insertion_sort_test_record.o: insertion_sort_test_record.c insertion_sort.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c insertion_sort_test_record.c

insertion_sort.o: insertion_sort.c insertion_sort.h
	$(CC) $(CFLAGS) -c insertion_sort.c

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
