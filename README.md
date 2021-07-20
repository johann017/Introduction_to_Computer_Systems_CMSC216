# CMSC216_Projects

## Description
### `Forkfile`
- The objective of this project is to work with files and input/output functions. In addition, process control and forks were used to create a parent and child processes that can execute a command and also check how the child process exited after executing the command. Pointers and structures were used to make datastructures. This project reads a file, extracts and organizes information into these datastructures which are accessed through various functions.

### `Graph`
- The objective of this project was to solidify understanding of pointers, structs, linked list and memory allocation. It creates a graph with vertices and connects vertices with edges that have costs or weights. It removes edges and vertices from the graph and appropriately deallocates the memory space it previously held. In this project, a graph can be created, modified to add or remove vertices and edges, and identifies how many neighbors a given vertex has.

### `Threads`
- This project has two files, one of which is normal C code without threads and the other has C code with threads. They both achieve the same thing but the file without threads was used as a reference to make the other file with threads. These two programs open input files and go line by line summing up all the values in the files and outputs the total.

### `Two_Sided_Queue`
- The objective of this project is to understand how to work with linked lists in C. It uses memory allocation and deallocation to add and remove elements in a list. It is able to add to the front and back of the queue and remove in a similar fashion.


## Setup
- Install [GitHub CLI](https://cli.github.com/) and connect to GitHub account
- Open Git CMD
- Run `gh repo clone johann017/Introduction_to_Computer_Systems_CMSC216` in the command line

To run `Forkfile` using sample tests:
- Move the current directory into the Forkfile folder
- Run `make all`

To run `Graph` using sample tests:
- Move the current directory into the Graph folder
- Run `make all`

To run `Threads` using sample tests:
- Move the current directory into the Threads folder
- Run `make all`

To run `Two_Sided_Queue` using sample tests:
- Move the current directory into the Two_Sided_Queue folder
- Run `make all`
