/*Johann Antisseril, johann, 116533928, 0207
 *
 *I pledge on my honor that I have not given or recieved any unauthorized
 *assistance on this assignment.
 *
 *The objective of this project was to solidify understanding of pointers,
 *structs, and linked list. This project creates a graph with vertices and 
 *connects vertices with edges that have costs or weights. This implementation
 *of a graph makes a directed, weighted graph using structs. The graph is made
 *up of list of vertices. Each vertex has a name and a list of edges which it 
 *has outgoing edges to. Each edge has a pointer to the vertex it is connecting
 *to and has a cost or a weight. To increase flexibility, a node is created
 *with a field void data to make it either an edge node or a vertex node. 
 *
 *The new part of this project was removing edges and vertics from the graph and
 *appropriately deallocating the memory space it previously held. In this 
 *project, a graph can be created, modified to add or removes vertices and
 *edges, and get and identify how many neighbors a given vertex has. 
 */


/*All necessary include statements put here.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wstring-graph.h"
#include "wstring-graph-datastructure.h"

/*Helper function prototypes*/
static int add_edge_helper(List *list, const char *source,
			   const char *dest, int cost);
static int add_vertex_helper(List *list, const char *name, int check);
static int help_free_edge(Vertex *source, const char *dest);
static void help_free_vertex(Vertex *vertex);




/*This function takes care of the actual adding of an edge to the list of edges
 *and checks to see if the edge is already in the list.*/
static int add_edge_helper(List *list, const char *source,
			   const char *dest, int cost) {
  /*Declarations and initializations of all pointers to be used.*/
  Node *curr = NULL, *prev = NULL, *new_node = NULL;
  Edge *new_edge = NULL;
  Vertex *src_vertex = NULL, *dst_vertex = NULL;

  /*Checks is the list pointer points to NULL*/
  if (list != NULL) {

    /*Sets curr pointer to reference the head node in list.*/
    curr = list->head;

    /*Goes through all the elements in the list to find the source and 
     *destination vertices.*/
    while (curr != NULL) {

      /*Checks if the current node is the desired vertex nodes. Adds cast 
       *of (Vertex *) to tell program that the data of the node needs to be 
       *a Vertex pointer.*/
      if (strcmp(((Vertex *)(curr->data))->name, source) == 0)
	src_vertex = ((Vertex *)(curr->data));
      if (strcmp(((Vertex *)(curr->data))->name, dest) == 0)
	dst_vertex = ((Vertex *)(curr->data));
      prev = curr;
      curr = curr->next;
    }

    /*Reassigns prev and curr to NULL and the head of the list of edges for the
     *source vertex, respectively.*/
    prev = NULL;
    curr = src_vertex->edges->head;

    /*Goes through all the nodes to see if the edge exists.*/
    while (curr != NULL &&
	   strcmp(((Edge *)(curr->data))->vertex->name, dest) < 0) {
      prev = curr;
      curr = curr->next;
    }

    /*Checks if the edge actually exists then changes just the cost field.*/
    if (curr != NULL && strcmp(((Edge *)(curr->data))->vertex->name, dest) == 0)
      ((Edge *)(curr->data))->cost = cost;
    
    else{

      /*Creates a new node and new edge pointer and allocates them in memory
       *appropriately.*/
      new_node = malloc(sizeof(Node));
      new_edge = malloc(sizeof(Edge));

      /*Checks if the memory allocation was successful.*/
      if (new_node != NULL && new_edge != NULL) {

	/*Initializes the newly allocated pointers appropriately.*/
	new_edge->vertex = dst_vertex;
	new_edge->cost = cost;
	new_node->data = new_edge;
	new_node->next = curr;

	/*Checks if it is the first edge in the list.*/
	if (prev != NULL)
	  prev->next = new_node;
	else
	  src_vertex->edges->head = new_node;

	/*Increments the number of elements in the list.*/
	src_vertex->edges->num_vertices++;
      }
      /*Returns 0 if memory allocation failed.*/
      else
	return 0;
    }
    return 1;
  }
  /*Returns 0 if something didn't go right*/
  return 0;
}

/*This function takes care of the actual adding of a vertex to the list of 
 *vertices and checks to see if the vertex is already in the list.*/
static int add_vertex_helper(List *list, const char *name, int check) {

  /*Declares and initializes all the pointers to be used in the function.*/
  List *edge_list = NULL;
  Node *curr = NULL, *prev = NULL, *new_node = NULL;
  Vertex *new_vertex = NULL;
  char *new_name = NULL;

  /*Checks if list is NULL.*/
  if (list != NULL) {

    /*Sets curr's reference to the head pointer of the list.*/
    curr = list->head;

    /*Goes through all the elements in the list to see where to insert the 
     *vertex in lexicographic order.*/
    while (curr != NULL && curr->data != NULL &&
	   strcmp(((Vertex *)(curr->data))->name, name) < 0) {
      prev = curr;
      curr = curr->next;
    }

    /*Checks if curr is already in the list.*/
    if (curr != NULL && strcmp(((Vertex *)(curr->data))->name, name) == 0)
      return 0;

    /*If the function isn't checking if the vertex in the list or not, it enters
     *here.*/
    if (!check) {

      /*Allocates space in memory for all the pointers to set them in memory.*/
      edge_list = malloc(sizeof(List));
      new_name = malloc(sizeof(char) * (strlen(name) + 1));
      new_vertex = malloc(sizeof(Vertex));
      new_node = malloc(sizeof(Node));

      /*Checks if the allocation was successful.*/
      if (new_name != NULL && new_vertex != NULL && new_node != NULL
	  && edge_list != NULL) {

	/*Copies name into the pointer*/
	strcpy(new_name, name);

	/*Assigns the name field and initializes the list of edges field.*/
	new_vertex->name = new_name;
	edge_list->head = NULL;
	edge_list->num_vertices = 0;
	new_vertex->edges = edge_list;

	/*Puts the Vertex into a node pointer to be put into the list.*/
	new_node->data = new_vertex;
	new_node->next = curr;

	/*Checks if it is the first vertex in the list.*/
	if (prev != NULL)
	  prev->next = new_node;
	else
	  list->head = new_node;

	/*Increments number of vertices in the list.*/
	list->num_vertices++;
      }

      /*Returns 0 if memory allocation failed.*/
      else
	return 0;
    }

    /*Returns 1 if everything went as expected.*/
    return 1;
  }
  /*Returns 0 if something went wrong.*/
  return 0;
}



/*This function initializes the graph.*/
void init_graph(WString_graph *const graph) {
  /*Declares a list pointer and allocates it space in memory.*/
  List *list = malloc(sizeof(List));

  /*Check if memory allocation worked and if graph is NULL.*/
  if (graph != NULL && list != NULL) {

    /*Sets the list pointer first then makes graph->vertices point to it.*/
    list->head = NULL;
    list->num_vertices = 0;
    graph->vertices = list;
  }

  /*If memory allocation failed, it prints a message and then exits.*/
  if (list == NULL) {
    printf("Memory allocation failed.\n");
    exit(0);
  }
}

/*This function adds a new vertex to the graph with the given name.*/
int new_vertex_add(WString_graph *const graph, const char new_vertex[]) {

  /*Checks if the parameters are NULL.*/
  if (graph != NULL && new_vertex != NULL)

    /*Calls the helper function to add the vertex in and returns.*/
    return add_vertex_helper(graph->vertices, new_vertex, 0);

  /*Returns 0 if the parameters are NULL.*/
  return 0;
}

/*Gets the number of vertieces in the graph.*/
int num_vertices(const WString_graph *const graph) {

  /*Checks if the parameter and the list of vertices are NULL.*/
  if (graph != NULL && graph->vertices != NULL)

    /*Accesses the num_vertices field in the list and returns the value.*/
    return graph->vertices->num_vertices;

  /*Returns 0 if anything was NULL.*/
  return 0;
}


/*This function checks if the vertex with the given name exists in the graph.*/
int is_existing_vertex(const WString_graph *const graph, const char name[]) {

  /*Checks if the parameters and the list of vertices are NULL.*/
  if (graph != NULL && graph->vertices != NULL && name!= NULL)

    /*Uses the add_vertex_helper function just to use its iterations to see if
     *the vertex exists.*/
    return !add_vertex_helper(graph->vertices, name, 1);

  /*Returns 0 if anything was NULL.*/
  return 0;
}

/*This function creates an array that has been allocated in memory of pointers
 *to character.*/
char **get_vertices(const WString_graph *const graph) {

  /*Declares and initializes the variables. Use a double pointer to represent
   *the array of pointers.*/
  int i = 0, size = num_vertices(graph);
  char **arr = NULL, *name = NULL;
  Node *curr = NULL;

  /*Checks if the parameter and the list of vertices are NULL.*/
  if (graph != NULL && graph->vertices != NULL) {

    /*Sets the curr node to the first element in the list of vertices.*/
    curr = graph->vertices->head;

    /*Allocates space in memory for the pointer.*/
    arr = malloc((size + 1) * sizeof(char*));

    /*Checks if memory allocation was successful.*/
    if (arr != NULL) {

      /*Goes through all the vertices in the list.*/
      for (i = 0; i < size; i++) {

	 /*Allocates space in memory for the pointer.*/
	name = malloc(sizeof(char) *
		      (strlen(((Vertex *)(curr->data))->name) + 1));
	
	/*Checks if memory allocation was successful.*/
	if (name != NULL) {

	  /*Copies the name of the vertex to the pointer name and leaves space
	   *for' \0' at the end.*/
	  strcpy(name, ((Vertex *)(curr->data))->name);

	  /*Sets the element of the array to refer to the name pointer.*/
	  arr[i] = name;
	  curr = curr->next;
	}

	/*If memory allocation fail, return NULL.*/
	else
	  return NULL;
      }

      /*Sets the last element of the array to NULL.*/
      arr[size] = NULL;
    }
  }

  /*Returns NULL.*/
  return arr;
}


/*This function adds the edge to the list of edges if it doesn't already exist 
 *or changes the cost if it already exists.*/
int add_edge(WString_graph *const graph, const char source[], const char dest[],
	     int cost) {

  /*Checks if cost is 0 or more.*/
  if (cost < 0)
    return 0;

  /*Checks if parameters are NULL and if the list of vertices are NULL*/
  if (graph != NULL && graph->vertices != NULL && source != NULL
      && dest != NULL) {

    /*Checks if the source and destination names exist, if not it creates 
     *vertices with those name.*/
    if (!is_existing_vertex(graph, source))
      new_vertex_add(graph, source);
    if (!is_existing_vertex(graph, dest))
      new_vertex_add(graph, dest);

    /*Calls the add_edge_helper function and returns.*/
    return add_edge_helper(graph->vertices, source, dest, cost);
  }

  /*Returns 0 if anything was NULL*/
  return 0;
}

/*This function gets the weight of the edge given the source and destination
 *names.*/
int get_weight_of_edge(const WString_graph *const graph, const char source[],
		       const char dest[]) {

  /*Declares and initializes the pointers to be used in this function.*/
  Node *curr = NULL, *node = NULL;

  /*Checks if the source or destination pointers were NULL.*/
  if (source == NULL || dest == NULL)
    return -1;

  /*Checks if the graph and its list were NULL.*/
  if (graph != NULL && graph->vertices != NULL) {

    /*Checks if the vertices exist in the graph.*/
    if (!is_existing_vertex(graph, source) || !is_existing_vertex(graph, dest))
      return -1;
    
    /*Sets curr's reference to the first vertex in the list of vertices.*/
    curr = graph->vertices->head;

    /*Goes through all the elements until it finds the vertex with the source
     *parameter's name.*/
    while (curr != NULL && strcmp(((Vertex *)(curr->data))->name, source) != 0)
      curr = curr->next;

    /*Sets node's reference to the head of curr's edge list.*/
    node = ((Vertex *)(curr->data))->edges->head;

    /*Goes through all the elements until it finds the edge that has a vertex 
     *pointed with the name equal to the destination's pointer.*/
    while (node != NULL &&
	   strcmp(((Edge *)(node->data))->vertex->name, dest) != 0)
      node = node->next;

    /*Checks if there was an edge with a vertex pointer with the field of
     *the destination parameter.*/
    if (node == NULL)
      return -1;

    /*Access the cost field in the edge struct and returns it.*/
    return ((Edge *)(node->data))->cost;
  }

  /*Returns 0 if the graph or the list of vertices in graph were NULL.*/
  return 0;
}


/*This function return the number of neighbors a given vertex has.*/
int num_neighbors(const WString_graph *const graph, const char vertex[]) {
  
  /*Declares and initializes the pointers to be used in this function.*/
  Node *curr = NULL;

  /*Checks if the string parameter was NULL.*/
  if (vertex == NULL)
    return -1;

   /*Checks if the graph and its list were NULL.*/
  if (graph != NULL && graph->vertices != NULL) {

    /*Checks if the vertex exists in the graph.*/
    if (!is_existing_vertex(graph, vertex))
      return -1;

    /*Sets curr's reference to the first node in the list of vertices.*/
    curr = graph->vertices->head;

    /*Iterates until it finds the vertex with the same name as the vertex
     *parameter.*/ 
    while (strcmp(((Vertex *)(curr->data))->name, vertex) != 0)
      curr = curr->next;

    /*Accesses the field of the number of elements in the list of edges for the
     *current vertex.*/ 
    return ((Vertex *)(curr->data))->edges->num_vertices;
  }

  /*Returns 0 if the graph or the list of vertices in graph were NULL.*/
    return 0;
}


/*This function serves as a helper to handle freeing the specific edge.*/
static int help_free_edge(Vertex *source, const char *dest) {
  /*Declarations and instantiations of the pointers to be used.*/
  Node *curr = NULL, *prev = NULL;
  if (source != NULL && dest != NULL) {

    /*Assigns curr to point to the first edge in the edge list and 
     *iterates through until it finds the correct one.*/
    curr = source->edges->head;
    while (curr != NULL &&
	   strcmp(((Edge *)(curr->data))->vertex->name, dest) != 0) {
      prev = curr;
      curr = curr->next;
    }

    /*Checks if the edge was in the edge list.*/
    if (curr != NULL) {

      /*Reassigns the header if it was the first element in the list.*/
      if (prev == NULL)
	source->edges->head = curr->next;
      else 
	prev->next = curr->next;

      /*Takes care of freeing the edge and the node while decrementing the 
       *number of edges there are in the edges list.*/
      free((Edge *)(curr->data));
      curr->data = NULL;
      free(curr);
      curr = NULL;
      source->edges->num_vertices--;

      /*Returns 1 if the whole process was a success.*/
      return 1;
    }
  }
  /*Returns 0 if the process failed.*/
  return 0;
}
  

/*This function serves as a helper to freeing a vertex.*/
static void help_free_vertex(Vertex *vertex) {

  /*Declarations and instantiations of the pointers to be used.*/
  Node *curr = NULL, *prev = NULL;

  /*Checks if the parameter was legal.*/
  if (vertex != NULL) {

    /*Assigns curr to point to the first edge in the edge list and 
     *iterates through all of them, freeing each edge and edge node in the
     *list.*/
    curr = vertex->edges->head;
    while(curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev->data);
      prev->data = NULL;
      free(prev);
      prev = NULL;
    }

    /*Frees the list, name, and the vertex itself and setting them to NULL 
     *after.*/
    free(vertex->edges);
    vertex->edges = NULL;
    free(vertex->name);
    vertex->name = NULL;
    free(vertex);
    vertex = NULL;
  }
}


/*This function goes through the list of vertex names and frees each element.*/
void free_vertex_list(char **const names) {
  int i = 0;

  /*Checks if the parameter is valid.*/
  if (names != NULL) {

    /*Goes through all the elements in the names array and frees each name.*/
    while (names[i] != NULL) {
      free(names[i]);
      names[i] = NULL;
      i++;
    }

    /*Frees the array that was holding the names.*/
    free(names);
  }
}


/*This function dismantles the entire graph and frees each part of it.*/
void destroy_graph(WString_graph *const graph) {

  /*Declarations and instantiations of the pointers to be used.*/
  Node *curr = NULL, *prev;

  /*Checks if the parameter is valid and if the vertex list is NULL.*/
  if (graph != NULL && graph->vertices != NULL) {

    /*Assigns curr to point to the first vertex in the vetex list and 
     *iterates through, freeing each one and its fields.*/
    curr = graph->vertices->head;
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      help_free_vertex((Vertex *)(prev->data));
      free(prev);
      prev = NULL;
    }

    /*Frees the vertex list and sets it to refer to NULL.*/
    free(graph->vertices);
    graph->vertices = NULL;
  }
}


/*This function removes the specified edge by checking some conditions and
 *calling the helper function.*/
int remove_edge(WString_graph *const graph, const char source[],
		const char dest[]) {

  /*Declarations and instantiations of pointers to be used.*/
  Node *curr = NULL;
  Vertex *src_vertex = NULL;

  /*Checks if the parameter is valid and if the vertex list is NULL and if the
   *two parameter names of vertices are valid vertices that exist in the 
   *graph.*/
  if (graph != NULL && graph->vertices != NULL &&
      is_existing_vertex(graph, source) && is_existing_vertex(graph, dest)) {


    /*Assigns curr to point to the first vertex in the vertex list and 
     *iterates through until it finds the correct one.*/
    curr = graph->vertices->head;
    while (curr != NULL && strcmp(((Vertex *)(curr->data))->name, source) < 0)
      curr = curr->next;

    /*Pointer to the current vertex to make calling the helper function 
     *easier.*/
    src_vertex = ((Vertex *)(curr->data));

    /*Checks if the source vertex was in the vertex list to double check and
     *calls the helper function.*/
    if (src_vertex != NULL)
      return help_free_edge(src_vertex, dest); 
  }

  /*Returns 0 if the process failed.*/
  return 0;
}
    

/*This function removes the specified vertex and free its allocated memory
 *and of all its field's memory too.*/
int remove_vertex(WString_graph *const graph, const char vertex[]) {

  /*Declaration and instantiation of the pointers to be used.*/
  Node *curr = NULL, *prev = NULL, *target = NULL, *prev_target = NULL;

  /*Checks if the parameter was valid and if the vertices list is NULL and if
   *the vertex with parameter name vertex exists in the graph.*/
  if (graph != NULL && graph->vertices != NULL &&
      is_existing_vertex(graph, vertex)) {

    /*Assigns curr to point to the first vertex in the vertex list and 
     *iterates through, freeing any incoming edges to the vertex with name
     *that of the parameter source. If the current vertex is the source 
     *vertex, it will store the current vertex and the previous one.*/
    curr = graph->vertices->head;
    while (curr != NULL) {
      if (strcmp(((Vertex *)(curr->data))->name, vertex) == 0) {
	prev_target = prev;
	target = curr;
      }
      else
	help_free_edge((Vertex *)(curr->data), vertex);
      prev = curr;
      curr = curr->next;
    }

    /*Checks if the vertex was in the list as a double check.*/
    if (target != NULL) {

      /*Checks if this is the first vertex in the list and reassigns head if it
       *is.*/
      if (prev_target == NULL)
	graph->vertices->head = target->next;

      /*Else it'll set the previous node's next to the next node after the 
       *target one.*/
      else
	prev_target->next = target->next;

      /*Calls the helper function to free the vertex, thrn free the node and 
       *decrements the number of vertices in the list.*/
      help_free_vertex((Vertex *)(target->data));
      free(target);
      target = NULL;
      graph->vertices->num_vertices--;

      /*Returns 1 if the process was successful.*/
      return 1;
    }
  }

  /*Returns 0 if the process failed.*/
  return 0;
}


/*This function returns an array to names of the neighbors to a given vertex.*/
char **get_neighbors(const WString_graph *const graph, const char vertex[]) {

  /*Declarations and intializations of variables to be used.*/
  int i = 0, size = 0;
  char **arr = NULL, *name = NULL;
  Node *curr = NULL;

  /*Checks if the parameter and the list of vertices are NULL and if the vertex
   *exists in the graph.*/
  if (graph != NULL && graph->vertices != NULL &&
      is_existing_vertex(graph, vertex)) {

    /*Sets the curr node to the first element in the list of vertices.*/
    curr = graph->vertices->head;

    /*Iterates through until it finds the vertex.*/
    while (curr != NULL &&
	   strcmp(((Vertex *)(curr->data))->name, vertex) < 0)
      curr = curr->next;

    /*Gets the number of edges to the vertex and sets curr to the first edge in
     *the edge list.*/
    size = ((Vertex *)(curr->data))->edges->num_vertices;
    curr = ((Vertex *)(curr->data))->edges->head;
    
    /*Allocates space in memory for the pointer.*/
    arr = malloc((size + 1) * sizeof(char*));

    /*Checks if memory allocation was successful.*/
    if (arr != NULL) {

      /*Goes through all the edges in the list.*/
      for (i = 0; i < size; i++) {

	 /*Allocates space in memory for the pointer.*/
	name = malloc(sizeof(char) *
		      (strlen(((Edge *)(curr->data))->vertex->name) + 1));
	
	/*Checks if memory allocation was successful.*/
	if (name != NULL) {

	  /*Copies the name of the vertex to the pointer name.*/
	  strcpy(name, ((Edge *)(curr->data))->vertex->name);

	  /*Sets the element of the array to refer to the name pointer.*/
	  arr[i] = name;
	  curr = curr->next;
	}

	/*If memory allocation fail, return NULL.*/
	else
	  return NULL;
      }

      /*Sets the last element of the array to NULL.*/
      arr[size] = NULL;
    }
  }

  /*Returns NULL.*/
  return arr;
}
