#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "../utility/test.h"
#include "../utility/unit_test_utility.h"

#define HASHDIM 11

/* -------HELPER FUNCTION------- */
int hash_function_int_ptr(void * key, int size) {
  return *(int * ) key % size;
}

void print_int(void * cargo, void * param) {
  printf("- %d -", * (int * ) cargo);
}

void print_strongly_connected(int num){
  printf("\nStrongly connected: element(%d)",num);
}

void assert_strongly_connected(int num){
  assert(num == 2);
}

/* -------TESTS------- */
void test_graph_insertion_on_int_ptr() {
  Graph_p graph;
  graph_init(&graph, UNDIRECTED, hash_function_int_ptr, HASHDIM, compare_int_ptr);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(3))->key,new_int(3)) == 0);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(5))->key,new_int(5)) == 0);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(7))->key,new_int(7)) == 0);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(12))->key,new_int(12)) == 0);

  graph_dealloc(graph,NULL);
}

void test_graph_insert_edge_on_int_ptr() {
  Graph_p graph;
  graph_init(&graph, UNDIRECTED, hash_function_int_ptr, HASHDIM, compare_int_ptr);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(3))->key,new_int(3)) == 0);
  assert(compare_int_ptr(graph_insert_vertex(graph, new_int(12))->key,new_int(12)) == 0);
  graph_insert_edge(graph, new_int(5), new_int(7), 5.0f);

  Vertex_p temp = (Vertex_p)hash_table_find(graph->hash_table_vertex,new_int(5))->cargo;
  assert(hash_table_find(temp->hash_table_adj,new_int(7)) != NULL);

  temp = (Vertex_p)hash_table_find(graph->hash_table_vertex,new_int(7))->cargo;
  assert(hash_table_find(temp->hash_table_adj,new_int(5)) != NULL);

  graph_dealloc(graph,NULL);
}

void test_graph_dfs_strongly_connected_on_int_ptr() {
  Graph_p graph;
  graph_init(&graph, UNDIRECTED, hash_function_int_ptr, HASHDIM, compare_int_ptr);
  graph_insert_edge(graph, new_int(1), new_int(13), 5.0f);
  graph_insert_edge(graph, new_int(2), new_int(7), 5.0f);
  graph_insert_edge(graph, new_int(3), new_int(11), 5.0f);
  graph_insert_edge(graph, new_int(20), new_int(70), 5.0f);
  graph_insert_edge(graph, new_int(5), new_int(9), 3.0f);

  graph_strongly_connected(graph,assert_strongly_connected);

  graph_dealloc(graph,NULL);
}

void test_graph_dijkstra_on_int_ptr() {
  Graph_p graph;
  graph_init(&graph, UNDIRECTED, hash_function_int_ptr, HASHDIM, compare_int_ptr);
  graph_insert_edge(graph, new_int(3), new_int(1), 5.0f);
  graph_insert_edge(graph, new_int(1), new_int(7), 5.0f);
  graph_insert_edge(graph, new_int(7), new_int(11), 5.0f);
  graph_insert_edge(graph, new_int(11), new_int(20), 5.0f);
  graph_insert_edge(graph, new_int(20), new_int(5), 3.0f);
  graph_insert_vertex(graph, new_int(100));

  assert(graph_dijkstra_min_path(graph,new_int(3),new_int(5),NULL) == 23.0f);
  assert(graph_dijkstra_min_path(graph,new_int(3),new_int(100),NULL) == -1);
  graph_insert_edge(graph, new_int(3), new_int(11), 3.0f);
  assert(graph_dijkstra_min_path(graph,new_int(3),new_int(5),NULL) == 11.0f);


  graph_dealloc(graph,NULL);
}


int main(int argc,
  const char * argv[]) {

  start_tests(" Graph structure");

  test(test_graph_insertion_on_int_ptr);
  test(test_graph_insert_edge_on_int_ptr);
  test(test_graph_dfs_strongly_connected_on_int_ptr);
  test(test_graph_dijkstra_on_int_ptr);

  end_tests();
  return 0;
}
