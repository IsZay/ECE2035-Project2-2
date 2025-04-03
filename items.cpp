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

Items* items;

// 2035TODO
// This function should initialize the Items struct and populate its linked list with 10 Item.
void items_init(void)
{
    // items = create_dlinkedlist();
    // int xCoordinate = 15 * 8;
    // int yCoordinate = 8;
    // // locations should be RANDOMLY GENERATED
    // // locations should NOT overlap with other items or the snake
    // for (int i = 0; i < NUM_ITEMS; i++) {
    //     Item* newItem = (Item*) malloc(sizeof(Item));

    //     newItem->point->x = xCoordinate; // This is not correct lowkey, not random at all!!!!!!
    //     newItem->point->y = yCoordinate;
    //     xCoordinate -= 8;
    //     yCoordinate += 8;
        
    //     // I don't know what else
        
    //     items.insertAfter(newItem); // I have less than no clue how to use insertAfter with this list
    // }
}


// 2035TODO
// This function should check if the snake's head collides with any items and handle each possible collision accordingly
// Should return 1 for a GAME-ENDING collision, 0 otherwise
bool check_item_collision() {
    // If an item is eaten, it should be replaced at a new location

    return 0;
}

// 2035TODO
// This function should delete and replace an item that was eaten by the snake
void replace_item(LLNode* current_item) {

}

//2035TODO
// This function should draw all of the items in the Items linked list
// This should be VERY similar to the draw_snake() function
void draw_items(void) {
    // Item currItem = items.getHead();
    // for (int i = 0; i < NUM_ITEMS; i++) {
    //     // draw 10 items, thats a lot!
    //     if (currItem->type == 1) {
    //         // draw Fruit
    //         draw_fruit(currItem->position->x, currItem->position->y); // I have no idea how to use that function pointer in items.h struct
    //     } else if (currItem->type == 2) {
    //         draw_boost(currItem->position->x, currItem->position->y);
    //     } else if (currItem->type == 3) {
    //         draw_poison(currItem->position->x, currItem->position->y);
    //     }
    //     currItem = currItem->next;
    // }
}

Items* get_items(void) {
    return items;
}