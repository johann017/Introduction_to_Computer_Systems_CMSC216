/*Johann Antisseril, johann, 116533928, 0207
 *
 *I pledge on my honor that I have not given or received any unauthorized 
 *assistance on this assignment.
 *
 *The purpose of this file in this project is to define the datastructure to be
 *used in this project. This file uses the conditional compilation directives
 *to ensure this file isn't defined multiple times. This file uses 5 structs
 *which all hold data in an organized way which makes it easier to manipulate
 *in the forkfile.c file. The forkfile struct stores the entire forkfile by
 *having a list of targets in it. The list(as well as all lists) have a counter
 *which keeps track of how many elements are in the list and a head node pointer
 *which points to the first node in the list. Each node has a void pointer
 *named data that can hold the data in the list and a next node pointer to
 *point to the next Node in a List. There is a Target struct which holds a 
 *char pointer(string) which holds its name as well as 2 List pointers which
 *hold the target's dependencies and its action line. Since both action word and
 *dependencies both just need to hold words or names, the struct Element was
 *created to generalize the name so both could use this structure. In it, it
 *only contains a char pointer(string) that holds the word.
 */

/*This makes sure this file is only defined once.*/
#if !defined(FORKFILE_DATASTRUCTURE_H)
#define FORKFILE_DATASTRUCTURE_H

/*This struct defines what a node has.*/
typedef struct node {

  /*Each node has a data field which can hold a Target or an element. A void
   *pointer was chosen for flexibility.*/
  void *data;

  /*A node pointer to the next node.*/
  struct node *next;
} Node;


/*This struct defines what a List is.*/
typedef struct list {

  /*Each List has a node pointer to the head of the list to point to the first 
   *element.*/
  Node *head;

  /*It has a counter to keep count of how many elements it contains.*/
  int counter;
} List;


/*This defines what an element struct is.*/
typedef struct element {

  /*Each element struct has just a name.*/
  char *name;
} Element;


/*This defines what a target struct is.*/
typedef struct target {

  /*Each Taregt has a string for its name.*/
  char *name;

  /*It has a list to hold each dependency.*/
  List *dependencies;

  /*It has a separate list to how each action line word which is separated in 
   *the action line by whitespace.*/
  List *action;
} Target;


/*This defines what a forkfile struct is.*/
typedef struct forkfile {

  /*It contains a list of targets which indicate each rule.*/
  List *targets;
} Forkfile;

#endif
