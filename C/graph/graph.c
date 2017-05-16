#include "graph.h"
#include <stdlib.h>

/*
 * This function initializes the graph and the hashtable vertex.
 * graph: the graph
 * graph_type: DIRECTED or INDIRECTED
 * hash: the hash function
 * hash_table_size: intial hash table size
 * compare: compare function
 */
void graph_init(Graph_p* graph, graph_type type, HashFunction hash, int hash_table_size, CompFunction compare) {
  *graph = (Graph_p) malloc(sizeof(Graph_t));
  (*graph)->type = type;
  (*graph)->hash_table_vertex = NULL;
  hash_table_init_struct(&((*graph)->hash_table_vertex), hash_table_size, hash, compare);
}

/*
 * This helper function allocates a new vertex and
 * initializes the hashtable of adjacents vertices of it.
 * hash: the hash function
 * hash_table_size: intial hash table size
 * compare: compare function
 * return: the allocated vertex
 */
Vertex_p new_vertex(HashFunction hash, int hash_table_size, CompFunction compare) {
  Vertex_p vertex = (Vertex_p) malloc(sizeof(Vertex_t));
  vertex->hash_table_adj = NULL;
  hash_table_init_struct(&(vertex->hash_table_adj), hash_table_size, hash, compare);
  return vertex;
}

/*
 * The function returns the number of vertex inserted
 * in the graph.
 */
int graph_num_vertex(Graph_p graph){
  return graph->hash_table_vertex->inserted_elem_count;
}

/*
 * This function inserts a new vertex in the graph.
 * graph: the graph
 * key: key to add
 * return: the inserted vertex
 */
Vertex_p graph_insert_vertex(Graph_p graph, void* key) {
  Vertex_p vertex = NULL;
  if (hash_table_find(graph->hash_table_vertex, key) == NULL) {
    vertex = new_vertex(graph->hash_table_vertex->hash, graph->hash_table_vertex->size, graph->hash_table_vertex->compare);
    vertex->key = key;
    hash_table_insert(graph->hash_table_vertex, key, vertex);
  }
  return vertex;
}

/*
 * This helper function allocate a new AdjlistNode
 * that is needed to the adjacency hashtable
 * for store the vertexAdj and the edge_weight.
 * edge_weight: weight of the edge
 * vertexAdj: the adjacent vertex
 * return: the new AdjlistNode
 */
AdjlistNode_p new_AdjlistNode(float edge_weight, Vertex_p vertexAdj) {
  AdjlistNode_p node = (AdjlistNode_p) malloc(sizeof(AdjlistNode_t));
  node->edge_weight = edge_weight;
  node->vertex = vertexAdj;
  return node;
}

/*
 * This helper function inserts an AdjlistNode in the adjacency hashtable
 * for store the vertexAdj and the edge_weight.
 * graph: the graph
 * vertex: the vertex
 * node: node with weight and the adjacenct vertex
 */
void graph_insert_adj_node(Graph_p graph, Vertex_p vertex, AdjlistNode_p node) {
  if (hash_table_find(vertex->hash_table_adj, node->vertex->key) == NULL) {
    hash_table_insert(vertex->hash_table_adj, node->vertex->key, node);
  }
}

/*
 * This function inserts an edge between two vertex.
 * If the leaders do not exist, it creates them.
 * If the graph is not directed also adds the mutual.
 * key_vertex: key of the first vertex
 * key_adj: key of the adjacenct vertex
 * edge_weight: weight of the edge
 */
void graph_insert_edge(Graph_p graph, void* key_vertex, void* key_adj, float edge_weight) {
  List temp = hash_table_find(graph->hash_table_vertex, key_vertex);
  if (temp != NULL) {
    Vertex_p vertex = (Vertex_p)(temp->cargo);
    temp = hash_table_find(graph->hash_table_vertex, key_adj);
    if (temp != NULL) {
      Vertex_p vertexAdj = (Vertex_p)(temp->cargo);
      AdjlistNode_p node = new_AdjlistNode(edge_weight, vertexAdj);
      graph_insert_adj_node(graph, vertex, node);

      if (graph->type == UNDIRECTED) {
        AdjlistNode_p nodeR = new_AdjlistNode(edge_weight, vertex);
        graph_insert_adj_node(graph, vertexAdj, nodeR);
      }
    } else {
      graph_insert_vertex(graph, key_adj);
      graph_insert_edge(graph, key_vertex, key_adj, edge_weight);
    }
  } else {
    graph_insert_vertex(graph, key_vertex);
    graph_insert_edge(graph, key_vertex, key_adj, edge_weight);
  }
}

/*
 * This helper function prints all adjacency vertex
 * cargo: the AdjlistNode_p
 * print: the print function
 */
void graph_internal_print_iterator(void* cargo, void* print) {
  IteratorFunction printCargo = (IteratorFunction) print;
  AdjlistNode_p node = (AdjlistNode_p) cargo;
  printCargo(node->vertex->key, NULL);
}

/*
 * This helper function prints all the vertex
 * cargo: the Vertex_p
 * print: the print function
 */
void graph_print_iterator(void* cargo, void* print) {
  IteratorFunction printCargo = (IteratorFunction) print;
  Vertex_p vertex = (Vertex_p) cargo;
  printf("\n");
  printCargo(vertex->key, NULL);
  printf(" --> ");

  hash_table_iterator(vertex->hash_table_adj, print, graph_internal_print_iterator);
}

/*
 * This function prints the graph
 * print: the print function
 */
void graph_print(Graph_p graph, IteratorFunction print) {
  hash_table_iterator(graph->hash_table_vertex, (void*)print, graph_print_iterator);
}

/*
 * This function is needed by graph_dealloc_iterator() to dealloc
 * the internal node of the adjacency hashtable
 * node: node to be dealloced
 */
void dealloc_adj_node(List node) {
  if (node != NULL) {
    AdjlistNode_p adjlistnode = (AdjlistNode_p)node->cargo;
    free(adjlistnode);
    free(node);
  }
}

/*
 * This function is needed to dealloc the internal node
 * of the vertex hashtable
 * node: node to be dealloced
 */
void dealloc_node(List node) {
  if (node != NULL) {
    free(node);
  }
}

/*
 * This function is needed for deallocated the dfs's structure parameter
 */
void dealloc_param_dfs(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p)cargo;
  ParamDfs_p param_dfs = (ParamDfs_p)vertex->param;
  free(param_dfs);
}

/*
 * This function is needed for deallocated the dijkstra's structure parameter
 */
void dealloc_param_dijkstra(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p)cargo;
  ParamDijkstra_p param_dk = (ParamDijkstra_p)vertex->param;
  free(param_dk);
}

/*
 * This helper function iterates for every vertex
 * cargo: the Vertex_p
 * param: the function for deallocation
 */
void graph_dealloc_iterator(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p) cargo;
  hash_table_deallocation(vertex->hash_table_adj,dealloc_adj_node);
  if(param != NULL){
    DeallocKeyVertex dealloc = (DeallocKeyVertex)param;
    dealloc(vertex->key);
  }
  free(vertex);
}

/*
 * This function deallocates the graph
 * graph: the graph
 * dealloc: pointer to the function for dealloc the vertex
 */
void graph_dealloc(Graph_p graph,DeallocKeyVertex dealloc){
  hash_table_iterator(graph->hash_table_vertex,(void*)dealloc,graph_dealloc_iterator);
  hash_table_deallocation(graph->hash_table_vertex,dealloc_node);
  free(graph);
}

/*
 * This helper function iterates for every AdjlistNode
 * cargo: the AdjlistNode_p
 * param: ParamDfsVisit that contain time and parent
 */
void graph_dfs_visit_iter(void* cargo, void* param) {
  AdjlistNode_p node = (AdjlistNode_p)cargo;
  Vertex_p vertex = node->vertex;
  ParamDfsVisit_p paramDfsVisit = (ParamDfsVisit_p)param;
  ParamDfs_p vertex_param = (ParamDfs_p)vertex->param;

  if(vertex_param->color == WHITE){
    vertex_param->parent = paramDfsVisit->parent;
    *(paramDfsVisit->counter) += graph_dfs_visit(vertex,paramDfsVisit->time);
  }
}

/*
 * This function is the core of the dfs, whenever it is calleed,
 * corresponds to a new tree in the forest
 * vertex: the vertex
 * time_p: pointer to a time counter
 */
int graph_dfs_visit(Vertex_p vertex,int* time_p){
  int counter = 1;
  ParamDfs_p vertex_param = (ParamDfs_p)vertex->param;
  ++(*time_p);
  vertex_param->d = *time_p;
  vertex_param->color = GRAY;

  ParamDfsVisit_p paramDfsVisit = (ParamDfsVisit_p)malloc(sizeof(ParamDfsVisit_t));
  paramDfsVisit->time = time_p;
  paramDfsVisit->parent = vertex;
  paramDfsVisit->counter = &counter;

  hash_table_iterator(vertex->hash_table_adj,paramDfsVisit,graph_dfs_visit_iter);

  vertex_param->color = BLACK;
  ++(*time_p);
  vertex_param->d = *time_p;

  free(paramDfsVisit);
  return counter;
}

/*
 * This helper function initially sets color to white and parent to NULL
 * cargo: the Vertex_p
 * param: ParamDfs that contain color,d,f,parent
 */
void graph_dfs_init(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p) cargo;

  ParamDfs_p paramDfs = (ParamDfs_p)malloc(sizeof(ParamDfs_t));
  paramDfs->color = WHITE;
  paramDfs->parent = NULL;

  vertex->param = paramDfs;
}

/*
 * This helper function iterates for every vertex
 * cargo: the Vertex_p
 * param: pointer to a time counter (time_p)
 */
void graph_dfs_iter(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p) cargo;
  int* time_p = (int*)param;
  ParamDfs_p vertex_param = (ParamDfs_p)vertex->param;

  if(vertex_param->color == WHITE){
    graph_dfs_visit(vertex,time_p);
  }

}

/*
 * This fuction makes a dfs visit on the graph
 * graph: the graph
 */
void graph_dfs(Graph_p graph){
  hash_table_iterator(graph->hash_table_vertex,NULL,graph_dfs_init);
  int time = 0;
  hash_table_iterator(graph->hash_table_vertex,&time,graph_dfs_iter);

  hash_table_iterator(graph->hash_table_vertex,NULL,dealloc_param_dfs);
}

/*
 * This helper function iterates for every vertex and calls the function on every strongly connected part
 * cargo: the Vertex_p
 * param: paramDfsConn that contain the StronglyConnectedFunction and a pointer to the time
 */
void graph_strongly_connected_iter(void* cargo, void* param) {
  int counter;
  Vertex_p vertex = (Vertex_p) cargo;
  ParamDfsConn_p paramDfsConn = (ParamDfsConn_p)param;
  int* time_p = paramDfsConn->time;
  StronglyConnectedFunction function = (StronglyConnectedFunction)paramDfsConn->function;
  ParamDfs_p vertex_param = (ParamDfs_p)vertex->param;

  if(vertex_param->color == WHITE){
    counter = graph_dfs_visit(vertex,time_p);
    function(counter);
  }
}

/*
 * This fuction makes a dfs visit on the graph and runs the function on every StronglyConnectedFunctions
 * graph: the graph
 * function: the StronglyConnectedFunction
 */
void graph_strongly_connected(Graph_p graph,StronglyConnectedFunction function){
  ParamDfsConn_p paramDfsConn = (ParamDfsConn_p)malloc(sizeof(ParamDfsConn_t));
  hash_table_iterator(graph->hash_table_vertex,NULL,graph_dfs_init);
  int time = 0;
  paramDfsConn->time = &time;
  paramDfsConn->function = function;
  hash_table_iterator(graph->hash_table_vertex,paramDfsConn,graph_strongly_connected_iter);
  free(paramDfsConn);

  hash_table_iterator(graph->hash_table_vertex,NULL,dealloc_param_dfs);
}

/*
 * This function compares the estimates of shortest paths of two vertices
 * ptr1: generic pointer that contains a vertex
 * ptr2: generic pointer that contains a vertex
 * return: 0 if are equals, 1 if the first is bigger and -1 if the first is smaller
 */
int compare_d_vertex(void* ptr1, void* ptr2) {
  Vertex_p v1 =  (Vertex_p)ptr1;
  Vertex_p v2 =  (Vertex_p)ptr2;
  ParamDijkstra_p v_param1 = (ParamDijkstra_p)v1->param;
  ParamDijkstra_p v_param2 = (ParamDijkstra_p)v2->param;
  if(v_param1->d < v_param2->d) return -1;
  if(v_param1->d == v_param2->d) return 0;
  return 1;
}

/*
 * The function initializes, with time O(V), the estimates
 * of shortest paths, the predecessors and inserts the vertices in the heap.
 * cargo: generic pointer that contains a vertex
 * param: generic pointer that contains a minimum heap
 */
void graph_dijkstra_init_single_source(void* cargo, void* param) {
  Vertex_p vertex = (Vertex_p) cargo;
  ParamDijkstra_p paramDijastra = (ParamDijkstra_p) malloc (sizeof(ParamDijkstra_p));
  paramDijastra->d = INFINITE;
  paramDijastra->parent = NULL;
  vertex->param = paramDijastra;

  HeapMin_p heap = (HeapMin_p)param;
  heap_insert(heap,vertex);
}

/*
 * The function checks if it is possible to improve the
 * estimate of a shortest path previously found.
 * A relaxation can reduce the value of the estimate of
 * the shortest path and can update the parent field of the vertex.
 * parent: vertex predecessor
 * vertex: the vertex
 * weight: weight of the edge_weight
 */
void relax(Vertex_p parent,Vertex_p vertex,float weigth){
  ParamDijkstra_p v_param_parent = (ParamDijkstra_p)parent->param;
  ParamDijkstra_p v_param = (ParamDijkstra_p)vertex->param;
  float sum = v_param_parent->d+weigth;
  if(v_param->d > sum){
    v_param->d = sum;
    v_param->parent = parent;
  }
}

/*
 * This support function recuperates the vertex and its predecessor
 * and calls the function relax() for the relaxation.
 * cargo: generic pointer that contains the vertex
 * param: generic pointer that contains the precedessor
 */
void graph_dijkstra_relax(void* cargo, void* param) {
  AdjlistNode_p node = (AdjlistNode_p)cargo;
  Vertex_p vertex = node->vertex;
  Vertex_p parent = (Vertex_p) param;
  relax(parent,vertex,node->edge_weight);
}

/*
 * The function performs dijkstra on the graph. It contains a min-priority queue of vertices.
 * The function initializes the queue (heap) and puts the vertices inside it; after it
 * puts the estimate of the shortest path to the source vertex to 0,
 * it extracts the vertex with minimum attribute d from the queue and it makes the relaxation
 * of the arcs from that vertex.
 * graph: the graph
 * vertex_source: source of the path
 */
void graph_dijkstra_v(Graph_p graph, Vertex_p vertex_source){
  HeapMin_p heap = NULL;
  Vertex_p vertex;
  heap_min_init(&heap,graph_num_vertex(graph),sizeof(Vertex_p),compare_d_vertex);
  hash_table_iterator(graph->hash_table_vertex,heap,graph_dijkstra_init_single_source);
  ParamDijkstra_p v_source_param = (ParamDijkstra_p)vertex_source->param;
  v_source_param->d = 0;

  while(heap->inserted_elem_count > 0){
    heap_build(heap);
    vertex = heap_extract_min(heap);
    hash_table_iterator(vertex->hash_table_adj,vertex,graph_dijkstra_relax);
  }
}

/*
 * Support function to perform Dijkstra. It recovers the source
 * vertex and calls graph_dijkstra_v().
 * graph: the graph
 * s_vertex: generec pointer that contains the source vertex
 */
void graph_dijkstra(Graph_p graph,void* s_vertex){
  List temp_s = hash_table_find(graph->hash_table_vertex,s_vertex);
  if(temp_s != NULL){
    graph_dijkstra_v(graph,(Vertex_p)temp_s->cargo);
  }else{
    printf("\nSource locality doesn't exist.\n");
    exit(0);
  }
}

/*
 * The function prints the vertices of a shortest path from a source vertex to another,
 * after having made Dijkstra.
 * graph: the graph
 * s_vertex: the source vertex
 * v_vertex: another vertex
 * print: function for print the minimum path or NULL
 * return: the minimum distance of the path
 */
float graph_dijkstra_min_distance_v(Graph_p graph,Vertex_p s_vertex,Vertex_p v_vertex,IteratorFunction print){
  float distance = 0;
  ParamDijkstra_p v_param = (ParamDijkstra_p)v_vertex->param;
  if(graph->hash_table_vertex->compare(s_vertex->key,v_vertex->key) == 0){
    if(print != NULL)print(s_vertex->key,NULL);
  }else{
    if(v_param->parent == NULL) return -1;
    distance = ((AdjlistNode_p)hash_table_find(v_param->parent->hash_table_adj,v_vertex->key)->cargo)->edge_weight;
    distance += graph_dijkstra_min_distance_v(graph,s_vertex,v_param->parent,print);
    if(print != NULL)print(v_vertex->key,NULL);
  }
  return distance;
}

/*
 * Support function for print the shortest path.
 * The function recovers the source vertex and another vertex and calls
 * the function graph_dijkstra_min_distance_v().
 * graph: the graph
 * s_vertx: generic pointer that contains the source vertex
 * v_vertx: generic pointer that contains another vertex
 * print: function to print the minimum path or NULL
 * return: the minimum distance between the two vertex
 */
float graph_dijkstra_min_distance(Graph_p graph,void* s_vertex,void* v_vertex,IteratorFunction print){
  float distance = -1;
  List temp_s = hash_table_find(graph->hash_table_vertex,s_vertex);
  List temp_v = hash_table_find(graph->hash_table_vertex,v_vertex);

  if (temp_s != NULL && temp_v != NULL) {
    distance = graph_dijkstra_min_distance_v(graph,(Vertex_p)temp_s->cargo,(Vertex_p)temp_v->cargo,print);
  }
  return distance;
}

/*
 * Function for deallocate the Dijkstra's struct parameters
 */
void graph_dealloc_dijkstra_param(Graph_p graph){
  hash_table_iterator(graph->hash_table_vertex,NULL,dealloc_param_dijkstra);
}


/*
 * Unique function to print a specific minimum path.
 * graph: the graph
 * s_vertex: the source vertex
 * v_vertex: another vertex
 * print: function for print the minimum path or NULL
 * return: the minimum distance
 */
float graph_dijkstra_min_path(Graph_p graph,void* s_vertex,void* v_vertex,IteratorFunction print){
  float distance = -1;
  List temp_s = hash_table_find(graph->hash_table_vertex,s_vertex);
  List temp_v = hash_table_find(graph->hash_table_vertex,v_vertex);

  if (temp_s != NULL && temp_v != NULL) {
    graph_dijkstra_v(graph,(Vertex_p)temp_s->cargo);
    distance = graph_dijkstra_min_distance_v(graph,(Vertex_p)temp_s->cargo,(Vertex_p)temp_v->cargo,print);
  }
  hash_table_iterator(graph->hash_table_vertex,NULL,dealloc_param_dijkstra);
  return distance;
}
