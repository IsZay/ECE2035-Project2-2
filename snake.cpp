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
    // snake->snake_list;
    SnakeDLL = create_dlinkedlist();
    // printf("Alright you created the SnakeDLL\n");
    snake->snake_list = SnakeDLL;
    
    // SnakeDLL = create_dlinkedlist();
    
    
    // for (int i = 0; i < 100; i++) {}
    // snake = ;
    snake->length = 10;
    snake->score = 0;
    snake->direction = RIGHT;
    snake->previous_tail_position.x = 0;
    snake->previous_tail_position.y = 0;
    snake->boosted = 0;
    int xCoordinate = 1;
    int yCoordinate = 8;
    
    // now that we have a new list, we can add all the items to it
    // Take a look at snake.h tclect i = 0; i < snake->length; i++) {
        // Lets just keep inserting to Tail (that way the first we store will be the head)
        // Then add the node to the list
        
        // how do I get the data which is a SnakeItem?
    for (int i = 0; i < snake->length; i++) { // This went on forever!
        // printf("Started for loop\n");
        SnakeItem* newItem = (SnakeItem*) malloc(sizeof(SnakeItem));
        newItem->position.x = xCoordinate; // This is not correct lowkey
        newItem->position.y = yCoordinate;
        xCoordinate += 1; // I'm pretty sure I want to do ++ not += 8
        yCoordinate += 0; // Like I'm pretty pretty sure
        
        // I don't know what else
        // printf("Before insertTail\n");
        insertHead(SnakeDLL, newItem); // I have less than no clue how to use insertAfter with this list
        // The data field of LLNode is newItem!
        // printf("After insertTail\n");
    }
    snake->previous_tail_position.x = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.x;
    snake->previous_tail_position.y = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.y;

    // printf("Snake is currently: %p\n", snake);
    // printf("The snake->list is: %p\n", snake->snake_list);
    // printf("The snake->snake_list as hex is %x\n ", snake->snake_list);
    // snake->snake_list = 0;
    // printf("The snake->list is: %p\n", snake->snake_list);
    // printf("The snake->snake_list as hex is %x\n ", snake->snake_list);

    
    // snake->length = 3;
    draw_snake(); //TODO Pretty sure I need to draw_snake
}

// 2035TODO
// This function updates the location of the SnakeItems in the Snake's DLL
void move_snake() {
    // Hint: you'll want to use previous_tail_position for this function
    
    // GameInputs inputs;
    // inputs = read_inputs();

    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeItem = (SnakeItem*) currSnake->data;
    int oldNextX = currSnakeItem->position.x;
    int oldNextY = currSnakeItem->position.y;


    // Lets update the new direction for the head!
            // Okay update currNode's position
        printf("snake->direction is %d\n", snake->direction);
        // if      (inputs.up && (snake->direction != DOWNWARD)) { printf("go Up move_snake()\ninputs.right is %d and snake->direction is %d\n", inputs.right, snake->direction); 
        // snake->direction = UPWARD;
        //  }
        // else if (inputs.down && (snake->direction != UPWARD)) { printf("go DOWN move_snake()\ninputs.right is %d and snake->direction is %d\n", 
        // inputs.right, snake->direction); 
        // snake->direction = DOWNWARD; }
        // else if (inputs.right == 1 && (snake->direction != LEFT)) { printf("go RIGHT move_snake()\n inputs.right is %d and snake->direction is %d\n", inputs.right, snake->direction); 
        // snake->direction = RIGHT; }
        // else if (inputs.left && (snake->direction != RIGHT)) { printf("go LEFT move_snake()\ninputs.right is %d and snake->direction is %d\n", inputs.right, snake->direction); 
        // snake->direction = LEFT; }
        // // else if (inputs.center) { snake->direction = NONE; }

        if (snake->direction == RIGHT) {
                currSnakeItem->position.x++; 
                printf("You moved Right!\n");
            } else if (snake->direction == LEFT) {
                currSnakeItem->position.x--;
                printf("You moved LEFT!\n");
            } else if (snake->direction == UPWARD) {
                currSnakeItem->position.y--;
                printf("You moved UP!\n");
            } else if (snake->direction == DOWNWARD) {
                currSnakeItem->position.y++;
                printf("You moved DOWN!\n");
            } else {
                // Do nothing
                printf("You tried to move nowhere\n");
            }


   // now that you moved the head, let the body follow
//    currSnake = currSnake->next;
// This is not working for sure
// currSnake: the Head
// currSnakeItem: the Head's data (SnakeItem*) type, observe that they're location already changed
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

    // Now change the tail's previous position to be blank
    
    printf("Taking away x pos: %d\n", snake->previous_tail_position.x);
    printf("Taking away y pos: %d\n", snake->previous_tail_position.y);
    
    
    // draw_nothing(oldLocX, oldLocY); // hopefully that's correct
    draw_nothing(snake->previous_tail_position.x, snake->previous_tail_position.y);

// ((SnakeItem*) (getHead(get_snake()->snake_list)->data))->position.x
    snake->previous_tail_position.x = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.x;
    snake->previous_tail_position.y = ((SnakeItem*) (getTail(snake->snake_list)->data))->position.y;
        
        
        // currSnakeItem = (SnakeItem*) currSnake->next->data; // we want the head to lead, and then share our direction with our past person
        // // Okay update currNode's position
        //     currSnakeItem->position.x = ((SnakeItem*) (currSnake->data))->position.x;
        //     currSnakeItem->position.y = ((SnakeItem*) (currSnake->data))->position.y;
        //     currSnake = currSnake->next;
        // }
}

// 2035TODO
// This function should check if the Snake has collided with a wall, returns 1 on collision
// Note that the left and top of the uLCD are x=0 and y=0, respectively
// The right and bottom of the screen are SIZE_X/CELL_SIZE and SIZE_Y/CELL_SIZE, respectively
bool check_wall_collision() {
    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeHead = (SnakeItem*) currSnake->data;
    // int oldNextX = currSnakeHead->position.x;
    // int oldNextY = currSnakeHead->position.y;
    currSnake = currSnake->next;
    for (int i = 1; i < snake->length; i++) {
        // Check the Head with every other index
        SnakeItem* currSnakeBody = (SnakeItem*) currSnake->data;
        if (currSnakeHead->position.x == 16 || currSnakeHead->position.x == -1 || currSnakeHead->position.y == 0 || currSnakeHead->position.y == 16) {
            return 1;
        }
        currSnake = currSnake->next;
    }
    return 0;
}


// 2035TODO
// This function should check if the Snake has collided with itself, returns 1 on collision
bool check_self_collision() {
    LLNode* currSnake = (LLNode*) getHead(snake->snake_list);
    SnakeItem* currSnakeHead = (SnakeItem*) currSnake->data;
    // int oldNextX = currSnakeHead->position.x;
    // int oldNextY = currSnakeHead->position.y;
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
    newItem->position.x = snake->previous_tail_position.x; // This is not correct lowkey
    newItem->position.y = snake->previous_tail_position.y;

    insertTail(SnakeDLL, newItem);
    snake->length++;
    }

// 2035TODO
// This function should draw all the SnakeItems in the Snake linked list
/*
Unlike a function declaration, a function pointer declaration wraps the function name in parentheses and precedes it with an asterisk. Here is an example:

int function(int x, int y); // a function taking two int arguments and returning an int
int (*pointer)(int x, int y); //  a pointer to such a function
*/
void draw_snake(void) {
    LLNode* currItem = getHead(SnakeDLL);
    
    for (int i = 0; i < snake->length; i++) {
        SnakeItem* currSnakeItem = (SnakeItem*) currItem->data;
        // draw 10 items, thats a lot!
        // printf("CurrItem is %p\n", currItem);
        // printf("currSnakeItem is %p\n", currSnakeItem);
        // printf("x coordinate: %d\n", currSnakeItem->position.x);
        // printf("y coordinate: %d\n", currSnakeItem->position.y);
        if (i == 0) {
            // printf("Draw the head now!\n");
            // printf("In draw snake, head's x: %d\n", ((SnakeItem*) currItem->data)->position.x);
            // printf("In draw snake, head's y: %d\n", ((SnakeItem*) currItem->data)->position.y);
            draw_snake_head(currSnakeItem->position.x, currSnakeItem->position.y); // I have no idea how to use that function pointer in items.h struct
        } else  {
            // The body is not following correctly!
            draw_snake_body(currSnakeItem->position.x, currSnakeItem->position.y);
        }
        currItem = currItem->next;
    }
    // printf("CurrItem is %p\n", currItem);
}

Snake* get_snake(void) {
    return snake;
}

point get_snake_head_location(void) {

    LLNode* head = SnakeDLL->head;
    return ((SnakeItem*)head->data)->position;
}


