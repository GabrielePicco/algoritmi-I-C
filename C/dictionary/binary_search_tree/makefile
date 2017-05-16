include ../makefile.vars

all: record test

record: tree_test_record.o binary_search_tree.o record_utility.o test.o
	$(CC) $(CFLAGS)  -o record tree_test_record.o binary_search_tree.o test.o record_utility.o

test: tree_unit_test.o binary_search_tree.o test.o unit_test_utility.o
	$(CC) $(CFLAGS) -o test tree_unit_test.o binary_search_tree.o test.o unit_test_utility.o

tree_test_record.o: tree_test_record.c binary_search_tree.h ../../utility/test.h ../../utility/record_utility.h
	$(CC) $(CFLAGS) -c tree_test_record.c

tree_unit_test.o: tree_unit_test.c binary_search_tree.h ../../utility/test.h ../../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c tree_unit_test.c

binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	$(CC) $(CFLAGS) -c binary_search_tree.c

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
