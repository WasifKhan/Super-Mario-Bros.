/*
 * .h file for PRNG
*/

#ifndef PRNG_H
#define PRNG_H

// Required files
#include "classes.h"

/*
Generates a random block to place in a random location
*/
Object getRandom();

/*
Randomly gets double stairs if needed
*/
bool getDoubleStairs();

/*
Starts randomness
*/
void startRandom();

#endif

