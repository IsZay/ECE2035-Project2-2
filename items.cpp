// ============================================
// The Items class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================



#include "items.h"
#include "snake.h"
#include "globals.h"
#include "graphics.h"
#include "doubly_linked_list.h"
#include <cstdlib>

Items* items;

// 2035TODO
// This function should initialize the Items struct and populate its linked list with 10 Item.
void items_init(void)
{
    items = (Items*) malloc(sizeof(Items*));
    items->items_list = create_dlinkedlist();
    items->data = NULL;
    
    // int xCoordinate = 13;
    // int yCoordinate = 1;


    for (int i = 0; i < NUM_ITEMS; i++) {
        Item* item = (Item*) malloc(sizeof(Item));
        item->type = i % 3 + 1; //1 is fruit, 2 is boost, 3 is poison
        // item->position.x = rand() % 16; // Lowkey I don't know all of the positions that are possible
        // item->position.y = rand() % 15 + 1; // The location auto defaults to 0?

            // Make sure that this location that we chose doesn't conflict with anything!
    // int max_x = SIZE_X / CELL_SIZE;
    // int max_y = SIZE_Y / CELL_SIZE;

    int attempts = 0;
    const int MAX_ATTEMPTS = 100;

    bool position_ok = false;

    while (!position_ok && attempts < MAX_ATTEMPTS) {
        int new_x = rand() % 16;
        int new_y = rand() % 15 + 1;

        // Check if (new_x, new_y) collides with the snake
        LLNode* node = get_snake()->snake_list->head;
        position_ok = true;

        while (node != NULL) {
            SnakeItem* s_item = (SnakeItem*)node->data;
            if (s_item->position.x == new_x && s_item->position.y == new_y) {
                position_ok = false;
                break;
            }
            node = node->next;
        }


        node = items->items_list->head;
        // position_ok = true;

        while (node != NULL) {
            Item* i_item = (Item*)node->data;
            if (i_item->position.x == new_x && i_item->position.y == new_y) {
                position_ok = false;
                break;
            }
            node = node->next;
        }

        if (position_ok) {
            item->position.x = new_x;
            item->position.y = new_y;
            break;
        }

        attempts++;
    }

    // Optionally handle the case where no position could be found
    if (!position_ok) {
        printf("WARNING: Could not find valid item position after %d attempts\n", MAX_ATTEMPTS);
    }
    
        
        // if (i != 0) {
        //     LLNode* currNode = getHead(items->items_list);
        //     for (int j = 0; j < i; j++) {

        //         Item* comparison = (Item*) currNode->data;
        //         // check every other item to make sure that they don't have your position's x and y
        //         if (comparison->position.x == item->position.x && comparison->position.y == item->position.y) {
        //             item->position.x = rand() % 16; // Lowkey I don't know all of the positions that are possible
        //             item->position.y = rand() % 15 + 1; // The location auto defaults to 0?
        //             // change the locations again
        //             // srand(rand()* 17 * 31 % rand());


        //             // start from the beginning again!
        //             // printf("Because you collided start over in items_init!\n");
        //             // printf("New x: %d\n", item->position.x);
        //             // printf("New y: %d\n", item->position.y);
        //             // j = 0;
        //             // currNode = getHead(items->items_list);
        //             // continue;


        //         }
        //         // otherwise, go to the next node and hope you escape!
        //         currNode = currNode->next;
        //     }
        // }


    item->data = NULL; 

    
    

        // printf("The item node is %p\n", item);
        
        //0x10002AF0 (0,1)
        //0x10002B08 (14,2)
        //0x10002B20 (14,3)

        //CurrItem is 0x10002AF0

        // if (i == 0) {
        //     item->position.x = 0; // Lowkey I don't know all of the positions that are possible
        //     item->position.y = 1;
        // }

        // printf("item's position x coord: %d\n", item->position.x);
        // printf("item's position y coord: %d\n", item->position.y);
        
        // yCoordinate += 1;
        insertTail( (items->items_list) , item);
    }



    

    LLNode* currNode = getHead(items->items_list);
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item* item = (Item*) currNode->data;
        printf("Item%d.x: %d\n", i, item->position.x);
        printf("Item%d.y: %d\n\n", i, item->position.y);
        currNode = currNode->next;
    }
    printf("\n\n\n\n\n");
    draw_items();

}


// 2035TODO
// This function should check if the snake's head collides with any items and handle each possible collision accordingly
// Should return 1 for a GAME-ENDING collision, 0 otherwise
bool check_item_collision() {
    // If an item is eaten, it should be replaced at a new location
    LLNode* currSnake = (LLNode*) getHead(get_snake()->snake_list);
    SnakeItem* currSnakeHead = (SnakeItem*) currSnake->data;
    // Okay now that you have the snake's head, check all spots
    
    // Items* theList = (Items*) getHead(items->items_list);
    LLNode* currNode = getHead(items->items_list);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Check the Head with every other index
        Item* currItem = (Item*) currNode->data;    // I hope this is right
        if (currSnakeHead->position.x == currItem->position.x && currSnakeHead->position.y == currItem->position.y) {
            // You found a collision but not necessarily game ending!
            if (currItem->type == 1) {
            // draw Fruit
            // printf("Fruit!\n\n");
            get_snake()->score++;
            if (get_snake()->boosted) {
                get_snake()->score++;
            }
            printf("You are eating element i: %d\n", i);
            printf("Incrementing score right now!!!!!!\n");
            grow_snake();
            draw_nothing(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
            draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
            replace_item(currNode);

            } else if (currItem->type == 2) {
            // draw Boost
            // printf("Boost!\n\n");
            get_snake()->boosted += 5;
            printf("You are trying to boost, but I don't know how to make you\n");
            // draw_boost(currItem->position.x, currItem->position.y);
            draw_nothing(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
            draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
            replace_item(currNode);
            } else if (currItem->type == 3) {
            // draw Poison
            // printf("Poison!\n\n");
            if (get_snake()->score) {
                get_snake()->score--;
                if (get_snake()->boosted) {
                    get_snake()->score--;
                }
            }

            draw_nothing(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
            draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
            replace_item(currNode);

            } else {
                // Okay what did you eat buddy
                printf("Ate unknown fruit as of right now?!");
                return 1;
            }
        }
        currNode = currNode->next;
    }


    // replace_item(LLNode* itemNode);
    return 0;
}

// 2035TODO
// This function should delete and replace an item that was eaten by the snake
void replace_item(LLNode* current_item) {

    // int max_x = SIZE_X / CELL_SIZE;
    // int max_y = SIZE_Y / CELL_SIZE;

    int attempts = 0;
    const int MAX_ATTEMPTS = 100;

    bool position_ok = false;

    while (!position_ok && attempts < MAX_ATTEMPTS) {
        int new_x = rand() % 16;
        int new_y = rand() % 15 + 1;

        // Check if (new_x, new_y) collides with the snake
        LLNode* node = get_snake()->snake_list->head;
        position_ok = true;

        while (node != NULL) {
            SnakeItem* s_item = (SnakeItem*)node->data;
            if (s_item->position.x == new_x && s_item->position.y == new_y) {
                position_ok = false;
                break;
            }
            node = node->next;
        }


        node = items->items_list->head;
        // position_ok = true;

        while (node != NULL) {
            Item* i_item = (Item*)node->data;
            if (i_item->position.x == new_x && i_item->position.y == new_y) {
                position_ok = false;
                break;
            }
            node = node->next;
        }



        if (position_ok) {
            ((Item*)current_item->data)->position.x = new_x;
            ((Item*)current_item->data)->position.y = new_y;
            break;
        }

        attempts++;
    }

    // Optionally handle the case where no position could be found
    if (!position_ok) {
        printf("WARNING: Could not find valid item position after %d attempts\n", MAX_ATTEMPTS);
    }

    
    // Item* item = (Item*) current_item->data; // The item we want to replace
    // LLNode* currNode = getHead(items->items_list);
    
    //         for (int j = 0; j < NUM_ITEMS; j++) {
    //             printf("j is %d\n", j);
    //             Item* comparison = (Item*) currNode->data; // Head index 1, 2, 3, 4, 5, 6, to 9
    //             printf("Comparison x: %d\n", comparison->position.x);
    //             printf("Comparison y: %d\n", comparison->position.y);
    //             // check every other item to make sure that they don't have your position's x and y
    //             if (comparison->position.x == item->position.x && comparison->position.y == item->position.y) {
    //                 // srand();
    //                 item->position.x = rand() % 16;
    //                 item->position.y = rand() % 15 + 1;
    //                 // item->position.x = (item->position.x * 17) % 16; // Lowkey I don't know all of the positions that are possible
    //                 // item->position.y = (item->position.y * 23) % 15 + 1; // The location auto defaults to 0?
    //                 // change the locations again

    //                 // start from the beginning again!
                    
    //                 printf("Because you collided start over in replace_item!\n");
    //                 printf("New x: %d\n", item->position.x);
    //                 printf("New y: %d\n", item->position.y);
    //                 printf("Comparisonx: %d\n", comparison->position.x);
    //                 printf("Comparisony: %d\n", comparison->position.y);
    //                 j = -1;
    //                 currNode = getHead(items->items_list);
    //             } else{
    //             // otherwise, go to the next node and hope you escape!
    //                 currNode = currNode->next;
    //             }
    //         }

    if (((Item*)current_item->data)->type == 1) {
            // draw Fruit
            // printf("Fruit!\n\n");
            draw_fruit(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y); // I have no idea how to use that function pointer in items.h struct
        } else if (((Item*)current_item->data)->type == 2) {
            // draw Boost
            // printf("Boost!\n\n");
            draw_boost(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y);
        } else if (((Item*)current_item->data)->type == 3) {
            // draw Poison
            // printf("Poison!\n\n");
            draw_poison(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y);
        }

        printf("Finished replacing item of type %d\n", ((Item*)current_item->data)->type);
}

//2035TODO
// This function should draw all of the items in the Items linked list
// This should be VERY similar to the draw_snake() function
void draw_items(void) {

    LLNode* currNode = getHead(items->items_list);
    for (int i = 0; i < NUM_ITEMS; i++) {
        // draw 10 items, thats a lot!
        Item* currItem = (Item*) (currNode->data);


        // printf("currNode is %p\n", currNode);
        // printf("CurrItem is %p\n", currItem);
        // printf("x coordinate: %d\n", currItem->position.x); // This is really not working
        // printf("y coordinate: %d\n", currItem->position.y);

        if (currItem->type == 1) {
            // draw Fruit
            // printf("Fruit!\n\n");
            draw_fruit(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
        } else if (currItem->type == 2) {
            // draw Boost
            // printf("Boost!\n\n");
            draw_boost(currItem->position.x, currItem->position.y);
        } else if (currItem->type == 3) {
            // draw Poison
            // printf("Poison!\n\n");
            draw_poison(currItem->position.x, currItem->position.y);
        }

        currNode = currNode->next;

    }
}

Items* get_items(void) {
    return items;
}