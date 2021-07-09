/*Johann Antisseril, johann, 116533928, 0207
 *
 *I pledge on my honor that I have not given or recieved any unauthorized
 *assistance on this assignment.
 *
 *The objective of this project is to understand how to work with linked list
 *in C. By using structures as the data structures named Node and
 *Two_sided_queue, it is possible to link data together and be able to traverse
 *through it. By using pointers, each structure is linked together and with
 *each new structure added to this list, memory is allocated. Conversely, if
 *an element is removed from this list, the list proceeds as if it weren't 
 *there and removed its allocated spot in memory.
 */

#include <stdio.h>
#include "two-sided-queue.h"
#include <stdlib.h>


/*This function initializes the structure to be used if it is not NULL*/
void init(Two_sided_queue *const twosq) {
  /*Checks if the argument being passed in is NULL.*/
  if (twosq != NULL)

    /*Assigns the head node to NULL to show nothing is in the structure yet.*/
    twosq->head = NULL;
}

/*This function adds a new element with the value being passed in into the
 *linked list.*/
int add_front(Two_sided_queue *const twosq, int new_value) {
  /*Creates the new element to be added.*/
  Node *new_item;

  /*Checks if the parameter being passed in is NULL.*/
  if (twosq != NULL) {

    /*Allocates memory to the new element.*/
    new_item = malloc(sizeof(Node));

    /*Checks if the memory allocation was successful.*/
    if(new_item != NULL) {

      /*Assigns each part of the new element in. */
      new_item->data = new_value;
      new_item->next = twosq->head;

      /*Lets the head node point to this new element.*/
      twosq->head = new_item;
      return 1;
    }
  }
  
  /*If anything was unsuccessful.*/
  return 0;
}

/*This function adds a new element with a value that is being passed in to 
 *the back of the linked list.*/
int add_back(Two_sided_queue *const twosq, int new_value) {
  Node *curr = NULL, *prev = NULL, *new_item;

  /*Checks if the parameter is NULL.*/
  if (twosq != NULL) {

    /*Assigns curr to the first element and traverses until curr is NULL and
     *prev is the last element.*/
    curr = twosq->head;
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
    }

    /*Allocated memory for the new element to be added.*/
    new_item = malloc(sizeof(Node));

    /*Checks if the memory allocation was successful.*/
    if (new_item != NULL) {

      /*Assigns the fields of the structure of the new element.*/
      new_item->data = new_value;
      new_item->next = NULL;

      /*Checks if there are any elements already in the list. If so, it'll add
       *to the back, if not, it'll refer the head node to the new element.*/
      if (twosq->head != NULL)
	prev->next = new_item;
      else
	twosq->head = new_item;
      return 1;
    }
  }
  /*If anything was unsuccessful returns 0.*/
  return 0;
}

/*This function returns the number of element in the linked list.*/
int num_elements(Two_sided_queue *const twosq) {

  /*Declares and initializes the number of elements in the list.*/
  int num = 0;
  Node *curr = NULL;

  /*Checks if the parameter is NULL.*/
  if (twosq != NULL) {

    /*Traverses the entire list.*/
    curr = twosq->head; 
    while (curr != NULL) {

      /*Increments the counter everytime it visits an element in the list.*/
      num++;
      curr = curr->next;
    }
  }

  /*Returns the number of elements in the list.*/
  return num;
}

/*This function prints all the elements in the linked list.*/
void print(Two_sided_queue *const twosq) {
  Node *curr = NULL;

  /*Checks if the parameter was NULL and if there are any elements in 
   *the list.*/
  if (twosq != NULL && twosq->head != NULL) {

    /*Traverses the list up to and including the second to last element.*/
    curr = twosq->head;
    while (curr->next != NULL) {
      printf("%d ", curr->data);
      curr = curr->next;
    }

    /*Prints last element with a new line after it.*/
    printf("%d\n", curr->data);
  }
}


/*This function removes the first element of the linked list and puts it into
*a new pointer. It also releases the allocated memory space taken up by the
*element being removed.*/
int remove_front(Two_sided_queue *const twosq, int *value) {
  Node *curr = NULL;

  /*Checks if both parameters are NULL.*/
  if (twosq != NULL && value != NULL) {

    /*Initializes curr to refer to the head node.*/
    curr = twosq->head;

    /*Checks if there are any elements in the list.*/
    if (twosq->head != NULL) {

      /*Rereferences the head pointer to the next element.*/
      twosq->head = curr->next;

      /*Assigns a value to what the value pointer refers to.*/
      *value = curr->data;

      /*Frees the allocated space in memory held by this element.*/
      free(curr);
      return 1;
    }
  }

  /*Returns 0 if anything was unsuccessful.*/
  return 0;
}

/*This function removes the last element from the linked list and puts it into 
 *a new pointer. It also releases the allocated memory space taken up by the 
 *element being removed.*/
int remove_back(Two_sided_queue *const twosq, int *value) {
  Node *curr = NULL, *prev = NULL;

  /*Checks if both parameters are NULL.*/
  if (twosq != NULL && value != NULL) {

    /*Initializes curr to refer to the head node.*/
    curr = twosq->head;

    /*Checks if there are any elements in the list.*/
    if (twosq->head != NULL) {

      /*Traverses the list until curr refers to the last element and prev
       *refers to the second to last element in the list.*/
      while (curr->next != NULL) {
	prev = curr;
	curr = curr->next;
      }

      /*Assigns a value to what the value pointer refers to.*/
      *value = curr->data;

      /*Assigns the next element to NULL to denote the end of the list.*/
      prev->next = NULL;

      /*Frees the memory space taken up by curr.*/
      free(curr);
      return 1;
    }
  }

  /*Returns 0 if anything goes wrong.*/
  return 0;
}
    
