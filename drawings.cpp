/*
 * .cpp file for drawings
*/

// Required files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include "include/drawings.h"
#include "include/init.h"
#include "include/gc.h"
#include "include/classes.h"
#include "include/error.h"
#include "include/events.h"

// Using the standard namespace
using namespace std;


// Global variables
extern int width;
extern int height;
extern int distanceToBowser;
extern int FPS;
extern Mario mario;
extern Sun sun;
extern Mushroom Mushrooms[];

/*
Draws the background
*/
void drawBackground( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( distanceToBowser > 2000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "blue" ), 0, 0, width, height );
	}
	else if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "darkBlue" ), 0, 0, width, height );
	}
	else
	{
		XFillRectangle( display, window, getGC( xInfo, "darkestBlue" ), 0, 0, width, height );
	}
}

/*
Draws the base line
*/
void drawBaseLine( XInfo& xInfo, posn p )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	XFillRectangle( display, window, getGC( xInfo, "brown" ), 0, height-50, width, height );
	for ( int i = 30; i < width; i+=50 )
	{
		XDrawArc( display, window, getGC( xInfo, "black" ), width-i, height-30, 10, 10, 0, 360*64 );
	}
	XDrawLine( display, window, getGC( xInfo, "red" ), 0, height-50, width, height-50 );
	XDrawLine( display, window, getGC( xInfo, "red" ), 0, height, width, height );
	for ( int i = 50; i < width; i+=50 )
	{
		XDrawLine( display, window, getGC( xInfo, "black" ), i, height-50, i, height-35 );
	}
}

/*
Draws Peach
*/
void drawPeach( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	XFillRectangle( display, window, getGC( xInfo, "pink" ), width - 280, height - 125, 50, 50 );
}

/*
Draw the baseline in BowserMode
*/
void drawGround( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	
	XFillRectangle( display, window, getGC( xInfo, "white" ), 0, height-50, width, height );
}

/*
Draws the starting objects
*/
void drawObjects( XInfo& xInfo, posn p )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
}

/*
Draws text to the screen
*/
void drawText( XInfo& xInfo, std::string s, int x, int y )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	int screen = xInfo.screen;
	GC gc = XCreateGC( display, window, 0, 0 );
	XSetForeground( display, gc, BlackPixel( display, screen ));
	XSetBackground( display, gc, WhitePixel( display, screen ));
	XFontStruct* font;
	font = XLoadQueryFont( display, "12x24" );
	XSetFont( display, gc, font->fid );
	std::string text( s );
	XDrawImageString( display, window, gc, x, y, text.c_str(), text.length() );
}

/*
Removes the start message "Press space to start"
*/
void removeStartMessage( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( distanceToBowser > 2000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "blue" ), 250, 250, 300, 100 );
	}
	else if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "darkBlue" ), 250, 250, 300, 100 );
	}
	else if ( 0 <= distanceToBowser && distanceToBowser <= 1000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "darkestBlue" ), 250, 250, 300, 100 );
	}
	else
	{
		XFillRectangle( display, window, getGC( xInfo, "black" ), 250, 250, 300, 100 );
	}
}

/*
Introduction to explain rules
*/
void introduction( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	int screen = xInfo.screen;
	int BufferSize = 10;
	XEvent event;
	KeySym key;
	char text[ BufferSize ];
	int i;
	int timer = 0;
	XFillRectangle( display, window, getGC( xInfo, "black" ), 0, 0, width, height );
	while ( true )
	{
		if ( XPending( display ) > 0 )
		{
			XNextEvent( display, &event );
			if ( event.type == KeyPress )
			{
				i = XLookupString( ( XKeyEvent* )&event, text, BufferSize, &key, NULL );
				if ( i == 1 && text[0] == 'q' )
				{
					error( "Hope you had fun!" );
				}
			}
		}
		drawText( xInfo, "Welcome to Super Mario Bros!", 50, 50 );
		if ( timer >= 50 )
		{
			drawText( xInfo, "The rules are as follows:", 50, 80 );
		}
		if ( timer >= 100 )
		{
			drawText( xInfo, "You will navigate your way around the", 80, 110 );
			drawText( xInfo, "world and try to collect points.", 80, 140 );
		}
		if ( timer >= 150 )
		{
			drawText( xInfo, "The green mushrooms give you one point", 80, 170 );
			drawText( xInfo, "and the red shells take away one point.", 80, 200 );
		}
		if ( timer >= 200 )
		{
			drawText( xInfo, "The screen will get darker the closer", 80, 230 );
			drawText( xInfo, "you get to Bowser.", 80, 260 );
		}
		if ( timer >= 250 )
		{
			drawText( xInfo, "At the end you will fight Bowser!", 80, 290 );
			drawText( xInfo, "You win the game by saving Peach", 80, 320 );
			drawText( xInfo, "who is trapped in a box.", 80, 350 );
			drawText( xInfo, "You lose the game if Bowser shoots you.", 80, 380 );
		}
		if (timer >= 300 )
		{
			drawText( xInfo, "Keys:", 50, 410 );
			drawText( xInfo, "Left/right arrow keys to move left/right", 80, 440 );
			drawText( xInfo, "Up arrow key or J to jump", 80, 470 );
			drawText( xInfo, "SPACE to pause and q to quit", 80, 500 );
		}
		if ( timer >= 350 )
		{
			drawText( xInfo, "Good Luck! The game will now begin.", 50, 530 );
		}
		XFlush( xInfo.display );
		timer ++;
		usleep( 1000000 / FPS );
		if ( timer == 450 )
		{
				break;
		}
	}
}

/*
Draws Mario - everything is relative to left foot
*/
void drawMario( XInfo& xInfo, posn p )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0, p.y0, p.x0+15, p.y0-15 ); 			// left foot
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+30, p.y0, p.x0+15, p.y0-15 );			// right foot
	XFillRectangle ( display, window, getGC( xInfo, "black" ), p.x0+10, p.y0-35, 10, 20 );			// body
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0, p.y0-25, p.x0+10, p.y0-25 );			// left arm
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+30, p.y0-25, p.x0+20, p.y0-25 );		// right arm
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+15, p.y0-30, p.x0+15, p.y0-40 );		// neck
	XDrawArc( display, window, getGC( xInfo, "black" ), p.x0+5, p.y0-60, 20, 20, 75, 360*64 );		// head
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+10, p.y0-53, p.x0+12, p.y0-55 );		// left eye
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+18, p.y0-53, p.x0+20, p.y0-55 );		// right eye
	XDrawLine( display, window, getGC( xInfo, "black" ), p.x0+12, p.y0-45, p.x0+18, p.y0-45 );			// mouth
}

/*
Draws the sky
*/
void drawTop( XInfo& xInfo, posn p )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "darkBlue" ), p.x0-25, p.y0-25, p.x0+80, p.y0+95 );
	}
	else if ( distanceToBowser <= 1000 )
	{
		XFillRectangle( display, window, getGC( xInfo, "darkestBlue" ), p.x0-25, p.y0-25, p.x0+80, p.y0+95 );
	}
	else
	{
		XFillRectangle( display, window, getGC( xInfo, "blue" ), p.x0-25, p.y0-25, p.x0+80, p.y0+95 );
	}
}

/*
Makes mushrooms/shells dissapear
*/
void disappear( XInfo& xInfo, Object ob )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( ob.getType() == "mushroom" )
	{
		if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkBlue" ), ob.getTop().x0, ob.getTop().y0, 5, 11 );
		}
			else if ( distanceToBowser <= 1000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkestBlue" ), ob.getTop().x0, ob.getTop().y0-32, 5, 11 );
		}
		else
		{
			XFillRectangle ( display, window, getGC( xInfo, "blue" ), ob.getTop().x0, ob.getTop().y0, 5, 11 );
		}
	}
}

/*
Main function that draws the entire scene
*/
void drawScene( XInfo& xInfo )
{
	posn p;
	posn Mario( 10, height - 53 );
	drawBackground( xInfo );
	drawBaseLine( xInfo, p );
	drawObjects( xInfo, p );
	drawMario( xInfo, Mario );
	sun.paint( xInfo );
	displayPoints( xInfo );
}

