// ============================================
// The Snake class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "doubly_linked_list.h"
#include "hardware.h"
#include <string>
#include <typeinfo>
#include "graphics.h"
#include "snake.h"

Snake* snake;
DLinkedList* SnakeDLL = NULL;

// 2035TODO
// This function should initialize the Snake struct and populate its linked list with 10 SnakeItems.
void snake_init()
{   

    // snake has already been created  thankfully
    SnakeDLL = create_dlinkedlist();
    printf("Alright you created the SnakeDLL\n");
    
    // for (int i = 0; i < 100; i++) {}
    // snake = ;
    // snake->score = 0;
    // snake->direction = NONE;
    snake->length = 3;
    // snake->previous_tail_position.x = 0;
    // snake->previous_tail_position.y = 0;
    // snake->boosted = 0;
    int xCoordinate = 1;
    int yCoordinate = 1;
    
    // now that we have a new list, we can add all the items to it
    // Take a look at snake.h tclect i = 0; i < snake->length; i++) {
        // Lets just keep inserting to Tail (that way the first we store will be the head)
        // Then add the node to the list
        
        // how do I get the data which is a SnakeItem?
    for (int i = 0; i < snake->length; i++) { // This went on forever!
        printf("Started for loop\n");
        SnakeItem* newItem = (SnakeItem*) malloc(sizeof(SnakeItem));
        newItem->position.x = xCoordinate; // This is not correct lowkey
        newItem->position.y = yCoordinate;
        xCoordinate += 1; // I'm pretty sure I want to do ++ not += 8
        yCoordinate += 1; // Like I'm pretty pretty sure
        
        // I don't know what else
        printf("Before insertTail\n");
        insertTail(SnakeDLL, newItem); // I have less than no clue how to use insertAfter with this list
        // The data field of LLNode is newItem!
        printf("After insertTail\n");
    }
    // snake->length = 3;
    // draw_snake(); //TODO Pretty sure I need to draw_snake
}

// 2035TODO
// This function updates the location of the SnakeItems in the Snake's DLL
void move_snake() {
    // Hint: you'll want to use previous_tail_position for this function

}

// 2035TODO
// This function should check if the Snake has collided with a wall, returns 1 on collision
// Note that the left and top of the uLCD are x=0 and y=0, respectively
// The right and bottom of the screen are SIZE_X/CELL_SIZE and SIZE_Y/CELL_SIZE, respectively
bool check_wall_collision() {
    return 0;
}


// 2035TODO
// This function should check if the Snake has collided with itself, returns 1 on collision
bool check_self_collision() {
    return 0;
}

// 2035TODO
// This function should increase the physical length of the Snake.
void grow_snake()
{
    
}

// 2035TODO
// This function should draw all the SnakeItems in the Snake linked list
/*
Unlike a function declaration, a function pointer declaration wraps the function name in parentheses and precedes it with an asterisk. Here is an example:

int function(int x, int y); // a function taking two int arguments and returning an int
int (*pointer)(int x, int y); //  a pointer to such a function
*/
void draw_snake(void) {
    // LLNode* currItem = getHead(SnakeDLL);
    // SnakeItem* currSnakeItem = (SnakeItem*) currItem->data; 
    // for (int i = 0; i < snake->length; i++) {
    //     // draw 10 items, thats a lot!
    //     if (i == 0) { 
    //         draw_snake_head(currSnakeItem->position.x, currSnakeItem->position.y); // I have no idea how to use that function pointer in items.h struct
    //     } else  {
    //         draw_snake_body(currSnakeItem->position.x, currSnakeItem->position.y);
    //     }
    //     currItem = currItem->next;
    // }


   
}

Snake* get_snake(void) {
    return snake;
}

point get_snake_head_location(void) {

    LLNode* head = SnakeDLL->head;
    return ((SnakeItem*)head->data)->position;
}


