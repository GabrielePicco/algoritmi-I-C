include makefile.vars

all: record test

record: graph_test_record.o graph.o hash_table.o test.o heap_min.o list.o
	$(CC) $(CFLAGS)  -o record graph_test_record.o graph.o list.o test.o hash_table.o heap_min.o

test: graph_unit_test.o graph.o test.o unit_test_utility.o heap_min.o list.o graph.h hash_table.o
	$(CC) $(CFLAGS) -o test graph_unit_test.o graph.o test.o unit_test_utility.o list.o hash_table.o heap_min.o

graph_test_record.o: graph_test_record.c graph.h ../utility/test.h
	$(CC) $(CFLAGS) -c graph_test_record.c

graph_unit_test.o: graph_unit_test.c graph.h ../utility/test.h ../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c graph_unit_test.c

hash_table.o: ../dictionary/hashtable/hash_table.c ../dictionary/hashtable/hash_table.h
	$(CC) $(CFLAGS) -c ../dictionary/hashtable/hash_table.c

graph.o: graph.c graph.h ../dictionary/hashtable/hash_table.h heap_min.h
	$(CC) $(CFLAGS) -c graph.c

heap_min.o: heap_min.c heap_min.h
	$(CC) $(CFLAGS) -c heap_min.c

list.o: ../dictionary/hashtable/list.c ../dictionary/hashtable/list.h
	$(CC) $(CFLAGS) -c ../dictionary/hashtable/list.c

unit_test_utility.o: ../utility/unit_test_utility.c ../utility/unit_test_utility.h
	$(CC) $(CFLAGS) -c ../utility/unit_test_utility.c

test.o: ../utility/test.c ../utility/test.h
	$(CC) $(CFLAGS) -c ../utility/test.c

clean:
	rm -f record
	rm -f test
	rm -f *.o
