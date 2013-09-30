/*
 * .cpp file to handle events
*/

// Required Files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/time.h>
#include <sstream>
#include "include/events.h"
#include "include/init.h"
#include "include/classes.h"
#include "include/error.h"
#include "include/drawings.h"
#include "include/collisions.h"
#include "include/PRNG.h"
#include "include/gc.h"

// Using the standard namespace
using namespace std;


// Global variables for settings and objects
int playable = 0; // wait for user to press SPACE
int holding = 0; // checks whether user is holding a key
int distanceToBowser = 3000;
int distanceSinceObject = 150;
int BufferSize = 10;
int jumpTime = 0;
int points = 0;
bool endGame = false;
int endTimer = 0;
extern int FPS;
extern int width;
extern int height;
extern int jumpSpeed;
int startWidth = 0;
int startHeight = 0;
int endWidth = width;
int endHeight = height;
Sun sun;
Mario mario;
Bowser bowser;
Ground ground;
Bullet bullet1;
Bullet bullet2;
Bullet bullet3;
Mushroom Mushrooms[60];
int mushroomCounter = 0;
Shell Shells[60];
int shellCounter = 0;
Stair Stairs[60];
int stairCounter = 0;
Win screen;

/*
Now function taken from course code
*/
unsigned long now()
{
	timeval tv;
	gettimeofday( &tv, NULL );
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

/*
Prevents user from holding a key down
*/
void holdingKeys()
{
	if ( holding != 0 )
	{
		holding ++;
	}
	if ( holding == 5 )
	{
		holding = 0;
	}

}

/*
Moves all objects on screen when screen moves
*/
void moveObjects( XInfo& xInfo )
{
	for ( int i = 0; i < 60; i++ )
	{
		if ( Mushrooms[ i ].inUse )
		{
			Mushrooms[ i ].move( xInfo );
		}
		if ( Shells[ i ].inUse )
		{
			Shells[ i ].move( xInfo );
		}
		if ( Stairs[ i ].inUse )
		{
			Stairs[ i ].move( xInfo );
		}
	}
}

/*
Paints all objects on screen
*/
void paintObjects( XInfo& xInfo )
{
	for ( int i = 0; i < 60; i++ )
	{
		if ( Mushrooms[ i ].inUse )
		{
			Mushrooms[ i ].paint( xInfo );
		}
		if ( Shells[ i ].inUse )
		{
			Shells[ i ].paint( xInfo );
		}
		if ( Stairs[ i ].inUse )
		{
			Stairs[ i ].paint( xInfo );
		}
	}
}

/*
Displays points at the top of the screen
*/
void displayPoints( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	string result;
	ostringstream convert;
	convert << points;
	result = convert.str();
	string s = "Current Points: " + result; 
	drawText( xInfo, s, 5+startWidth, 25+startHeight );
}

/*
Function to handle KeyPress
*/
void handleKeyPress( XInfo& xInfo, XEvent& event )
{
	KeySym key;
	char text[BufferSize];
	// i stores information about pressed key
	int i = XLookupString( ( XKeyEvent* )&event, text, BufferSize, &key, NULL );
	if ( i == 1 || key == 65363 || key == 65361 || key == 65362 )
	{
		if ( text[0] == 'q' )
		{
			error( "Hope you had fun!" );
		}
		else if ( playable == 1 && key == 32 )
		{
			playable = 0;
			drawText( xInfo, "Press SPACE To Start", 290, 290 );
		}
		else if ( playable == 0 && key == 32 )
		{
			playable = 1;
			removeStartMessage( xInfo );
		}
		else if ( playable == 1 && key == 65363 && distanceToBowser != 0 && !mario.getJumped() && holding == 0 )
		{
			if ( mario.getD() == 'l' )
			{
				mario.setD( 'r' );
				mario.setMove( 1 );
			}
			else if ( mario.getD() == 'r' )
			{
				mario.setD( 'r' );
				mario.setMove( 1 );
				mario.move( xInfo );
			}
			holding ++;
		}
		else if ( playable == 1 && key == 65361 && distanceToBowser != 0 && !mario.getJumped() && holding == 0 )
		{
			if ( mario.getD() == 'l' )
			{
				mario.setD( 'l' );
				mario.setMove( 1 );
				mario.move( xInfo );
			}
			else if ( mario.getD() == 'r' )
			{
				mario.setD( 'l' );
				mario.setMove( 1 );
			}
			holding ++;
		}
		else if ( playable == 1 && ( text[0] == 'j' || key == 65362 ) && distanceToBowser != 0 && !mario.getJumped() )
		{
			mario.setMove( 1 );
			mario.setJumped( true );
			mario.jump( xInfo );
		}
	}
}

/*
Handles resizing
*/
void handleResize( XInfo& xInfo, XEvent& event )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	XConfigureEvent xce = event.xconfigure;
	if ( xce.width != width || xce.height != height )
	{
		if ( xce.width < 800 || xce.height < 600 )
		{
			XFillRectangle( display, window, getGC( xInfo, "black" ), 0, 0, xce.width, xce.height );
			drawText( xInfo, "too small", 5, 25 );
		}
		else
		{
			XFillRectangle( display, window, getGC( xInfo, "black" ), 0, 0, xce.width, xce.height );
			drawText( xInfo, "Did not feel like resizing to bigger", 5, 25 );
			drawText( xInfo, "Please don't take too many marks off :)", 5, 50 );
		}
		playable = 0;
	}
}

/*
Land on box movement
*/
bool landOnBox()
{
	for ( int i = mario.getX()-15; i <= mario.getBtmRight().x0+15; i ++ )
	{
		for ( int j = 0; j < 60; j ++ )
		{
			if ( Stairs[ j ].inUse )
			{
				for ( int k = Stairs[ j ].getX(); k < Stairs[ j ].getX() + 50; k ++ )
				{
					if ( k  == i )
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*
Animation function
*/
void handleAnimation( XInfo& xInfo )
{
	if ( distanceSinceObject >= 150 && distanceToBowser != -1 )
	{
		Object a = getRandom();
		if ( a.getType() == "mushroom" )
		{
			Mushrooms[ mushroomCounter ].start( xInfo );
			mushroomCounter ++;	
		}
		else if ( a.getType() == "shell" )
		{
			Shells[ shellCounter ].start( xInfo );
			shellCounter ++; 
		}
		else if ( a.getType() == "stair" )
		{
			Stairs[ stairCounter ].start( xInfo );
			stairCounter ++;
		}
		distanceSinceObject = 0;
	}
	if ( mario.getJumped() )
	{
		jumpTime ++;
	}
	if ( jumpTime == jumpSpeed )
	{
		if ( landOnBox() && mario.onBox == false )
		{
			mario.onBox = true;
			mario.boxLand( xInfo );
		}
		else
		{
			mario.land( xInfo );
		}
	}
	if ( distanceToBowser != -1 && distanceToBowser != 0 )
	{
		sun.move( xInfo );
	}
	if ( mario.getX() >= endWidth / 2  && distanceToBowser != -1 && distanceToBowser != 0 )
	{
		distanceSinceObject += 25;
		distanceToBowser -= 25;
		moveObjects( xInfo );
		ground.move( xInfo );
	}
	if ( distanceToBowser == 0 )
	{
		mario.setX( endWidth + 200 );
	}
	// this if condition is for the "scene"
	if ( mario.getX() > endWidth + 100 )
	{
		if ( !bowser.inPosition() )
		{
			screen.move( xInfo );
			bowser.move( xInfo );
		}
		if ( bowser.inPosition() )
		{
			drawPeach( xInfo );
			addToTable( "peach", endWidth - 280, endHeight - 125, endWidth - 280, endHeight - 75 );
			drawGround( xInfo );
			mario.setX( 10 + startWidth );
			mario.setY( endHeight - 53 );
			mario.setJumped( false );
			mario.setMove( 1 );
			jumpTime = 0;
			mario.bowserMovement = 0;
			distanceToBowser = -1;
		}
	}
	// these are the animations for when in bowsermode
	if ( distanceToBowser == -1 )
	{
		if ( mario.bowserMovement >= 50 && !endGame )
		{
			mario.bowserMovement = 0;
			if ( !bullet1.inUse )
			{
				bullet1.start( xInfo );
			}
			else
			{
				if ( !bullet2.inUse )
				{
					bullet2.start( xInfo );
				}
				else
				{
					if ( !bullet3.inUse )
					{
						bullet3.start( xInfo );
					}
				}
			}
		}
		bullet1.move( xInfo );
		bullet2.move( xInfo );
		bullet3.move( xInfo );
	}
}

/*
Repaints the scene
*/
void repaint( XInfo& xInfo )
{
	if ( distanceToBowser == 2000 || distanceToBowser == 1000 )
	{
		drawBackground( xInfo );
		sun.paint( xInfo );
		mario.paint( xInfo );
		ground.paint( xInfo );
		distanceToBowser -= 25;
	}
	if ( distanceToBowser != -1 && distanceToBowser != 0 )
	{
		displayPoints( xInfo );
		paintObjects( xInfo );
		sun.paint( xInfo );
	}
	if ( mario.getX() >= endWidth / 2 && distanceToBowser != -1 && distanceToBowser != 0 )
	{
		ground.paint( xInfo );
	}
	if ( mario.getMove() == 1 && mario.getX() < endWidth + 200  && distanceToBowser != -1 && distanceToBowser != 0 )
	{
		mario.setMove( 0 );
		mario.paint( xInfo );
	}
	if ( mario.getJumped() && jumpTime == jumpSpeed && distanceToBowser != -1 && distanceToBowser != 0 )
	{
		mario.setJumped( false );
		jumpTime = 0;
		mario.paint( xInfo );
	}
	// for scene
	if ( distanceToBowser == 0 )
	{
		if ( !bowser.inPosition() )
		{
			screen.paint( xInfo );
			bowser.paint( xInfo );
		}
	}
	// for bowsermode
	if ( distanceToBowser == -1)
	{
		if ( mario.getMove() == 1 && !endGame )
		{
			mario.setMove( 0 );
			mario.newPaint( xInfo );
		}
		if ( mario.getJumped() && jumpTime == jumpSpeed && !endGame )
		{
			mario.setJumped( false );
			jumpTime = 0;
			mario.newPaint( xInfo );
		}
		drawPeach( xInfo );
		drawGround( xInfo );
		bullet1.paint( xInfo );
		bullet2.paint( xInfo );
		bullet3.paint( xInfo );
	}
	XFlush( xInfo.display );
}

/*
Event loop for the program
*/
void eventLoop( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	int screen = xInfo.screen;
	XEvent event;
	while( true )
	{
		if ( XPending( display ) > 0 )
		{
			XNextEvent( display, &event );
			switch ( event.type )
			{
				case KeyPress:
					handleKeyPress( xInfo, event );
					break;
				case ConfigureNotify:
					handleResize( xInfo, event );
					break;
			}
		}
		if ( endGame )
		{
			endTimer ++;
		}
		if ( endTimer == 150 )
		{
			error( "Hope you had fun" );
		}
		if ( !endGame && playable == 1 )
		{
			holdingKeys();
			handleAnimation( xInfo );
			repaint( xInfo );
			checkCollisions( xInfo );
		}
		usleep ( 1000000 / FPS );
	}
}

