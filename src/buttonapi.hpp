// #ifndef BUTTONAPI
// #define BUTTONAPI


// /*                  GLOBAL DEFINITIONS
//  * 
//  *      These global variables are used across this program to maintain state (choices)
//  *
//  */
// #include "vex.h"
// #include "robotdevices.h"

// // storage for our auton selection
// int   autonomousSelection = -1;

// /* 
//         James Pearman autoselect functions and definitions. These are modified for Walsh
// */
// // collect data for on screen button and include off and on color feedback for button
// // prc - instead of radio approach with one button on or off at a time, each button has
// //          a state.  ie shootPreload may be low yellow and high yellow when on.
// typedef struct _button {
//     int    xpos;
//     int    ypos;
//     int    width;
//     int    height;
//     bool   state;
//     vex::color offColor;
//     vex::color onColor;
//     const char *label;
// } button;

// // Button array definitions for each software button. The purpose of each button data structure
// // is defined above.  The array size can be extended, so you can have as many buttons as you 
// // wish as long as it fits.
// button buttons[] = {
//     {   30,  30, 60, 60,  false, 0xE00000, 0x0000E0, "++++" },
//     {  150,  30, 60, 60,  false, 0x303030, 0xD0D0D0, "----" },
//     {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "" },
//     {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "" },
//     {   30, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "" },
//     {  150, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "" },
//     {  270, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "" },
//     {  390, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "" }
// };

// // forward ref
// void displayButtonControls( int index, bool pressed );

// /*-----------------------------------------------------------------------------*/
// /** @brief      Check if touch is inside button                                */
// /*-----------------------------------------------------------------------------*/
// int findButton(  int16_t xpos, int16_t ypos ) {
//     int nButtons = sizeof(buttons) / sizeof(button);

//     for( int index=0;index < nButtons;index++) {
//       button *pButton = &buttons[ index ];
//       if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
//         continue;

//       if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
//         continue;

//       return(index);
//     }
//     return (-1);
// }

// /*-----------------------------------------------------------------------------*/
// /** @brief      Init button states                                             */
// /*-----------------------------------------------------------------------------*/
// void
// initButtons() {
//     int nButtons = sizeof(buttons) / sizeof(button);

//     for( int index=0;index < nButtons;index++) {
//       buttons[index].state = false;
//     }
// }

// /*-----------------------------------------------------------------------------*/
// /** @brief      Screen has been touched                                        */
// /*-----------------------------------------------------------------------------*/
// void
// userTouchCallbackPressed() {
//     int index;
//     int xpos = Brain.Screen.xPosition();
//     int ypos = Brain.Screen.yPosition();

//     if( (index = findButton( xpos, ypos )) >= 0 ) {
//       displayButtonControls( index, true );
//     }

// }

// /*-----------------------------------------------------------------------------*/
// /** @brief      Screen has been (un)touched                                    */
// /*-----------------------------------------------------------------------------*/
// void
// userTouchCallbackReleased() {
//     int index;
//     int xpos = Brain.Screen.xPosition();
//     int ypos = Brain.Screen.yPosition();

//     if( (index = findButton( xpos, ypos )) >= 0 ) {
//       // clear all buttons to false, ie. unselected
//       //      initButtons(); 

//       // now set this one as true
//       if( buttons[index].state == true) {
//       buttons[index].state = false; }
//       else    {
//       buttons[index].state = true;}

//       // save as auton selection
//       autonomousSelection = index;

//       displayButtonControls( index, false );
//     }
// }

// /*-----------------------------------------------------------------------------*/
// /** @brief      Draw all buttons                                               */
// /*-----------------------------------------------------------------------------*/
// void
// displayButtonControls( int index, bool pressed ) {
//     vex::color c;
//     Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

//     for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

//       if( buttons[i].state )
//         c = buttons[i].onColor;
//       else
//         c = buttons[i].offColor;

//       Brain.Screen.setFillColor( c );

//       // button fill
//       if( i == index && pressed == true ) {
//         Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
//       }
//       else
//         Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

//       // outline
//       Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

// // draw label
//       if(  buttons[i].label != NULL )
//         Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
//     }
// }


// #endif
