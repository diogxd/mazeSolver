// Written by Diogo Tartarotti for CSC 161 Fall 2021 at Grinnell College

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "path.h"
#include "queue.h"

void
queue_initialize (queue_t * queue){
  queue->front = NULL;
  queue->rear = NULL;
}//queue_initialize


bool
queue_empty (const queue_t * queue){
   return (queue->front == NULL  && queue->rear == NULL);
}//queue_empty


bool
enqueue (queue_t * queue, list_t* path){

  node_t * new_node = (node_t*)malloc(sizeof(node_t));

  if(new_node == NULL){
    printf("There is not more memory to be allocated");
    return false;
  }//if

  new_node->solution = path;
  new_node->next = NULL;

  if(queue_empty(queue)){
    queue->front = new_node;
    queue->rear = new_node;
    return true;
  }//if
  
  (queue->rear)->next = new_node;

  queue->rear = new_node;

  return true; 
}//enqueue

list_t*
dequeue (queue_t * queue){
  
  assert(!queue_empty(queue));//verify the precondition

  node_t * first_node = queue->front;

  list_t * result = queue->front->solution;

  if(queue->front == queue->rear){
    queue->front = NULL;
    queue->rear = NULL; 
  }
 
  else queue->front = queue->front->next;//change the pointer of head

  free(first_node);
  
  return result; 
}//dequeue


list_t*
queue_front (const queue_t * queue){
  assert(!queue_empty(queue));

  return queue->front->solution;
}//queue_front
