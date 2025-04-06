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
    snake = (Snake*)malloc(sizeof(Snake));
    SnakeDLL = create_dlinkedlist();
    snake->snake_list = SnakeDLL;
    snake->length = 10;
    snake->score = 0;
    snake->direction = RIGHT;
    snake->previous_tail_position.x = 0;
    snake->previous_tail_position.y = 0;
    snake->boosted = 0;
    int xCoordinate = 1;
    int yCoordinate = 8;
    
    for (int i = 0; i < snake->length; i++) {

        SnakeItem* newItem = (SnakeItem*) malloc(sizeof(SnakeItem));
        newItem->position.x = xCoordinate; // This is not correct lowkey
        newItem->position.y = yCoordinate;
        xCoordinate++;
        insertHead(SnakeDLL, newItem);
    }

    snake->previous_tail_position.x = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.x;
    snake->previous_tail_position.y = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.y;

    // Set the previous position of tail as its 
    draw_snake();
}

// 2035TODO
// This function updates the location of the SnakeItems in the Snake's DLL
void move_snake() {

    // Hint: you'll want to use previous_tail_position for this function

    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeItem = (SnakeItem*) currSnake->data;
    int oldNextX = currSnakeItem->position.x;
    int oldNextY = currSnakeItem->position.y;

    // Lets update the new direction for the head!
    // Okay update currNode's position
    // printf("snake->direction is %d\n", snake->direction;

    if (snake->direction == RIGHT) {
        currSnakeItem->position.x++; 
        // printf("You moved Right!\n");
    } else if (snake->direction == LEFT) {
        currSnakeItem->position.x--;
        // printf("You moved LEFT!\n");
    } else if (snake->direction == UPWARD) {
        currSnakeItem->position.y--;
        // printf("You moved UP!\n");
    } else if (snake->direction == DOWNWARD) {
        currSnakeItem->position.y++;
        // printf("You moved DOWN!\n");
    } else {
        // Do nothing
        // printf("You tried to move nowhere\n");
    }

    currSnake = currSnake->next; // This should be index 1 now
    int oldLocX;
    int oldLocY;
    for (int i = 1; i < snake->length; i++) {
        currSnakeItem = (SnakeItem*) currSnake->data; // Index 1's data
        oldLocX = currSnakeItem->position.x; // Store index 1's data
        oldLocY = currSnakeItem->position.y; // Store index 1's y position
        currSnakeItem->position.x = oldNextX; // Store index 0's x position
        currSnakeItem->position.y = oldNextY; // Store index 0's y position
        oldNextX = oldLocX; // Store Index 1's x
        oldNextY = oldLocY; // Store Index 1's y
        
        currSnake = currSnake->next;
    }

    // YES HE MOVES!!!!
    draw_nothing(snake->previous_tail_position.x, snake->previous_tail_position.y);
    
    snake->previous_tail_position.x = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.x;
    snake->previous_tail_position.y = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.y;

}

// 2035TODO
// This function should check if the Snake has collided with a wall, returns 1 on collision
// Note that the left and top of the uLCD are x=0 and y=0, respectively
// The right and bottom of the screen are SIZE_X/CELL_SIZE and SIZE_Y/CELL_SIZE, respectively
bool check_wall_collision() {
    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeHead = (SnakeItem*) currSnake->data;
    if (currSnakeHead->position.x == 16 || currSnakeHead->position.x == -1 || currSnakeHead->position.y == 0 || currSnakeHead->position.y == 16) {
        return 1;
    }
    return 0;
}


// 2035TODO
// This function should check if the Snake has collided with itself, returns 1 on collision
bool check_self_collision() {
    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeHead = (SnakeItem*) currSnake->data;

    currSnake = currSnake->next;
    for (int i = 1; i < snake->length; i++) {
        // Check the Head with every other index
        SnakeItem* currSnakeBody = (SnakeItem*) currSnake->data;
        if (currSnakeHead->position.x == currSnakeBody->position.x && currSnakeHead->position.y == currSnakeBody->position.y) {
            return 1;
        }
        currSnake = currSnake->next;
    }
    return 0;
}

// 2035TODO
// This function should increase the physical length of the Snake.
void grow_snake()
{
    // This should be O(1)
    SnakeItem* newItem = (SnakeItem*) malloc(sizeof(SnakeItem));
    // printf("%d, %d\n", snake->previous_tail_position.x, snake->previous_tail_position.y);
    newItem->position.x = snake->previous_tail_position.x; // This is not correct lowkey
    newItem->position.y = snake->previous_tail_position.y;
    // previous tail position updates in move_snake()!
    
    insertTail(SnakeDLL, newItem);
    snake->length++;    
}

// 2035TODO
// This function should draw all the SnakeItems in the Snake linked list
void draw_snake(void) {
    LLNode* currItem = getHead(SnakeDLL);
    
    for (int i = 0; i < snake->length; i++) {
        SnakeItem* currSnakeItem = (SnakeItem*) currItem->data;
        if (i == 0) {
            draw_snake_head(currSnakeItem->position.x, currSnakeItem->position.y);
        } else  {
            draw_snake_body(currSnakeItem->position.x, currSnakeItem->position.y);
        }
        currItem = currItem->next;
    }
}

Snake* get_snake(void) {
    return snake;
}

point get_snake_head_location(void) {

    LLNode* head = SnakeDLL->head;
    return ((SnakeItem*)head->data)->position;
}


