// Written by Diogo Tartarotti for CSC 161 Fall 2021 at Grinnell College

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "position.h"
#include "path.h"
#include "queue.h"
#include "maze.h"

cell_t
readCell(maze_t * maze, position_t position){
  
  if(position.row < 0 || position.col < 0)//check if position is within boundaries
    return BLOCKED;
  else if (position.row >= maze->height || position.col >= maze->width)//check if position is within boundaries
    return BLOCKED;
  return maze->cells[offset(maze, position)];//returning cell of passed position
}

list_t*
pathFinder (maze_t * maze){

  queue_t queue;

  queue_initialize(&queue);//initializing queue

  list_t * path = NULL; //initializing variable to store paths

  list_t * empty = NULL;
  
  list_t * start = list_add(maze->start,empty);//creating the starting path

  bool startAssigned = enqueue(&queue, start);//enqueueing starting path

  if(!startAssigned){
    printf("Start position could not be assigned.\n");
    return NULL;
  }//checking if start 
  
  while(!queue_empty(&queue)){

  PATH :path = dequeue(&queue);//dequeueing a path

    position_t pos = list_front(path); // current position
    
    if (path == NULL)//check if path is empty
      return NULL;
    
    cell_t current = readCell(maze, pos);//reads cell value of path front position

    if(current == VISITED || current == BLOCKED)//check if cell was visited before or is blocked
      goto PATH;//if cell was visited, dequeue next path in queue
    
    if (current == END)//check if current cell is OPEN or START
      break;

    maze->cells[offset(maze, pos)] = VISITED;  //marks current cell as visited

    //Neighboring Positions
    
    position_t north,south,east,west;

    north.row = pos.row - 1;
    north.col = pos.col;

    south.row = pos.row + 1;
    south.col = pos.col;

    east.row = pos.row;
    east.col = pos.col + 1;
   
    west.row = pos.row;
    west.col = pos.col - 1;

    //Neighboring Cells
    
    cell_t nCell,sCell,eCell,wCell;

    nCell = readCell(maze, north);

    sCell = readCell(maze,south);

    eCell = readCell(maze,east);

    wCell = readCell(maze,west);

    if (nCell == OPEN || nCell == END){
      bool northAssigned = enqueue(&queue, list_add(north, path));

      if (!northAssigned){
	printf("Failed to assigned north neighbor.\n");
	return NULL;
      }//if
    }//if
    
    if (sCell == OPEN || sCell == END){
      bool southAssigned =  enqueue(&queue, list_add(south, path));

      if (!southAssigned){
	printf("Failed to assigned south neighbor.\n");
	return NULL;
      }//if
    }//if
    if (eCell == OPEN || eCell == END){
      bool eastAssigned =  enqueue(&queue, list_add(east, path));

      if(!eastAssigned){
	printf("Failed to assigned east neighbor.\n");
	return NULL;
      }//if
      
    }//if
    if (wCell == OPEN || wCell == END)
      {
	bool westAssigned = enqueue(&queue, list_add(west, path));

	if(!westAssigned){
	  printf("Failed to assigned west neighbor.\n");
	  return NULL;
	}//if
      }//if
  }//while
  if (readCell(maze, list_front(path)) != END){
    return NULL;
  }
  return path;
}
int
main(void){


  maze_t * maze;

  
  maze = readMaze(stdin); //reads maze from file

  if(maze == NULL){
    printf("Failed to read maze\n");
    return 0;
  }//check if maze was read
    

  list_t * path = pathFinder(maze); //solving maze

  // freeMaze(maze);
  
  if (path == NULL)//check if maze was solved
    return 0;

  list_print_reverse(path);//printing solution

  return 0;
}
