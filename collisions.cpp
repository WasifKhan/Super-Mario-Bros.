/*
 * .cpp file is for collisions
*/

// Required files
#include "include/collisions.h"
#include "include/events.h"
#include "include/drawings.h"
#include "include/classes.h"
#include "include/error.h"

// Preprocessor definitions
#define numObjects 200
// Using the standard namespace
using namespace std;


extern bool endGame;
extern Mario mario;
extern int distanceToBowser;
extern int width;
extern int height;
extern int points;
extern Bullet bullet1;
extern Bullet bullet2;
extern Bullet bullet3;
extern Mushroom Mushrooms[];
extern Shell Shells[];
Object lstOfObjects[ numObjects ];
int tablePosition = 0;

/*
Initialize the table
*/
void initTable()
{
	for ( int i = 0; i < numObjects; i++ )
	{
		Object ob;
		lstOfObjects[ i ] = ob;
	}
}

/*
Adds an object entry to the table
*/
int addToTable( string type, int x, int y, int a, int b )
{
	Object ob( type, x, y, a, b, true );
	lstOfObjects[ tablePosition ] = ob;
	tablePosition ++;
	return tablePosition - 1;
}

/*
Checks of an object collided with Mario
*/
bool collided( Object ob )
{
	if ( ob.getUse() )
	{
		for ( posn p = ob.getBtm(); p != ob.getTop(); p.y0 -- )
		{
			for ( posn q = mario.getBtmRight(); q != mario.getTopRight(); q.y0 -- )
			{
				if ( q.x0 - 30 <= p.x0 && p.x0 <= q.x0 && p.y0 == q.y0 )
				{
					return true;
				}
			}
		}
	}
	return false;
}

/*
Handles collisions based on what they are
*/
void handleCollision( XInfo& xInfo, Object ob, int i )
{
	if ( ob.getType() == "stair" )
	{
	}
	else if ( ob.getType() == "doubleStair" )
	{
	}
	else if ( ob.getType() == "mushroom" )
	{
		points ++;
		lstOfObjects[ i ].setUse( false );
		for ( int j = 0; j < 60; j ++ )
		{
			if ( Mushrooms[ j ].tablePos == i )
			{
				Mushrooms[ j ].inUse = false;
			}
		}
	}
	else if ( ob.getType() == "shell" )
	{
		if ( points > 0 )
		{
			points --;
		}
		lstOfObjects[ i ].setUse( false );
		for ( int j = 0; j < 60; j++ )
		{
			if ( Shells[ j ].tablePos == i )
			{
				Shells[ j ].inUse = false;
			}
		}
	}
	else if ( ob.getType() == "bullet" )
	{
		drawText( xInfo, "Bowser has killed you. You lose!", 180, 210 );
		endGame = true;
	}
	else if ( ob.getType() == "peach" )
	{
		drawText( xInfo, "Congrats, you have saved Princess Peach. You Win!", 120, 210 );
		endGame = true;
	}
}

/*
Checks every object in use for collisions
*/
void checkCollisions( XInfo& xInfo )
{
	for( int i = 0; i < numObjects; i++ )
	{
		if ( collided( lstOfObjects[ i ] ))
		{
			handleCollision( xInfo, lstOfObjects[ i ], i );
			break;
		}
	}
}

