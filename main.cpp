//=================================================================
// The main program file.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <cstdio>
#include <stdlib.h>

// Project Includes
#include "globals.h"
#include "hardware.h"
#include "mbed_retarget.h"
#include "snake.h"
#include "items.h"
#include "doubly_linked_list.h"

#define TICK_RATE 2



int main()
{

    printf("Initialization starting\n");
    GameInputs inputs;
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    
    Timer t;
    t.start();

    // This is the text that prints on the start screen
    uLCD.printf("Press any button to start.\n");
    uLCD.locate(0,3);
    // uLCD.printf("hint: implement read_inputs().\n");
    // printf("The beginning ran!\n");

    // This loop is for the start screen
    // While the user has not provided an input, the game should remain on the start screen
    while(1){
        // 2035TODO
        // you need to implement read_inputs to get past the start screen!!
        inputs = read_inputs(); // get the current buttons
        if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3 || inputs.b4) {
            srand(t.elapsed_time().count()); // this line sets the random seed
            break;
        }
    }

    uLCD.cls();

    // 2035TODO
    // initialize the Snake and the Items
    snake_init(); // They return nothing, so don't bother doing Snake theSnake = snake_init()
    items_init(); // I will assume these functions workk

    // So I went to snake.h and snake.cpp
    // But I didn't know how to make SnakeItems (i could make the snake struct fine)
    // So I went to Items and had the same issue


    uLCD.baudrate(115200);
    
    int tick = 0;
    // 2035TODO
    // Implement the main game loop
    while(1)
    {
        
        wait_us(30000);
        // wait_us(40000); // Recovery time 
        // wait_us(4000000); // Recovery time  
        if (tick % 2 == 0) {
            // I do not want the snake to move everytime, so every other iteration move

            // 1. draw the items and the snake
            // uLCD.cls();
            draw_items(); 
            draw_snake();


            // 2. print the score and the snake's 'boosted' value at the top of the screen
                // check out uLCD.locate() and uLCD.printf()
            uLCD.locate(0, 0); // I hope thats a good location
            uLCD.printf("Score:%d Boost: %d ", get_snake()->score, get_snake()->boosted); // make score variable
            


            // 3. check for collision -> if a GAME-ENDING collision occurs, end the game with a game over screen
                // self collision
                // item collision
                // wall colliison
            if (check_self_collision()) {
                //Game ending collision
                uLCD.cls();
                uLCD.locate(0, 3);
                uLCD.printf("GAME OVER");
                break;
            }
            if (check_item_collision()) {
                // This tick % 2 helps it not increase twice!
                //increase score if fruit
                // how to get the fruit that it collided with?
                // uLCD.printf("\nYou should have eaten somn");
                uLCD.cls();
                uLCD.locate(0, 3);
                uLCD.printf("You at a bad fruit\nGAME OVER");
            }
            if (check_wall_collision()){
                //Game ending collision
                uLCD.cls();
                uLCD.locate(0, 3);
                uLCD.printf("GAME OVER");
                break;
            }

            // 4. check if the snake's score >= 10 -> if so end the game with a game win screen
                // for 3 and 4, check out uLCD.cls()
            if (get_snake()->score >= 10) {
                uLCD.cls();
                uLCD.locate(0, 2);
                uLCD.printf("YOU WIN!!\nWOW");
                break;
            }

            // 5. read the user inputs and update the snake direction if necessary
            inputs = read_inputs();

            if  (inputs.up && (get_snake()->direction != DOWNWARD)) { 
                get_snake()->direction = UPWARD;
            } else if (inputs.down && (get_snake()->direction != UPWARD)) { 
                get_snake()->direction = DOWNWARD; 
            } else if (inputs.right == 1 && (get_snake()->direction != LEFT)) { 
                get_snake()->direction = RIGHT;
            } else if (inputs.left && (get_snake()->direction != RIGHT)) { 
                get_snake()->direction = LEFT; 
            }

            // 6. move the snake (you might not want the snake to move every loop)
            if (tick % 2 == 0) {
                move_snake();
                if (get_snake()->boosted) {
                    get_snake()->boosted--; // Boost should decrease for every new frame
                }
            }
        }
        tick++;
        t.reset();
    }

    printf("out of main loop\n");
    destroyList(get_snake()->snake_list);
    destroyList(get_items()->items_list);

    return 0;
}