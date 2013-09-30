/*
 * .h file for events
*/

#ifndef EVENTS_H
#define EVENTS_H

// Required files
#include <X11/Xlib.h>
#include "classes.h"

/*
Event function
*/
void eventLoop( XInfo& xInfo );

/*
Displays points at top
*/
void displayPoints( XInfo& xInfo );

#endif

