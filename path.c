// Written by Diogo Tartarotti for CSC 161 Fall 2021 at Grinnell College

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "path.h"
#include "position.h"


list_t * 
list_add ( position_t position, list_t* current){
  
  list_t * added = malloc(sizeof(list_t));

  if(added == NULL){
    printf("Memory could not be allocated.\n");
    return NULL;
  }
  added->position = position;
  added->next = current;

  return added;
}//list_add



position_t
list_front (list_t* current){

  assert(current != NULL);
  
  return current->position;
}//list_front



void
list_print_reverse ( list_t* list){
  
  list_t* reversed = NULL;
  list_t* current = list;
  
  while (current != NULL){
    list_t* next = current->next;
    current->next = reversed;
    reversed = current;
     current = next;
      }
  for(list_t * temp = reversed ; temp != NULL ; temp = temp->next)
    printf("%d,%d\n", (temp->position).row, (temp->position).col);
  
}//list_print_reverse


void
list_free ( list_t* list){

list_t* current = list;
 while (current != NULL){
    list_t* helper = current;
    current = current->next;
    free(helper);
  }
 list = NULL;
}//list_free
