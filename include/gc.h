/*
 * .h file for initialization
*/

#ifndef GC_H
#define GC_H

// Required files
#include <iostream>
#include "classes.h"

/*
Function that makes all the Graphic's Context
*/
GC getGC( XInfo& xInfo, std::string str );

#endif

