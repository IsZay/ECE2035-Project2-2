// ============================================
// The file for all of the Mbed's hardware peripherals
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "globals.h"

#include "hardware.h"

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11); // LCD Screen (tx, rx, reset)
Nav_Switch myNav(p12, p15, p14, p16, p13); // initialize nav switch
BufferedSerial pc(USBTX, USBRX, 115200);  // USB Console (tx, rx)
DigitalIn button1(p21);  // Pushbuttons (pin) // This is pin SLeft
DigitalIn button2(p22);  // SRight
DigitalIn button3(p23);  // SUp
// Alright I think I need to add more here!
DigitalIn button4(p24);  // SDown (I'm gonna change these names later)

// Navigation Switch stuff
// should I have it called this? Thats what the constructor says in Nav_Switch.cpp
// Looks like PinName is part of "mbed.h"
// Nav_Switch 
// PinName up;
// PinName down;
// PinName left;
// PinName right;
// PinName center;
// Yo its already done on line 18 lol

AnalogOut DACout(p18); // Speaker (pin)
PwmOut speaker(p25); 

int hardware_init()
{    
    button1.mode(PullUp); 
    button2.mode(PullUp);
    button3.mode(PullUp);
    
    button4.mode(PullUp); // SDown

    // up.up();
    // down.down();
    // left.left();
    // right.right();
    // center.center();


    // I don't think thats correct, myNav.up() returns 0 or 1 (though it is a boolean)
    // This means that if the button is pressed or not is what returns 0 or 1
    // not if an error occured in initalization


    // // How do I initialize the 5 way navigation switch
    // if (myNav.up() || myNav.down() || myNav.left() || myNav.right() || myNav.center()) {
    //     // probably should print somn to the console to be like, a pin on the nav switch aint working!
    //     return ERROR_OCCURED; // I defined this, I don't know if this is right
    // }
    return ERROR_NONE;
}

// 2035TODO
// This function reads the inputs (nav switch, buttons) and stores their values in the GameInputs struct
// The current code is placeholder, replace it!
// HINT: lookup your NavSwitch under mbed site > Hardware> Components and look at demo code
// Thats the url
// https://os.mbed.com/components/
// https://os.mbed.com/users/4180_1/notebook/using-a-navigation-switch-digital-joystick/


GameInputs read_inputs()
{
    GameInputs in; // Initialize the struct
    
    // 1. read and invert the buttons (the buttons are active-low)
    in.b1 = !(button1.read()); // https://os.mbed.com/docs/mbed-os/v6.16/apis/digitalin.html
    in.b2 = !(button2.read());  // They are pulled up, so typically high
    in.b3 = !(button3.read());
    in.b4 = !(button4.read()); // I added button 4 since its on my breadboard already

    // 2. read the navswitch
    in.up= myNav.up();  // Okay notice this is bool going to int
    in.down= myNav.down();
    in.left= myNav.left();
    in.right = myNav.right();
    in.center = myNav.center();
    if (in.up) {
        printf("You are pressing up currently!\n");
    } else if (in.down) {
        printf("You are pressing down currently!\n");
    } else if (in.left) {
        printf("You are pressing left currently!\n");
    } else if (in.right) {
        printf("You are pressing right currently!\n");
    } else if (in.center) {
        printf("You are pressing center currently!\n");
    }

    return in;
}
// Should be finished

// A shortcut to serial port print
void print(const char* c)
{
    pc.write(c, strlen(c));
}