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

    for (int i = 0; i < NUM_ITEMS; i++) {
        Item* item = (Item*) malloc(sizeof(Item));
        item->type = i % 3 + 1; //1 is fruit, 2 is boost, 3 is poison
        // item->position.x = rand() % 16;
        // item->position.y = rand() % 15 + 1;
        // As you add all 10 items, you might get a collision with the snake or another new item!
        
        bool position_ok = false;

        while (!position_ok) {
            int xCoordinate = rand() % 16; // an x coordinate
            int yCoordinate = rand() % 15 + 1; // a y coordinate

            // Check if (xCoordinate, yCoordinate) collides with the snake
            LLNode* currSnake = getHead(get_snake()->snake_list);
            position_ok = true;

            while (currSnake != NULL) {
                SnakeItem* currSnakeItem = (SnakeItem*)currSnake->data;
                if (currSnakeItem->position.x == xCoordinate && currSnakeItem->position.y == yCoordinate) {
                    position_ok = false;
                    break;
                }
                currSnake = currSnake->next;
            }

            currSnake = getHead(items->items_list);

            while (currSnake != NULL) {
                Item* currItem = (Item*)currSnake->data;
                if (currItem->position.x == xCoordinate && currItem->position.y == yCoordinate) {
                    position_ok = false;
                    break;
                }
                currSnake = currSnake->next;
            }

            if (position_ok) {
                item->position.x = xCoordinate;
                item->position.y = yCoordinate;
                break;
            }
        }
        insertTail( (items->items_list) , item);
    }
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

    LLNode* currNode = getHead(items->items_list);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Check the Head with every other index
        Item* currItem = (Item*) currNode->data;
        if (currSnakeHead->position.x == currItem->position.x && currSnakeHead->position.y == currItem->position.y) {
            // You found a collision but not necessarily game ending!
            if (currItem->type == 1) {
                // draw Fruit
                get_snake()->score++;
                if (get_snake()->boosted) {
                    get_snake()->score++;
                }
                grow_snake();
                // draw_nothing(currItem->position.x, currItem->position.y);
                draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
                replace_item(currNode);

            } else if (currItem->type == 2) {
                // draw Boost
                get_snake()->boosted += 5;
                // printf("You are trying to boost, but I don't know how to make you\n");
                // draw_boost(currItem->position.x, currItem->position.y);
                // draw_nothing(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
                draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
                replace_item(currNode);
            } else if (currItem->type == 3) {
                // draw Poison
                // printf("Poison!\n\n");
                if (get_snake()->score) {
                    get_snake()->score--;
                    if (get_snake()->score && get_snake()->boosted) {
                        get_snake()->score--;
                    }
                }

            // draw_nothing(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
            draw_snake_head(currSnakeHead->position.x, currSnakeHead->position.y);
            replace_item(currNode);

            } else {
                // When implementing a game ending poison, return 1
                printf("Ate unknown fruit as of right now?!");
                return 1;
            }
        }
        currNode = currNode->next;
    }
    return 0;
}

// 2035TODO
// This function should delete and replace an item that was eaten by the snake
void replace_item(LLNode* current_item) {

    Item* item = (Item*) current_item->data;


    bool position_ok = false;

    while (!position_ok) {
        int xCoordinate = rand() % 16; // an x coordinate
        int yCoordinate = rand() % 15 + 1; // a y coordinate

        // Check if (xCoordinate, yCoordinate) collides with the snake
        LLNode* currSnake = getHead(get_snake()->snake_list);
        position_ok = true;

        while (currSnake != NULL) {
            SnakeItem* currSnakeItem = (SnakeItem*)currSnake->data;
            if (currSnakeItem->position.x == xCoordinate && currSnakeItem->position.y == yCoordinate) {
                position_ok = false;
                break;
            }
            currSnake = currSnake->next;
        }

        currSnake = getHead(items->items_list);

        while (currSnake != NULL) {
            Item* currItem = (Item*)currSnake->data;
            if (currItem->position.x == xCoordinate && currItem->position.y == yCoordinate) {
                position_ok = false;
                break;
            }
            currSnake = currSnake->next;
        }

        if (position_ok) {
            item->position.x = xCoordinate;
            item->position.y = yCoordinate;
            break;
        }
    }
    // Now that you made it out, you know you found a new location

    if (((Item*)current_item->data)->type == 1) {
        // draw Fruit
        draw_fruit(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y); // I have no idea how to use that function pointer in items.h struct
    } else if (((Item*)current_item->data)->type == 2) {
        // draw Boost
        draw_boost(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y);
    } else if (((Item*)current_item->data)->type == 3) {
        // draw Poison
        draw_poison(((Item*)current_item->data)->position.x, ((Item*)current_item->data)->position.y);
    }
}

//2035TODO
// This function should draw all of the items in the Items linked list
// This should be VERY similar to the draw_snake() function
void draw_items(void) {

    LLNode* currNode = getHead(items->items_list);
    for (int i = 0; i < NUM_ITEMS; i++) {
        // draw 10 items, thats a lot!
        Item* currItem = (Item*) (currNode->data);
        if (currItem->type == 1) {
            // draw Fruit
            draw_fruit(currItem->position.x, currItem->position.y);
        } else if (currItem->type == 2) {
            // draw Boosted
            draw_boost(currItem->position.x, currItem->position.y);
        } else if (currItem->type == 3) {
            // draw Poison
            draw_poison(currItem->position.x, currItem->position.y);
        }

        currNode = currNode->next;

    }
}

Items* get_items(void) {
    return items;
}