// ============================================
// The Graphics file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "graphics.h"
#include "globals.h"

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define ORANGE 0xFFA500
#define PURPLE 0xA020F0

#include <stdint.h>


// 2035TODO
// You should create your own sprite, but feel free to use this one while setting up your game!
const char* fruit_img =
    "000BG000"
    "000B0000"
    "0RRRRRR0"
    "RRRRRRRR"
    "RRRRRRRR"
    "RRRRRRRR"
    "0RRRRRR0"
    "00RRRR00";

const char* poison_img =
    "000BG000"
    "000B0000"
    "0YYYYYY0"
    "YYYYYYYY"
    "YYYYYYYY"
    "YYYYYYYY"
    "0YYYYYY0"
    "00YYYY00";

const char* boost_img =
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBWBB"
    "WWWWWWWB"
    "WWWWWWWW"
    "WWWWWWWB"
    "BBBBBWBB"
    "BBBBBBBB";
    // "000YG000"
    // "000Y0000"
    // "0BBBBBB0"
    // "BBBBBBBB"
    // "BBBBBBBB"
    // "BBBBBBBB"
    // "0BBBBBB0"
    // "00BBBB00";

const char* snake_head_img =
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW";

const char* snake_body_img =
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG"
    "GGGGGGGG";

const char* nothing_img =
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000";
    // "00000000" // use this to debug nothing img i guess
    // "00000000"
    // "00000000"
    // "RRRRRRRR"
    // "RRRRRRRR"
    // "00000000"
    // "00000000"
    // "00000000";
const char* speed_img =
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB"
    "BBBBBBBB";  

const char* death_img =
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW"
    "WWWWWWWW";  


static const uint32_t poison_data[1][64] = {
{
0x00000000, 0xff00ff71, 0xff00ff71, 0xff00ff71, 0xff00ff71, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffff00cf, 0xff00ff71, 0xff00ff71, 0xffff00cf, 0xffff00cf, 0x00000000, 
0x00000000, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffffffff, 0xffff00cf, 
0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffff00cf, 
0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffff00cf, 0xffff00cf, 
0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffff00cf, 
0x00000000, 0xffff00cf, 0xffffffff, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffffffff, 0xffff00cf, 
0x00000000, 0x00000000, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0xffff00cf, 0x00000000
}
};



static const uint32_t speedboost_data[1][64] = {
{
0x00000000, 0xff00ff5b, 0xff00ff5b, 0xff00ff5b, 0xff00ff5b, 0xff00ff5b, 0xff00ff5b, 0x00000000, 
0xff00ff5b, 0xff00ff5b, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00ff5b, 0xff00ff5b, 
0xff00ff5b, 0x00000000, 0x00000000, 0xfff9ec00, 0xfff9ec00, 0x00000000, 0x00000000, 0xff00ff5b, 
0xff00ff5b, 0x00000000, 0xfff9ec00, 0x00000000, 0x00000000, 0xfff9ec00, 0x00000000, 0xff00ff5b, 
0xff00ff5b, 0xfff9ec00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff9ec00, 0xff00ff5b, 
0xff00ff5b, 0x00000000, 0x00000000, 0xfff9ec00, 0xfff9ec00, 0x00000000, 0x00000000, 0xff00ff5b, 
0xff00ff5b, 0x00000000, 0xfff9ec00, 0x00000000, 0x00000000, 0xfff9ec00, 0x00000000, 0xff00ff5b, 
0xff00ff5b, 0xfff9ec00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff9ec00, 0xff00ff5b
}
};

static const uint32_t long_data[1][64] = {
{
0x00000000, 0x00000000, 0x00000000, 0xff00a2ff, 0xff00a2ff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0x00000000, 0x00000000, 
0x00000000, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0x00000000, 
0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 0xff75e5ff, 0xff75e5ff, 0xff00a2ff, 0xff00a2ff, 0xff00a2ff, 
0xff00a2ff, 0xff00a2ff, 0xff75e5ff, 0xff75e5ff, 0xff75e5ff, 0xff75e5ff, 0xff00a2ff, 0xff00a2ff, 
0xff00a2ff, 0xff75e5ff, 0xff75e5ff, 0xfffff200, 0xfffff200, 0xff75e5ff, 0xff75e5ff, 0xff00a2ff, 
0xff00a2ff, 0xff75e5ff, 0xfffff200, 0xfffff200, 0xfffff200, 0xfffff200, 0xff75e5ff, 0xff00a2ff, 
0xff00a2ff, 0xff75e5ff, 0xfffff200, 0xffff3e00, 0xffff3e00, 0xfffff200, 0xff75e5ff, 0xff00a2ff
}
};

static const uint32_t newfruit_data[1][64] = {
{
0x00000000, 0xffff6000, 0xffff6000, 0x00000000, 0x00000000, 0xffff6000, 0x00000000, 0x00000000, 
0xffff6000, 0x00000000, 0xffff6000, 0xffff6000, 0xffff6000, 0xffff6000, 0xffff6000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffff6000, 0xff00ff01, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0x00000000, 
0x00000000, 0xff00ff01, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xff00ff01, 
0xff00ff01, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xff00ff01, 0xff00ff01, 
0xff00ff01, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xffec00ff, 0xff00ff01, 0xff00ff01, 0x00000000, 
0x00000000, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0xff00ff01, 0x00000000, 0x00000000
}
};

static const uint32_t armor_data[1][64] = {
{
0xffd500ff, 0xffff006a, 0xffd500ff, 0xffffd000, 0xffffd000, 0xffd500ff, 0xffff006a, 0xffd500ff, 
0xffd500ff, 0xffd500ff, 0xffff006a, 0xffd500ff, 0xffd500ff, 0xffff006a, 0xffd500ff, 0xffd500ff, 
0xffff006a, 0xffd500ff, 0xffffd000, 0xffff006a, 0xffff006a, 0xffffd000, 0xffd500ff, 0xffff006a, 
0xffd500ff, 0xffff006a, 0xffd500ff, 0xffffd000, 0xffffd000, 0xffd500ff, 0xffff006a, 0xffd500ff, 
0xffff006a, 0xffffd000, 0xffff006a, 0xffffd000, 0xffffd000, 0xffff006a, 0xffffd000, 0xffff006a, 
0xffd500ff, 0xffff006a, 0xffffd000, 0xffff006a, 0xffff006a, 0xffffd000, 0xffff006a, 0xffd500ff, 
0xffffd000, 0xffffd000, 0xffff006a, 0xffff006a, 0xffff006a, 0xffff006a, 0xffffd000, 0xffffd000, 
0xffd500ff, 0xffffd000, 0xffd500ff, 0xffff006a, 0xffff006a, 0xffd500ff, 0xffffd000, 0xffd500ff
}
};


/* Piskel data for "PoisonTemp" */

// This takes a location (x,y) and const char* as input, and prints a sprite onto the screen
void draw_img(int x, int y, const char* img) {
    int colors[CELL_SIZE*CELL_SIZE];
    for (int i = 0; i < CELL_SIZE*CELL_SIZE; i++)
    {
        switch(img[i]) {
            case 'R':
                colors[i] = RED;
                break;
            case 'Y':
                colors[i] = YELLOW;
                break;
            case 'B':
                colors[i] = BROWN;
                break;
            case 'G':
                colors[i] = GREEN;
                break;
            case 'W':
                colors[i] = WHITE;
                break;
            case '0':
                colors[i] = BLACK;
                break;
            default:
                colors[i] = BLACK;
        }
    }
    uLCD.BLIT(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, colors);
    wait_us(250); // Recovery time!
}

// 2035TODO
void draw_fruit(int x, int y)
{
    draw_img(x,y, fruit_img);
    wait_us(250);
    // 1. call draw_img OR uLCD.BLIT() to draw a custom sprite that you create
    // 2. OR implement functionality that draws a CELL_SIZExCELL_SIZE square using the uLCD.filled_rectangle function
    // Recall the grid structure of the uLCD screen.
    // CELL_SIZE is 8 in the provided code, and the real size of the uLCD screen is 128x128
    // filled_rectangle takes x1, y1, x2, y2 that define the bounding points (top left, bottom right) of a filled rectangle IN uLCD COORDINATES
    // you must convert the passed in x,y coordinates (which correspond to a 16x16 grid of cells) to uLCD coordinates before drawing the rectangle

}



// 2035TODO
// the remainder of these functions should be handled the same way as draw_fruit
void draw_poison(int x, int y)
{
    draw_img(x,y, poison_img);
    wait_us(250);
}

void draw_boost(int x, int y)
{
    draw_img(x,y,boost_img);
    wait_us(250);
}

void draw_snake_body(int x, int y)
{
    draw_img(x,y,snake_body_img);
    wait_us(250);
}

void draw_snake_head(int x, int y)
{
    draw_img(x,y,snake_head_img);
    wait_us(250);
    
}

void draw_nothing(int x, int y)
{
    draw_img(x,y,nothing_img);
    wait_us(250);
}

void draw_speed(int x, int y)
{
    uLCD.BLIT(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, (int *) speedboost_data);
    wait_us(250);
}

void draw_death(int x, int y)
{

    uLCD.BLIT(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, (int *) poison_data);
    wait_us(250);
}

void draw_long(int x, int y) {
    uLCD.BLIT(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, (int *) long_data);
    wait_us(250);
}

void draw_again(int x, int y) {
    uLCD.BLIT(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, (int *) newfruit_data);
    wait_us(250);
}

void draw_armor(int x, int y) {
    uLCD.BLIT(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, (int *) armor_data);
    wait_us(250);
}