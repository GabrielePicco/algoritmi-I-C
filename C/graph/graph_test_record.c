#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "../utility/test.h"

#define STRING_LENGTH 50
#define HASHDIM 11

/* -------HELPER FUNCTIONS------- */
/*
 * Hash function for string. The value val(word) of a word
 * is calculated adding the ASCII code of the characters.
 */
int hash_function_string(void* key, int size){
  char* word = (char*) key;
  int val = 0;
  for (int i = 0; i < strlen(word); ++i){
    val += abs((int)word[i]);
  }
  return val % size;
}

int compare_string(void* ptr1, void* ptr2){
  char* i1 =  (char*)ptr1;
  char* i2 =  (char*)ptr2;
  int str = strcmp(i1,i2);
  if(str > 0){
    return 1;
  }else if(str < 0){
    return -1;
  }
  return 0;
}

void print_string(void * cargo, void * param){
  printf("- %s -", (char*) cargo);
}

void dealloc_key_vertex(void* key) {
  free((char*)key);
}

void print_strongly_connected(int num){
  printf("\nStrongly connected: element(%d)",num);
}

/* -------FUNCTIONS-------*/
/*
 * The function creates the vertices and edges of the graph
 */
void creat_graph(FILE* stream,Graph_p graph){
  char loc1[STRING_LENGTH],loc2[STRING_LENGTH];
  float dist;
  int readByte = 0;

  while (readByte != -1){
    readByte = fscanf(stream,"%[^,],%[^,],%f\n]",loc1,loc2,&dist);
    if (readByte != -1){
    graph_insert_edge(graph,strdup(loc1),strdup(loc2),dist);
    }
  }
}

/*
 * Function to read the file and create the graph
 */
Graph_p read_data_and_creat_graph(){
  char* filename = "../italian_dist_graph.csv";
  Graph_p graph;
  graph_init(&graph, UNDIRECTED, hash_function_string, HASHDIM, compare_string);

  FILE* stream = fopen(filename, "r");
  if(stream == NULL){
    printf("ERROR. File italian_dist_graph.csv not found !\n");
    exit(0);
  }

  printf("\nLoading file italian_dist_graph.csv and creating graph\n");
  creat_graph(stream,graph);
  fclose(stream);
  printf("\nCreated the graph!\n");

  return graph;
}

/* -------TESTS-------*/
void test_strongly_connected_on_record_file(Graph_p graph){
  start_timer("\tStrongly connected part dimension");
  graph_strongly_connected(graph,print_strongly_connected);
  end_timer();
}

void test_dijkstra_min_path_on_record_file(Graph_p graph,char* source,char* dest){
  source[0] = tolower(source[0]);
  dest[0] = tolower(dest[0]);
  start_timer("\tDijkstra min path");
  graph_dijkstra(graph,source);
  float distance = graph_dijkstra_min_distance(graph,source,dest,NULL);
  if(distance != -1)printf("\nDistance %s - %s: %.2f (Km)",source,dest,distance/1000);
  else  printf("\n<-- It does not exist a possible path between %s - %s -->",source,dest);
  end_timer();

  graph_dealloc_dijkstra_param(graph);
}

int main(int argc, const char * argv[]) {
    char source[STRING_LENGTH];
    char dest[STRING_LENGTH];
    printf("\nEnter the locations to calculate the shortest path:\n");
    printf("\nEnter first locality: ");
    scanf("%[^\n]s",source);
    getchar();
    printf("\nEnter second locality: ");
    scanf("%[^\n]s",dest);

    Graph_p graph = read_data_and_creat_graph();

    test_strongly_connected_on_record_file(graph);
    test_dijkstra_min_path_on_record_file(graph,source,dest);

    graph_dealloc(graph,dealloc_key_vertex);
    return 0;
}
