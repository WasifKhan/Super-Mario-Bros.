/*
 * .h file for collisions
*/

#ifndef COLLISIONS_H
#define COLLISIONS_H

// Required files
#include <iostream>
#include "classes.h"


/*
table initializer
*/
void initTable();

/*
Add to collisions table
*/
int addToTable( std::string type, int x, int y, int a, int b );

/*
Checks collisions
*/
void checkCollisions( XInfo& xInfo );

#endif

