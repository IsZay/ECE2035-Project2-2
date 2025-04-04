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
    
    // printf("Rand is: %d\n", rand());
    // printf("Rand is: %d\n", rand());
    // int randomVariable = rand() % 16;
    // int randomVariable2 = (rand() % 15) + 1;
    // printf("Rand is: %d\n ", randomVariable);
    // int randomType = rand() % 3 + 1;
    int xCoordinate = 14;
    int yCoordinate = 1;


    for (int i = 0; i < 10; i++) {
        Item* item = (Item*) malloc(sizeof(Item));
        item->type = i % 3 + 1; //1 is fruit, 2 is boost, 3 is poison
        item->position.x = xCoordinate; // Lowkey I don't know all of the positions that are possible
        item->position.y = yCoordinate; // The location auto defaults to 0?
 
        // printf("The item node is %p\n", item);
        
        //0x10002AF0 (0,1)
        //0x10002B08 (14,2)
        //0x10002B20 (14,3)

        //CurrItem is 0x10002AF0
        item->data = NULL; 
        if (i == 0) {
            item->position.x = 0; // Lowkey I don't know all of the positions that are possible
            item->position.y = 1;
        }

        // printf("item's position x coord: %d\n", item->position.x);
        // printf("item's position y coord: %d\n", item->position.y);
        
        yCoordinate += 1;
        insertTail( (items->items_list) , item);
    }
    draw_items();

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