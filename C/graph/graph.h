#ifndef __GRAPH_H_KEIXJ4PDU3__
#define __GRAPH_H_KEIXJ4PDU3__
#include <float.h>
#include "../dictionary/hashtable/hash_table.h"
#include "heap_min.h"

#define INFINITE (FLT_MAX/2);

/* -------ENUMERATIONS------- */
typedef enum {UNDIRECTED=0,DIRECTED} graph_type;
typedef enum {WHITE=0,GRAY=1,BLACK=2} vertex_color;

/* -------POINTER TO FUNCTION------- */
typedef void (*StronglyConnectedFunction)(int);
typedef void (*DeallocKeyVertex)(void*);

/* -------VERTEX STRUCT------- */
typedef struct Vertex{
    void* key;
    void* param;
    HashTable hash_table_adj;
}Vertex_t, *Vertex_p;

/* -------ADJLISTNODE STRUCT------- */
typedef struct AdjlistNode{
    float edge_weight;
    Vertex_p vertex;
}AdjlistNode_t, *AdjlistNode_p;

/* -------GRAPH STRUCT------- */
typedef struct Graph{
    graph_type type;
    HashTable hash_table_vertex;
}Graph_t, *Graph_p;

/* -------DFS STRUCT------- */
//structure for passing parameter
typedef struct ParamDfs{
  vertex_color color;
  int d;
  int f;
  Vertex_p parent;
}ParamDfs_t, *ParamDfs_p;

typedef struct ParamDfsVisit{
  int* time;
  Vertex_p parent;
  int* counter;
}ParamDfsVisit_t, *ParamDfsVisit_p;

/* -------STRONGLY CONNECTED PARTS STRUCT------- */
typedef struct ParamDfsConn{
  int* time;
  StronglyConnectedFunction function;
}ParamDfsConn_t, *ParamDfsConn_p;

/* -------DIJKSTRA STRUCT------- */
typedef struct ParamDijkstra{
  float d;
  Vertex_p parent;
}ParamDijkstra_t, *ParamDijkstra_p;

/* -------PROTOTYPES------- */
// This function initializes the graph and the hashtable vertex.
void graph_init(Graph_p* graph,graph_type type,HashFunction hash,int hash_table_size,CompFunction compare);
// This function inserts a new vertex in the graph.
Vertex_p graph_insert_vertex(Graph_p graph,void* key);
// This function inserts an edge between two vertex.
void graph_insert_edge(Graph_p graph,void* key_vertex,void* key_adj,float edge_weight);
// This fuction makes a dfs visit on the graph
void graph_dfs(Graph_p graph);
// This function is the core of the dfs, whenever it is calleed,
// corresponds to a new tree in the forest
int graph_dfs_visit(Vertex_p vertex,int* time_p);
// This fuction makes a dfs visit on the graph and runs the function on every StronglyConnectedFunctions
void graph_strongly_connected(Graph_p graph,StronglyConnectedFunction function);
// The function performs dijkstra on the graph
void graph_dijkstra(Graph_p graph,void* s_vertex);
//  The function prints the vertices of a shortest path from a source vertex to another,after having made Dijkstra
float graph_dijkstra_min_distance(Graph_p graph,void* s_vertex,void* v_vertex,IteratorFunction print);
// Unique function to print a specific minimum path.
float graph_dijkstra_min_path(Graph_p graph,void* s_vertex,void* v_vertex,IteratorFunction print);
// Function for deallocate the Dijkstra's struct parameters
void graph_dealloc_dijkstra_param(Graph_p graph);
// This function prints the graph
void graph_print(Graph_p graph,IteratorFunction print);
// This function deallocates the graph
void graph_dealloc(Graph_p graph,DeallocKeyVertex dealloc);
#endif
