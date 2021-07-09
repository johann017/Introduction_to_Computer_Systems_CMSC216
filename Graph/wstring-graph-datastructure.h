/*Johann Antisseril, johann, 116533928, 0207
 *
 *I pledge on my honor that I have not given or received any unauthorized
 *assistance on this assignment.
 *
 *The purpose of this program file header is to have all the datastructures
 *that are used in this project to be here and defined. The graph that is 
 *implemented is a directed, weighted graph. It consists of a field that is a 
 *list. A list is a structure that contains a head pointer to node and a field
 *that counts the number of elements in the list. A node is a structure that 
 *has a field that is a void pointer to the data and another field that is a
 *pointer to the next node. A vertex is a structure that contains a field
 *that is a character pointer for the name of the vertex and another field 
 *which was a a list of edges to the vertex. An edge is a structure that has
 *a field which is a vertex pointer and another field that holds the cost.
 */ 


/*Makes sure it's only defined once.*/
#if !defined(WSTRING_GRAPH_DATASTRUCTURE_H)
#define WSTRING_GRAPH_DATASTRUCTURE_H

/*structures for "wstring-graph-datastructure.h"*/

/*This structure defines what a node is.*/
typedef struct node {
  
  /*This is a void pointer to allow for more flexibilty between different
   *types such as Vertex and Edges.*/
  void *data;
  struct node *next;
  
} Node;

/*This structure defines what a list is.*/
typedef struct list {
  struct node *head;

  /*This is the number of elements in the list.*/
  int num_vertices;
} List;

/*This structure defines what an edge is.*/
typedef struct edge {
  struct vertex *vertex;
  int cost;
} Edge;


/*This structure defines what a vertex is.*/
typedef struct vertex {
  char *name;
  
  /*This is a list of the outgoing edges.*/
  struct list *edges;
} Vertex;


/*This structure defines what a graph is.*/
typedef struct graph {
  struct list *vertices;
} WString_graph;

#endif





