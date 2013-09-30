/*
 * .cpp file is for initialization
*/

// Required files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "include/init.h"
#include "include/error.h"
#include "include/drawings.h"
#include "include/classes.h"
#include "include/collisions.h"
#include "include/events.h"
#include "include/PRNG.h"

// Using the standard namespace
using namespace std;


// Global variables
int width = 800;
int height = 600;

/*
Open a display
*/
Display* OpenDisplay()
{
	Display* display = XOpenDisplay( "" );
	if ( !display ) 
	{
		error ( "Can't open display." );
	}
	return display;
}

/*
Retrieve colours
*/
unsigned long Colour( string colour, XInfo& xInfo)
{
	if ( colour == "White" )
	{
		return XWhitePixel( xInfo.display, xInfo.screen );
	}
	else if ( colour == "Black" )
	{
		return XBlackPixel( xInfo.display, xInfo.screen );
	}
}

/*
Make a window
*/
Window makeWindow( XInfo& xInfo )
{
	unsigned long white = Colour( "White", xInfo );
	unsigned long black = Colour( "Black", xInfo );
	int borderWidth = 5;
	return XCreateSimpleWindow(	xInfo.display,
								DefaultRootWindow( xInfo.display),
								10, 10,
								width, height, borderWidth,
								black, white );
}

/*
Extra window properties
*/
void setProperties(XInfo& xInfo, int argc, char* argv[])
{
	XSetStandardProperties ( 	xInfo.display,
								xInfo.window,
								"Super Mario Brothers",
								"OW",
								None,
								argv, argc,
								None );
}

/*
Makes display visible for user
*/
void makeVisible( XInfo& xInfo )
{
	XMapRaised (xInfo.display, xInfo.window);
	XFlush ( xInfo.display );
	sleep( 2 );
}

/*
Main initializer function that initializes game
*/
void initX(int argc, char* argv[], XInfo& xInfo)
{
	// Opens display with error check
	xInfo.display = OpenDisplay();
	// Get information about display
	xInfo.screen = DefaultScreen( xInfo.display );
	// Makes a window
	xInfo.window = makeWindow( xInfo );
	// Sets basic properties for window
	setProperties( xInfo, argc, argv );
	// Gets Input types
	XSelectInput( xInfo.display, xInfo.window, ButtonPressMask | KeyPressMask | StructureNotifyMask );
	// Makes display visible for user
	makeVisible( xInfo );
	// Introduction screen
	introduction( xInfo );
	// Draws the entire scene for the Mario game
	drawScene( xInfo );
	// The starting text is displayed
	drawText( xInfo, "Press SPACE To Start", 290, 290 );
	// Initialize the collision table
	initTable();
	// Starts randomness
	startRandom();
	// Flush display
	XFlush( xInfo.display );
}

