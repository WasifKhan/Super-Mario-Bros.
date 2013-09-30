/*
 * .cpp file for GC's
*/

// Required files
#include "include/gc.h"
#include "include/drawings.h"
#include "include/classes.h"

// Using the standard namespace
using namespace std;
 
/*
Gets the graphics context, mainly differentiated by colour
*/
GC getGC( XInfo& xInfo, string str )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	int screen = xInfo.screen;
	GC gc;
	XColor color;
	Colormap colormap;
	if ( str == "brown" )
	{
		char brown[] = "#B87333";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, brown, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "pink" )
	{
		char pink[] = "#FF96CA";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, pink, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "red" )
	{
		char red[] = "#FF2400";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, red, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "redNew" )
	{
		char red[] = "#800000";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, red, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 4, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "green" )
	{
		char green[] = "#A4B791";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, green, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}

	else if ( str == "black" )
	{
		char black[] = "#362819";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, black, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "white" )
	{
		char white[] = "#EEE9E9";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, white, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );
	}
	else if ( str == "yellow" )
	{
		char yellow[] = "#FFFF00";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, yellow, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 3, LineSolid, CapButt, JoinRound );

	}
	else if ( str == "blue" )
	{
		char blue[] = "#6666FF";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, blue, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );

	}
	else if ( str == "darkBlue" )
	{
		char blue[] = "#6666B2";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, blue, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );

	}
	else if ( str == "darkestBlue" )
	{
		char blue[] = "#323299";
		colormap = DefaultColormap( display, screen );
		gc = XCreateGC( display, window, 0, 0 );
		XParseColor( display, colormap, blue, &color );
		XAllocColor( display, colormap, &color );
		XSetForeground( display, gc, color.pixel );
		XSetBackground( display, gc, WhitePixel( display, screen ));
		XSetFillStyle( display, gc, FillSolid );
		XSetLineAttributes( display, gc, 2, LineSolid, CapButt, JoinRound );

	}
	return gc;
}

