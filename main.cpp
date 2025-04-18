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

    // This is the text that prints on the start screen'
    int page = 3;
    // uLCD.locate(0,5);
    // uLCD.printf("SNAKE\n");
    // uLCD.printf("Welcome, scroll right to see all sprites\n");
    // uLCD.printf("Or left to  choose game difficulty\n");
    while (page >= 0) {
        inputs = read_inputs(); // get the current buttons
        wait_us(250);
        if (page == 0) {
            // You are on the Hard mode select
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(4,3);
            uLCD.printf("HARD MODE\n");
            uLCD.printf("Only one life\nOnly one fruit,\nthe rest poison\nand death fruits\n");
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.right) {
                    break;
                }
                if (inputs.center) {
                    page = -3;
                    srand(t.elapsed_time().count()); // this line sets the random seed
                    break;
                }
            }
        } else if (page == 1) {
            // You are on medium page
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(3,3);
            uLCD.printf("NORMAL MODE\n");
            uLCD.printf("3 lives\nAll fruits available\n");
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
                if (inputs.center) {
                    page = -2;
                    srand(t.elapsed_time().count()); // this line sets the random seed
                    break;
                }
            }
        } else if (page == 2) {
            // You are on easy mode
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(4,3);
            uLCD.printf("EASY MODE\n");
            uLCD.printf("5 lives\nOnly FRUIT\n");

            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
                if (inputs.center) {
                    page = -1;
                    srand(t.elapsed_time().count()); // this line sets the random seed
                    break;
                }
            }

        } else if (page == 3) {
            // You are on the main page
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(5,3);
            uLCD.printf("SNAKE\n\n\n");
            uLCD.printf("Welcome\nScroll right to\nsee all sprites\n\n");
            uLCD.printf("Or left to choose\ngame difficulty\n");
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }
            
        } else if (page == 4) {
            // You are showing the fruit sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("FRUIT\n\n\n");
            uLCD.printf("Adds score and\n");
            uLCD.printf("length by 1\n");
            draw_fruit(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }
            
        } else if (page == 5) {
            // You are showing the boost sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("BOOST\n\n\n");
            uLCD.printf("Doubles amount\n");
            uLCD.printf("recieved by fruits\n");
            draw_boost(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }

        } else if (page == 6) {
            // You are showing the poison sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("POISON\n\n\n");
            uLCD.printf("Decreases score\nby 1 but will\n");
            uLCD.printf("increase length\nby 1\n");
            draw_poison(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }

        } else if (page == 7) {
            // You are showing the slow sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("SLOW\n\n\n");
            uLCD.printf("Decreases speed\n");
            draw_speed(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }

        } else if (page == 8) {
            // You are showing the death sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("DEATH\n\n\n");
            uLCD.printf("Takes life away\n");
            draw_death(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }

        } else if (page == 9) {
            // You are showing the long sprite
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("LONG\n\n\n");
            uLCD.printf("Increases the\n");
            uLCD.printf("length by 3\n");
            draw_long(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left || inputs.right) {
                    break;
                }
            }

        } else if (page == 10) {
            // You are showing the green fruit item
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("FRUIT?\n\n\n");
            uLCD.printf("Same as FRUIT\n");
            uLCD.printf("Or is it?\n\n\n");
            uLCD.printf("It is\n");

            draw_again(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left) {
                    break;
                }
            }

        } else if (page == 11) {
            // You are showing the armor
            wait_us(75000);
            uLCD.cls();
            uLCD.locate(6,7);
            uLCD.printf("ARMOR\n\n\n");
            uLCD.printf("Supposed to protect\n");
            uLCD.printf("But ran out of\n");
            uLCD.printf("Advanced Fruits\nSo don't count on it\n");

            draw_armor(7, 3);
            while (1) {
                inputs = read_inputs(); // get the current buttons
                if (inputs.left) {
                    break;
                }
            }
        }
        

        if (inputs.left) {
            if (page) {
                page--;
            }
        }
        if (inputs.right) {
            if (page < 10) {
                page++;
            }
        }
    }
    printf("We ended with page: %d\n", page);
    // uLCD.printf("Press any top right button to start do easy mode!\n");
    // uLCD.printf("Press any other to do normal mode!\n");
    // uLCD.locate(0,3);
    // uLCD.printf("hint: implement read_inputs().\n");
    // printf("The beginning ran!\n");

    // This loop is for the start screen
    // While the user has not provided an input, the game should remain on the start screen
    // while(1){
    //     // 2035TODO
    //     // you need to implement read_inputs to get past the start screen!!
    //     inputs = read_inputs(); // get the current buttons
    //     // wait_us(1000000);
    //     // printf("b1: %d\n", inputs.b1); // The one thats barely holding on
    //     // printf("b2: %d\n", inputs.b2);
    //     // printf("b3: %d\n", inputs.b3);
    //     // printf("b4: %d\n", inputs.b4);
    //     if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3 || inputs.b4) {
            
    //         break;
    //     }
    // }

    uLCD.cls();

    // 2035TODO
    // initialize the Snake and the Items
    snake_init(); // They return nothing, so don't bother doing Snake theSnake = snake_init()
    int lives;
    if (page == -3) {
        // You wanted hard mode!
        items_hard_init();
        lives = 1;
    } else if (page == -1) {
        // You wanted easy mode!
        items_easy_init();
        lives = 5;
    } else {
        // Normal mode
        items_init();
        lives = 3; 
    }
    // So I went to snake.h and snake.cpp
    // But I didn't know how to make SnakeItems (i could make the snake struct fine)
    // So I went to Items and had the same issue


    uLCD.baudrate(115200);
    
    int tick = 0;
  
    // 2035TODO
    // Implement the main game loop
    while (1) {

    
        while(1)
        {
            // printf("b1: %d \n",inputs.b1);
            if (get_items()->data) {
                // Move faster or slower?
                wait_us(100000);
            } else {
                wait_us(20000);
            }
            // wait_us(40000); // Recovery time 
            // wait_us(4000000); // Recovery time  
            if (tick % 2 == 0) {

                if (inputs.b1) {
                    // pause game
                    uLCD.cls();
                    uLCD.locate(0, 3);
                    uLCD.printf("Game is paused, current score %d", get_snake()->score);
                    // int count = 0;
                    wait_us(1000000); // wait 5 seconds before doing it again
                    while (1) {   
                        wait_us(40000);
                        inputs = read_inputs();
                        if (inputs.b1) {
                            break;
                        }
                        // count++;
                    }
                    uLCD.cls();
                    // now draw everything again
                    // done in loop
                }
                // I do not want the snake to move everytime, so every other iteration move

                // 1. draw the items and the snake
                // uLCD.cls();
                draw_items(); 
                draw_snake();


                // 2. print the score and the snake's 'boosted' value at the top of the screen
                    // check out uLCD.locate() and uLCD.printf()
                uLCD.locate(0, 0); // I hope thats a good location
                uLCD.printf("SCR:%d B:%d S:%d", get_snake()->score, get_snake()->boosted, get_items()->data); // make score variable
                


                // 3. check for collision -> if a GAME-ENDING collision occurs, end the game with a game over screen
                    // self collision
                    // item collision
                    // wall colliison
                wait_us(5000);
                if (check_self_collision()) {
                    //Game ending collision
                    // uLCD.cls();
                    // uLCD.locate(0, 3);
                    // uLCD.printf("GAME OVER");
                    break;
                }
                if (check_item_collision()) {
                    // This tick % 2 helps it not increase twice!
                    //increase score if fruit
                    // how to get the fruit that it collided with?
                    // uLCD.printf("\nYou should have eaten somn");
                    // uLCD.cls();
                    // uLCD.locate(0, 3);
                    // uLCD.printf("You at a bad fruit\nGAME OVER");
                    break;
                }
                if (check_wall_collision()){
                    //Game ending collision
                    // uLCD.cls();
                    // uLCD.locate(0, 3);
                    // uLCD.printf("GAME OVER");
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

                wait_us(5000);
                // 6. move the snake (you might not want the snake to move every loop)
                if (tick % 2 == 0) {
                    move_snake();
                    if (get_snake()->boosted) {
                        get_snake()->boosted--; // Boost should decrease for every new frame
                    }
                    if (get_items()->data) {
                        get_items()->data--;
                    }
                }
            }
            tick++;
            t.reset();
            wait_us(5000);
        }
        if (get_snake()->score >= 10) {
            break;
        }

        lives--;
        if (!lives || get_snake()->score >= 10) {
            // Game ending collision
            uLCD.cls();
            uLCD.locate(0, 3);
            uLCD.printf("GAME OVER");
            break;
        }
        uLCD.cls();
        uLCD.printf("You have %d lives left!\n", lives);
        wait_us(5000000); // wait 5 seconds
        uLCD.cls(); 
        snake_reset();
        items_reset();

    }

    printf("out of main loop\n");
    destroyList(get_snake()->snake_list);
    destroyList(get_items()->items_list);

    return 0;
}
