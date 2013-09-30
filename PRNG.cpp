/*
 * .cpp file is for random block generator
*/

// Required files
#include <stdlib.h>
#include "include/PRNG.h"
#include "include/init.h"

// Using the standard namespace
using namespace std;


// Global variables
extern int width;
extern int height;


/*
Function that starts randomness
*/
void startRandom()
{
	srand( getpid() );
}

/*
Function that gets a random object
*/
Object getRandom()
{
	int i = rand() % 3;
	Object ob;
	if ( i == 0 )
	{
		ob.setType( "mushroom" );
	}
	else if ( i == 1 )
	{
		ob.setType( "shell" );
	}
	else if ( i == 2 )
	{
		ob.setType( "stair" );
	}
	return ob;
}

/*
Checks whether you need double stairs
*/
bool getDoubleStairs()
{
	int i = rand() % 3;
	if ( i == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}
