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
    uLCD.printf("hint: implement read_inputs().\n");
    printf("The beginning ran!\n");

    // This loop is for the start screen
    // While the user has not provided an input, the game should remain on the start screen
    while(1){
        // 2035TODO
        // you need to implement read_inputs to get past the start screen!!
        inputs = read_inputs(); // inputs is the struct in hardware.cpp
        // I don't know if its set to be low tho in the beginning, inputs b1-b3 really
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
    
    // printf("print again to end initialization\n");
    // uLCD.printf("Push Again!");

    
    //  while(1){
    //     // 2035TODO
    //     // you need to implement read_inputs to get past the start screen!!
    //     inputs = read_inputs(); // inputs is the struct in hardware.cpp
    //     // I don't know if its set to be low tho in the beginning, inputs b1-b3 really
    //     if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3) {
    //         srand(t.elapsed_time().count()); // this line sets the random seed
    //         break;
    //     }
    // }

    // So I went to snake.h and snake.cpp
    // But I didn't know how to make SnakeItems (i could make the snake struct fine)
    // So I went to Items and had the same issue


    uLCD.baudrate(115200);
    
    int tick = 0;

    int score = 0; // use snake->score
    int boostValue = 0; // use snake->boosted
    // 2035TODO
    // Implement the main game loop
    while(1)
    {

        wait_us(40000); // Recovery time 
        // wait_us(4000000); // Recovery time    

        // 1. draw the items and the snake
        // uLCD.cls();
        draw_items(); // This feature might not be implemented right! 
        draw_snake(); // Neither lowkey


        // 2. print the score and the snake's 'boosted' value at the top of the screen
            // check out uLCD.locate() and uLCD.printf()
        
        uLCD.locate(0, 0); // I hope thats a good location
        uLCD.printf("Score:%d Boost: %d ", score, boostValue); // make score variable
        


        // 3. check for collision -> if a GAME-ENDING collision occurs, end the game with a game over screen
            // self collision
            // item collision
            // wall colliison
        if (check_self_collision()) {
            //Game ending collision
            uLCD.cls();
            uLCD.locate(24, 24);
            uLCD.printf("GAME OVER");
            break;
        }
        if (check_item_collision()) {
            //increase score if fruit
            // how to get the fruit that it collided with?
            uLCD.printf("\nYou should have eaten somn");
            printf("\nIn terminal, you shoulda eaten somn\n");
        }
        if (check_wall_collision()){
            //Game ending collision
            uLCD.cls();
            uLCD.locate(0, 9);
            uLCD.printf("GAME OVER");
            break;
        }

        // 4. check if the snake's score >= 10 -> if so end the game with a game win screen
            // for 3 and 4, check out uLCD.cls()
        if (score >= 10) {
            uLCD.cls();
            uLCD.locate(0, 9);
            uLCD.printf("YOU WIN!! WOW");
            break;
        }


        // 5. read the user inputs and update the snake direction if necessary
        GameInputs allButtons = read_inputs();
        if (allButtons.b1) {
            printf("b1 was pressed!\n");
        } else if (allButtons.b2) {
            // Only let one button be active at a time for maybe?
            printf("b2 was pressed!\n");
        } else if (allButtons.b3) {
            // Only let one buton be active at a time for maybe?
            printf("b3 was pressed!\n");
        } else if (allButtons.b4) {
            // Only let one button be active at a time for maybe?
            printf("b4 was pressed!\n");
        }

        if (allButtons.up) {
            // Only let one button be active at a time for maybe?
            printf("up was pressed!\n");
            
            // move_snake();
        } else if (allButtons.down) {
            printf("down was pressed!\n");
            // move_snake();
        } else if (allButtons.right) {
            printf("right was pressed!\n");
            // move_snake();
        } else if (allButtons.left) {
            printf("left was pressed!\n");
            // move_snake();
        } else if (allButtons.center) {
            printf("center was pressed!\n");
            // move_snake();
        }


        // 6. move the snake (you might not want the snake to move every loop)
        if (tick % 16 == 0) {
            // Move the snake now!
            // move_snake();
            move_snake();
            // printf("\n\n\n\n\nMove snake right now!\n\n\n\n\n");
            
        }
        printf("\n");
        tick++;
        t.reset();
    }

    printf("out of main loop\n");
    destroyList(get_snake()->snake_list);
    destroyList(get_items()->items_list);

    return 0;
}