include ../makefile.vars

all: record test

record: hash_table_test_record.o hash_table.o record_utility.o test.o list.o
	$(CC) $(CFLAGS)  -o record hash_table_test_record.o hash_table.o test.o record_utility.o list.o

test: hash_table_unit_test.o hash_table.o test.o unit_test_utility.o list.o
	$(CC) $(CFLAGS) -o test hash_table_unit_test.o hash_table.o test.o unit_test_utility.o list.o

hash_table_test_record.o: hash_table_test_record.c hash_table.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c hash_table_test_record.c

hash_table_unit_test.o: hash_table_unit_test.c hash_table.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c hash_table_unit_test.c

hash_table.o: hash_table.c hash_table.h list.h
	$(CC) $(CFLAGS) -c hash_table.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

record_utility.o: ../../utility/record_utility.c ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c ../../utility/record_utility.c

unit_test_utility.o: ../../utility/unit_test_utility.c ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c ../../utility/unit_test_utility.c

test.o: ../../utility/test.c ../../utility/test.h
	$(CC) $(CFLAGS) -c ../../utility/test.c

clean:
	rm -f record
	rm -f test
	rm -f *.o
