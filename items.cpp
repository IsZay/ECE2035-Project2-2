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
    
    printf("Rand is: %d\n", rand());
    printf("Rand is: %d\n", rand());
    int randomVariable = rand() % 16;
    int randomVariable2 = (rand() % 15) + 1;
    printf("Rand is: %d\n ", randomVariable);
    int randomType = rand() % 3 + 1;


    for (int i = 0; i < 10; i++) {
        Item* item = (Item*) malloc(sizeof(Item*));
        item->type = randomType; //1 is fruit, 2 is boost, 3 is poison
        item->data = NULL; 
        item->position.x = (randomVariable); // Lowkey I don't know all of the positions that are possible
        item->position.y = randomVariable2;
        if (i == 0) {
            item->position.x = 0; // Lowkey I don't know all of the positions that are possible
            item->position.y = 1;
        }
        insertTail(items->items_list, item);
    }
    draw_items();

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
    LLNode* currNode = getHead(items->items_list);
    Item* currItem = (Item*) currNode->data;
    for (int i = 0; i < NUM_ITEMS; i++) {
        // draw 10 items, thats a lot!
        printf("currNode is %p\n", currNode);
        printf("CurrItem is %p\n", currItem);
        printf("x coordinate: %d\n", currItem->position.x);
        printf("y coordinate: %d\nThe Fruit for this node is ", currItem->position.y);
        if (currItem->type == 1) {
            // draw Fruit
            printf("Fruit!\n\n");
            draw_fruit(currItem->position.x, currItem->position.y); // I have no idea how to use that function pointer in items.h struct
        } else if (currItem->type == 2) {
            printf("Boost!\n\n");
            draw_boost(currItem->position.x, currItem->position.y);
        } else if (currItem->type == 3) {
            printf("Poison!\n\n");
            draw_poison(currItem->position.x, currItem->position.y);
        }
        currNode = currNode->next;
    }
}

Items* get_items(void) {
    return items;
}