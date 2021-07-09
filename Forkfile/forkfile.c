/*Johann Antisseril, johann, 116533928, 0207
 *
 *I pledge on my honor that I have not given or received any unauthorized
 *assistance on this assignment.
 *
 *The objective of this project is to work with files and input/output 
 *functions. In addition to that, working with process control, specifically
 *using fork to create a parent and child processes that can execute a command 
 *and check how the child process exited after executing the command. This 
 *project uses concepts of pointers and structures to make datastructures which
 *makes the code work the way it should. This project will work with reading in 
 *a file and extracting and organizing information into these datastructures
 *and accessed through various functions. The whole datastructure that contains
 *the other structures is called a forkfile which is a file that consists of
 *rules. Each rule has a target, its dependencies and an action line right below
 *it which compiles the file. A structure implemented in this file is the 
 *Target struct where each target has a name, a list of actions which forms the
 *action line and a list of dependencies. Each dependency and action word has
 *a "name" which just signifies that it's a word and both of these share a 
 *struct called Element to generalize that both can use this struct. Since there
 *may be multiple targets and/or dependencies and action words in the action
 *line, each one of these utilize the List struct which contain a counter for 
 *how many elements are in the list and a head Node which points to the first
 *element in the List. A Node is another structure which contains a data field
 *which can hold any struct and a next field which links it to the next Node. 
 *Finally there is a struct called Forkfile which contains a List field which is
 *meant to hold all the targets. With this organization all the data can be 
 *stored properly. In this project, there is use of dynamically allocating 
 *memory for these structs as well as strings(char pointers) so that they can 
 *hold their information in memory to be used later on in the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "forkfile.h"
#include "forkfile-datastructure.h"
#include "split.h"
#include "safe-fork.h"
#include "make-target.h"


/*Global variable errno to be used for error number.*/
extern int errno;

/*Helper Prototypes*/
static int valid_rule_num(List *list, int rule_num);
static void print_dependencies(Node *curr_tar);
static Node *get_rule(Forkfile forkfile, int rule_num);


/*This is a helper function that determines if a rule number is valid or not.*/
static int valid_rule_num(List *list, int rule_num) {

  /*Checks if the rule number is greater than or equal to 0 and less than or
   *equal to the amount of targets.*/
  if (rule_num < 0 || (list->counter < rule_num))
    return 0;
  return 1;
}


/*This helper function prints the dependencies for a given target.*/
static void print_dependencies(Node *curr_tar) {

  /*Pointers to be used.*/
  Node *curr_dep = ((Target *)(curr_tar->data))->dependencies->head;

  /*Iterates through all the dependencies one by one.*/
  while (curr_dep != NULL) {

    /*Prints the dependencies with a space in front of each one.*/
    printf(" %s", ((Element *)(curr_dep->data))->name);
    curr_dep = curr_dep->next;
  }

  /*Adds a newline afterwards.*/
  printf("\n");
}


/*This helper function gets the rule with the number rule_num from the
 *forkfile.*/
static Node *get_rule(Forkfile forkfile, int rule_num) {

  /*Variables to be used.*/
  int i = 0;
  Node *curr = NULL;

  /*Checks if the parameters are valid.*/
  if (forkfile.targets != NULL && valid_rule_num(forkfile.targets, rule_num)) {

    /*Sets curr to the first target and iterates until it gets to the correct 
     *target.*/
    curr = forkfile.targets->head;
    for (i = 0; i < rule_num; i++)
      curr = curr->next;

    /*Returns the current target.*/
    return curr;
  }

  /*Returns NULL if the parameters weren't valid.*/
  return NULL;
}
  
  



/*This function reads the file and returns a forkfile.*/
Forkfile read_forkfile(const char filename[]) {

  /*Variables to be used.*/
  Forkfile forkfile;
  List *tar_list = NULL, *act_list = NULL, *dep_list = NULL;
  Node *tar_node = NULL, *dep_node = NULL, *act_node = NULL, *prev_act = NULL;
  Node *prev_tar = NULL, *prev_dep = NULL;
  Target *target = NULL;
  Element *dependency = NULL, *act = NULL;
  FILE *file = NULL;
  char buff[1001], *tar_name = NULL, *dep_name = NULL, *act_name = NULL;
  char **string = NULL;
  int checker = 0;

  /*Checks if the file is valid.*/
  if (filename != NULL) {

    /*Allocates space in memory for the list of targets.*/
    tar_list = malloc(sizeof(List));

    /*Checks if malloc was successful.*/
    if (tar_list != NULL) {

      /*Sets the head of the list to NULL and the counter(num of targets) to 0*/
      tar_list->head = NULL;
      tar_list->counter = 0;

      /*Opens the file with name passed in the parameter and sets it to read.*/
      file = fopen(filename, "r");
      if (file != NULL) {

	/*Iterates and reads each line in the file until it reaches the end.*/
	while (fgets(buff, 1001, file) != NULL){

	  /*Sets the previous action and dependency elements to NULL for each 
	   *new target.*/
	  prev_act = NULL;
	  prev_dep = NULL;

	  /*Sets the last element which would be a newline character to a NUL 
	   *byte*/
	  buff[strlen(buff) - 1] = '\0';

	  /*Uses the split function to seperate by word.*/
	  string = split(buff);

	  /*Checks if the split worked with a valid string.*/
	  if (*string != NULL) {

	    /*Checks if this iteration is supposed to read dependencies.*/
	    if ((checker % 2) == 0) {

	      /*Allocates space in memory for the Node to hold the target, the
	       *target itself, the dependency list, the action list and the
	       *target's name.*/
	      tar_node = malloc(sizeof(Node));
	      target = malloc(sizeof(Target));
	      dep_list = malloc(sizeof(List));
	      act_list = malloc(sizeof(List));
	      tar_name = malloc(sizeof(char) * (strlen(*string) + 1));

	      /*Checks if the memory allocation was successful.*/
	      if (tar_name != NULL && tar_node != NULL && target != NULL &&
		  dep_list != NULL && act_list != NULL) {

		/*Sets the dependency list's counter to 0 and head to NULL.*/
		dep_list->head = NULL;
		dep_list->counter = 0;
		
		/*Copies the first word in the line read in.*/
		strncpy(tar_name, *string, strlen(*string) + 1);

		/*Sets the current target's name reference to point to the word
		 *that was just copied.*/
		target->name = tar_name;

		/*Goes to the next word.*/
		string++;

		/*Iterates until it reaches the end of the line.*/
		while (*string != NULL){

		  /*Allocates space in memory for the node that holds the 
		   *dependency, the dependency itself and the dependency name.*/
		  dep_node = malloc(sizeof(Node));
		  dependency = malloc(sizeof(Element));
		  dep_name = malloc(sizeof(char) * (strlen(*string) + 1));

		  /*Checks if the allocation was successful.*/
		  if (dep_node != NULL && dependency != NULL &&
		      dep_name != NULL) {

		    /*Copies the current word.*/
		    strncpy(dep_name, *string, strlen(*string) + 1);

		    /*Sets the dependency's name's reference to the copied 
		     *word. It stores the dependency in the node's data and 
		     *sets the next pointer to NULL*/
		    dependency->name = dep_name;
		    dep_node->data = dependency;
		    dep_node->next = NULL;

		    /*Checks if this is the first dependency in the list. If
		     *so, the head of the list will point to this node. If not,
		     *the previous's node's next pointer will point to this
		     *dependency's node.*/
		    if (prev_dep != NULL)
		      prev_dep->next = dep_node;
		    else
		      dep_list->head = dep_node;

		    /*Increments the counter.*/
		    dep_list->counter++;

		    /*Sets the previous node to the current one then iterates
		     *the current node to the next.*/
		    prev_dep = dep_node;
		    string++;
		  }
		}
	      }

	      /*Sets the targets dependency list to point to the dependency just
	       *made.*/
	      target->dependencies = dep_list;
	    }

	    /*Checks if this iteration checks the action line.*/
	    if (checker % 2) {
	      
	      /*Sets the dependency list's counter to 0 and head to NULL.*/
	      act_list->head = NULL;
	      act_list->counter = 0;
	      
	      /*Iterates through the line that was just read in.*/
	      while (*string != NULL){

		/*Allocates space in memory for the node that holds the each
		 *part of the action line, the actual part of the action line,
		 *and the name of each word.*/
		act_node = malloc(sizeof(Node));
		act = malloc(sizeof(Element));
		act_name = malloc(sizeof(char) * (strlen(*string) + 1));

		/*Checks if the mallocs were successful.*/
		if (act_node != NULL && act != NULL &&
		    act_name != NULL) {

		  /*Copies each word in the current line.*/
		  strncpy(act_name, *string, strlen(*string) + 1);

		  /*Sets the action line name to the copied word. Sets the
		   *node's data to refer to act and sets the next pointer to
		   *NULL.*/
		  act->name = act_name;
		  act_node->data = act;
		  act_node->next = NULL;

		  /*Checks if this is the first action in the list. If
		   *so, the head of the list will point to this node. If not,
		   *the previous's node's next pointer will point to this
		   *action's node.*/
		  if (prev_act != NULL)
		    prev_act->next = act_node;
		  else
		    act_list->head = act_node;

		  /*Increments the counter for the number of elements in the 
		   *list.*/
		  act_list->counter++;

		  /*Sets the previous node to the current one then iterates
		   *the current node to the next.*/
		  prev_act = act_node;
		  string++;
		}
		
		/*Sets target's action list field to point to the action list
		 *just created.*/
		target->action = act_list;
	      }

	      /*Sets the target node's data field to point to the current
	       *target and the next field to point to NULL.*/
	      tar_node->data = target;
	      tar_node->next = NULL;

	      /*Checks if this is the first target in the list. If
	       *so, the head of the list will point to this node. If not,
	       *the previous's node's next pointer will point to this
	       *target's node.*/
	      if (prev_tar != NULL)
		prev_tar->next = tar_node;
	      else
		tar_list->head = tar_node;

	      /*Sets the previous node to the current one.*/
	      prev_tar = tar_node;

	      /*Increments the counter for the number of elements in the 
	       *list.*/
	      tar_list->counter++;
	    }
	    /*Increment checker to alernate dependencies and action line.*/
	    checker++;
	  }
	  /*Clears the array holding the information.*/
	  memset(buff, '\0', sizeof(buff));
	}
	/*Closes the file.*/
	fclose(file);
	
	/*Sets the forkfile's target list pointer to refer to the list.*/
	forkfile.targets =  tar_list;
      }
    } 
  }

  /*If file is invalid, set forkfile to be empty.*/
  else
    forkfile.targets = NULL;
  return forkfile;
}

/*This function determines what number the given target is.*/
int lookup_target(Forkfile forkfile, const char target_name[]) {

  /*Variables to be used.*/
  int counter = 0;
  Node *curr = NULL;

  /*Checks if the parameters are valid.*/
  if (forkfile.targets != NULL && target_name != NULL) {

    /*Curr is set to the first target.*/
    curr = forkfile.targets->head;

    /*Iterates through targets until the one matching the parameter is found or
     *curr is NULL.*/
    while (curr != NULL &&
	   (strcmp(((Target *)(curr->data))->name, target_name) != 0)) {

      /*Increments counter and sets curr to the next target.*/
      counter++;
      curr = curr->next;
    }

    /*Makes sure if the target is found and returns the number associated with
     *it.*/
    if (curr != NULL &&
	 strcmp(((Target *)(curr->data))->name, target_name) == 0)
      return counter;
  }

  /*If the target isn't foudn return -1.*/
  return -1;
}


/*This function prints the action line of the given rule.*/
void print_action(Forkfile forkfile, int rule_num) {

  /*Variables to be used.*/
  Node *curr_tar = NULL, *curr_act = NULL;

  /*Checks if the parameters are valid.*/
  if (forkfile.targets != NULL && valid_rule_num(forkfile.targets, rule_num)) {

    /*Uses the helper function to get the correct target.*/
    curr_tar = get_rule(forkfile, rule_num);

    /*Checks if the target is valid to be used.*/
    if (curr_tar != NULL) {

      /*Sets curr_act to the first word in the action line.*/
      curr_act = ((Target *)(curr_tar->data))->action->head;

      /*Iterates through all the elementd in the action line.*/
      while (curr_act->next != NULL) {

	/*Prints the word with a space after each word and sets curr_act to the
	 *next word.*/
	printf("%s ", ((Element *)(curr_act->data))->name);
	curr_act = curr_act->next;
      }

      /*Checks if all elements except the last one has been read and that this 
       *line isn't an empty line and prints the last word with a newline after*/
      if (curr_act != NULL)
	printf("%s\n", ((Element *)(curr_act->data))->name);
    }
  }
}


/*This function prints the entire forkfile.*/
void print_forkfile(Forkfile forkfile) {

  /*Variables to be use in the function.*/
  int i = 0;
  Node *curr_tar = NULL;

  /*Checks if the parameter is valid.*/
  if (forkfile.targets != NULL) {

    /*Sets curr_tar to the first target.*/
    curr_tar = forkfile.targets->head;

    /*Iterates through all targets.*/
    while (curr_tar != NULL) {

      /*Prints the target with a colon right after.*/
      printf("%s:", ((Target *)(curr_tar->data))->name);

      /*Calls the helper function to print the dependencies.*/
      print_dependencies(curr_tar);

      /*Prints a tab and then calls the print_action function to print the 
       *action line.*/
      printf("\t");
      print_action(forkfile, i);

      /*Increments i and sets curr_tar to the next target's node.*/
      i++;
      curr_tar = curr_tar->next;

      /*If the curr target's node isn't NULL, prints a newline after it.*/ 
      if (curr_tar != NULL)
	printf("\n");
    }
  }
}



/*This function returns the number of dependencies in the given rule.*/
int num_dependencies(Forkfile forkfile, int rule_num) {

  /*Variables to be used.*/
  Node *curr = NULL;

  /*Checks if the parameters are valid and if not returns -1.*/
  if (forkfile.targets == NULL || !valid_rule_num(forkfile.targets, rule_num))
    return -1;

  /*Gets the target associated with the parameter rule_num by calling the 
   *helper function and sets curr to point to it.*/
  curr = get_rule(forkfile, rule_num);

  /*Returns the counter of the current target's dependency list.*/
  return ((Target *)(curr->data))->dependencies->counter;
}



/*This function returns the dependency give the target number and the 
 *dependency number.*/
char *get_dependency(Forkfile forkfile, int rule_num, int dependency_num) {

  /*Variables to be used.*/
  int i = 0;
  Node *curr_tar = NULL, *curr_dep = NULL;

  /*Checks if the forkfile is valid.*/
  if (forkfile.targets) {

    /*Sets the current target's node to refer to the one returned by the helper 
     *function.*/
    curr_tar = get_rule(forkfile, rule_num);

    /*Checks if the node is a valid one to be used,*/
    if (curr_tar != NULL) {

      /*Sets the current dependency's node to the first dependency in the list*/
      curr_dep = ((Target *)(curr_tar->data))->dependencies->head;

      /*Checks if the parameter dependency_num is valid.*/
      if (valid_rule_num(((Target *)(curr_tar->data))->dependencies,
			 dependency_num)) {

	/*Iterates until it reaches the corect dependency  and returns its 
	 *name.*/
	for(i = 0; i < dependency_num; i++)
	  curr_dep = curr_dep->next;
	return ((Element *)(curr_dep->data))->name;
      }
    }
  }

  /*Returns NULL if anything was invalid.*/
  return NULL;
}


/*This function checks if the file exists in the system at all.*/
int exists(const char filename[]) {

  /*Structure to be used.*/
  struct stat *buff;

  /*Allocates space in memeory for it.*/
  buff = malloc(sizeof(*buff));

  /*Checks if the parameter is valid and if the mempry allocation was 
   *successful.*/
  if (filename != NULL &&  buff != NULL) {

    /*Checks if stat return -1 and errno is ENOENT to show that the file does
     *not exist in the system and returns 0 if it doesn't and 1 if it does.*/
    if (stat(filename, buff) == -1 && errno == ENOENT)
      return 0;
    else
      return 1;
  }

  /*Returns 0 if the parameter wasn't valid or malloc wasn't successful.*/
  return 0;
}


/*This functions checks whether file 1 is older than file 2.*/
int is_older(const char filename1[], const char filename2[]) {

  /*Two structure to be used.*/
  struct stat *first = NULL, *second = NULL;

  /*Allocate space in memory for both structures.*/
  first = malloc(sizeof(*first));
  second = malloc(sizeof(*second));

  /*Checks if both memory allocations were successful and if both parameter's
   *exist in the system.*/
  if (first != NULL && second != NULL && exists(filename1) &&
      exists(filename2)) {

    /*Calls stat on both paremeters.*/
    stat(filename2, second);
    stat(filename1, first);

    /*Checks if the st_mime in the first struct is less than second's st_mtime
     *field to show that file 1 was created before file 2.*/
    if (first->st_mtime < second->st_mtime)
      return 1;
  }

  /*Returns 0 if anything went wrong or if file 2 was created before file 1.*/
  return 0;
}


/*This function does the action line associated with the target that is 
 *associated by the parameter rule_num.*/
int do_action(Forkfile forkfile, int rule_num) {

  /*Variables to be used in this function.*/
  char **array = NULL, *name = NULL;
  Node *curr_tar = NULL, *curr_act = NULL;
  int i = 0, length = 0, status = 0;
  pid_t pid = 0;

  /*Checks if the forkfile parameter is valid.*/
  if (forkfile.targets != NULL) {

    /*Calls the helper function to get the current target associated with the
     *rule number.*/
    curr_tar = get_rule(forkfile, rule_num);

    /*Checks if the current target node is valid to be used.*/
    if (curr_tar != NULL) {

      /*Sets curr_act to the first action word.*/
      curr_act = ((Target *)(curr_tar->data))->action->head;

      /*Gets the number of words in the action line and adds one to set the 
       *last element to NULL.*/
      length = (((Target *)(curr_tar->data))->action->counter) + 1;

      /*Allocates space in memory for a doubke pointer to store the action 
       *line.*/
      array = malloc(sizeof(*array) * sizeof(length));

      /*Checks if the malloc was successful.*/
      if (array != NULL) {

	/*Iterates through all the action words.*/
	while (curr_act != NULL) {

	  /*Allocates space in memory for each word.*/
	  name = malloc(sizeof(*name) *
			(strlen(((Element *)(curr_act->data))->name) + 1));

	  /*Copies each word.*/
	  strcpy(name,((Element *)(curr_act->data))->name);

	  /*Points each element in the array to point to the newly copied 
	   *word. Sets curr_act to the next node and increments i.*/
	  array[i] = name;
	  curr_act = curr_act->next;
	  i++;
	}

	/*Sets the last element to NULL.*/
	array[i] = NULL;

	/*Forks the function into the parent and child processes.*/
	pid = safe_fork();

	/*Checks if the process is the parent.*/
	if (pid > 0) {

	  /*Waits for the child to finish and sets the exit status.*/
	  wait(&status);

	  /*Use WIFEEXITED since it returns true if the child exited normally 
	   *and returns the exit status.*/
	  if (WIFEXITED(status))
	    return status;
	}

	/*Enters in this if  the process isn't the parent process.*/
	else {

	  /*Checks if the process is the child process.*/
	  if (pid == 0) {

	    /*Executes the action line.*/
	    execvp(array[0], array);
	    exit(0);
	  }

	  /*Exits if not a parent or a child process.*/
	  else
	    exit(1);
	}
      }      
    }
  }

  /*Returns -1 if it didn't exit normally or there isn't a rule associated with 
   *rule_num.*/
  return -1;
}
