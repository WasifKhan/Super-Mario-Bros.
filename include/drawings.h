/*
 * .h file for drawings
*/

#ifndef DRAWINGS_H
#define DRAWINGS_H

// Required files
#include <iostream>
#include "init.h"
#include "classes.h"

/*
This function draws the introduction to explain the rules
*/
void introduction( XInfo& xInfo );

/*
This function draws the starting window
This includes the baseline, the sun, starting objects and Mario
*/
void drawScene( XInfo& xInfo );

/*
Draws text in middle of screen
*/
void drawText( XInfo& xInfo, std::string s, int x, int y );
/*
Removes "Press SPACE To Start"
*/
void removeStartMessage( XInfo& xInfo );

/*
Draws the top background for sun animation
*/
void drawTop( XInfo& xInfo, posn p);

/*
Draws the baseline in bowserMode
*/
void drawGround( XInfo& xInfo );

/*
Draws peach
*/
void drawPeach( XInfo& xInfo );

/*
Draws the blue backgruond in different shades
*/
void drawBackground( XInfo& xInfo );

/*
Disappear function for objects
*/
void disappear( XInfo& xInfo, Object ob );

/*
Erases previous mario
*/
void erasePreviousMario( XInfo& xInfo );

#endif

