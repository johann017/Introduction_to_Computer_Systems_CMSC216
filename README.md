# CMSC216_Projects

## Setup
To run `Forkfile` using sample tests:
- 

To run `Graph` using sample tests:
- 

To run `Threads` using sample tests:
- `make all`

To run `Two_Sided_Queue` using sample tests:
- `make all`

## Description
### Forkfile
- The objective of this project is to work with files and input/output functions. In addition to that, working with process control, specifically using fork to create a parent and child processes that can execute a command and check how the child process exited after executing the command. This project uses concepts of pointers and structures to make datastructures which makes the code work the way it should. This project will work with reading in a file and extracting and organizing information into these datastructures and accessed through various functions.

### Graph
- The objective of this project was to solidify understanding of pointers, structs, and linked list. This project creates a graph with vertices and connects vertices with edges that have costs or weights. It also removes edges and vertices from the graph and appropriately deallocating the memory space it previously held. In this project, a graph can be created, modified to add or removes vertices and edges, and get and identify how many neighbors a given vertex has.

### Threads
- This project has two files, one of which is normal C code without threads and the other has C code with threads. They both achieve the same thing but the file without threads was used as a reference to make the other file with threads. These two programs open input files and go line by line summing up all the values in the files and output the total.

### Two_Sided_Queue
- The objective of this project is to understand how to work with linked list in C. This project also uses memory allocation and deallocation to add and remove elements in a list. It is able to add to the front and back of the queue and remove in a similar fashion.
