/*
 * .cpp file is for classes
*/

// Required files
#include <iostream>
#include "include/classes.h"
#include "include/gc.h"
#include "include/drawings.h"
#include "include/collisions.h"


// Global variables for dimentions of window
extern int width;
extern int height;
extern int runSpeed;
extern int sunSpeed;
extern int startWidth;
extern int startHeight;
extern int endWidth;
extern int endHeight;
extern Mario mario;
extern int distanceToBowser;
extern Object lstOfObjects[];
extern Stair Stairs[];

/*
Constructor for posns
*/
posn::posn()
{
	x0 = 0;
	y0 = 0;
}

/*
Constructor for posns
*/
posn::posn( int a, int b )
{
	x0 = a;
	y0 = b;
}

/*
Increment for posns
*/
void posn::increment()
{
	x0 ++;
	y0 ++;
}

/*
Overloading the != operator for posn
*/
bool posn::operator!=( posn a )
{
	return ( a.x0 != x0 || a.y0 != y0 );
}

/*
Overlaoding the == operator for posn
*/
bool posn::operator==( posn a )
{
	return ( x0 == a.x0 && y0 == a.y0 );
}

/*
Constructor for an object
*/
Object::Object()
{
	type = "None";
	topleft.x0 = 0;
	topleft.y0 = 0;
	btmleft.x0 = 0;
	btmleft.y0 = 0;
	used = false;
}

/*
Constructor for an object
*/
Object::Object( std::string t, int x, int y, int a, int b, bool use)
{
	type = t;
	posn tl( x, y );
	posn bl( a, b );
	topleft = tl;
	btmleft = bl;
	used = use;
}

/*
Setter for use field in object
*/
bool Object::getUse()
{
	return used;
}

/*
Getter for use field in object
*/
void Object::setUse( bool b )
{
	used = b;
}

/*
type getter for object
*/
std::string Object::getType()
{
	return type;
}

/*
type setter for object
*/
void Object::setType( std::string s)
{
	type = s;
}

/*
top left getter for object
*/
posn Object::getTop()
{
	return topleft;
}

/*
btm left getter for object
*/
posn Object::getBtm()
{
	return btmleft;
}

/*
top left setter for object
*/
void Object::setTop( posn p )
{
	topleft = p;
}

/*
btm left setter for object
*/
void Object::setBtm( posn p )
{
	btmleft = p;
}

/*
Constructor for Sun
*/
Sun::Sun()
{
	x = 30 + startWidth;
	y = 75 + startHeight;
	direction = sunSpeed;
}

/*
Paint function for Sun
*/
void Sun::paint( XInfo& xInfo )
{
	posn p( x, y );
	drawTop( xInfo, p );
	// Draw the arc for the sun
	XFillArc( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+startWidth, y+startHeight, 75, 75, 0, 360*64 );
	// top left/bottom right lines
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+5+startWidth, y+5+startHeight, x-5+startWidth, y-5+startHeight );
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+70+startWidth, y+70+startHeight, x+80+startWidth, y+80+startHeight );
	// top middle/bottom middle lines
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+38+startWidth, y-10+startHeight, x+38+startWidth, y-24+startHeight );
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+38+startWidth, y+85+startHeight, x+38+startWidth, y+99+startHeight );
	// middle left/middle right lines
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+80+startWidth, y+35+startHeight, x+94+startWidth, y+35+startHeight );
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x-5+startWidth, y+35+startHeight, x-19+startWidth, y+35+startHeight );
	// top right/bottom left lines
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+70+startWidth, y+5+startHeight, x+80+startWidth, y-5+startHeight );
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x+5+startWidth, y+70+startHeight, x-5+startWidth, y+80+startHeight );
}

/*
Move function for Sun
*/
void Sun::move( XInfo& xInfo )
{
	x += direction;
	if ( x > endWidth - 100 || x < 30+startWidth )
	{
		direction = -direction;
	}
}

/*
X getter for Sun
*/
int Sun::getX()
{
	return x;
}

/*
Y getter for Sun
*/
int Sun::getY()
{
	return y;
}

/*
Constructor for Mario
*/
Mario::Mario()
{
	x = 10;
	y = endHeight - 53;
	direction = 'r';
	bowserMovement = 0;
	jumped = false;
}

/*
getter for jump within mario
*/
bool Mario::getJumped()
{
	return jumped;
}

/*
setter for jump within mario
*/
void Mario::setJumped( bool j )
{
	jumped = j;
}

/*
X getter for Mario
*/
int Mario::getX()
{
	return x;
}

/*
Y getter for Mario
*/
int Mario::getY()
{
	return y;
}

/*
BtmRight getter for Mario
*/
posn Mario::getBtmRight()
{
	posn btmRight;
	btmRight.x0 = mario.getX() + 25;
	btmRight.y0 = mario.getY();
	return btmRight;
}

/*
TopRight getter for Mario
*/

posn Mario::getTopRight()
{
	posn topRight;
	topRight.x0 = mario.getX() + 25;
	topRight.y0 = mario.getY() - 25;
	return topRight;
}

/*
Direction getter for Mario
*/
char Mario::getD()
{
	return direction;
}

/*
Sets direction field
*/
void Mario::setD( char c )
{
	if ( c == 'r' )
	{
		direction = 'r';
	}
	else if ( c == 'l' )
	{
		direction = 'l';
	}
}

/*
Sets move field
*/
void Mario::setMove( int i )
{
	movement = i;
}

/*
Gets move field
*/
int Mario::getMove()
{
	return movement;
}

/*
Sets x field
*/
void Mario::setX( int a )
{
	x = a;
}

/*
Sets y field
*/
void Mario::setY( int a )
{
	y = a;
}

/*
Mario paint function
*/
void Mario::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	// Remove previous mario
	if ( jumped )
	{
		if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkBlue" ), x-65, y-80, 140, 132 );
		}
		else if ( distanceToBowser <= 1000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkestBlue" ), x-65, y-80, 140, 132 );
		}
		else
		{
			XFillRectangle ( display, window, getGC( xInfo, "blue" ), x-65, y-80, 140, 132 );
		}
		XDrawLine( display, window, getGC( xInfo, "black" ), x-5, y-15, x+15, y-15 ); 			// left foot
		XDrawLine( display, window, getGC( xInfo, "black" ), x+35, y-15, x+15, y-15 );			// right foot
		XFillRectangle ( display, window, getGC( xInfo, "black" ), x+10, y-35, 10, 20 );			// body
		if ( direction == 'r' )
		{
			XDrawLine( display, window, getGC( xInfo, "black" ), x+30, y-30, x+20, y-30 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "black" ), x+30, y-25, x+20, y-25 );		// right arm

		}
		else if ( direction == 'l' )
		{
			XDrawLine( display, window, getGC( xInfo, "black" ), x, y-25, x+10, y-25 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "black" ), x, y-30, x+10, y-30 );		// right arm
		}
		XDrawLine( display, window, getGC( xInfo, "black" ), x+15, y-30, x+15, y-40 );		// neck
		XDrawArc( display, window, getGC( xInfo, "black" ), x+5, y-60, 20, 20, 75, 360*64 );		// head
		XDrawLine( display, window, getGC( xInfo, "black" ), x+10, y-53, x+12, y-55 );		// left eye
		XDrawLine( display, window, getGC( xInfo, "black" ), x+18, y-53, x+20, y-55 );		// right eye	
		XDrawArc( display, window, getGC( xInfo, "black" ), x+12, y-48, 5, 5, 75, 360*64 );		// mouth
	}
	else
	{
		if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkBlue" ), x-65, y-143, 140, 145 );
		}
		else if ( distanceToBowser <= 1000 )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkestBlue" ), x-65, y-143, 140, 145 );
		}
		else
		{
			XFillRectangle ( display, window, getGC( xInfo, "blue" ), x-65, y-143, 140, 145 );
		}
		XDrawLine( display, window, getGC( xInfo, "black" ), x, y, x+15, y-15 ); 			// left foot
		XDrawLine( display, window, getGC( xInfo, "black" ), x+30, y, x+15, y-15 );			// right foot
		XFillRectangle ( display, window, getGC( xInfo, "black" ), x+10, y-35, 10, 20 );			// body
		if ( direction == 'r' )
		{
			XDrawLine( display, window, getGC( xInfo, "black" ), x+30, y-30, x+20, y-30 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "black" ), x+30, y-25, x+20, y-25 );		// right arm

		}
		else if ( direction == 'l' )
		{
			XDrawLine( display, window, getGC( xInfo, "black" ), x, y-25, x+10, y-25 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "black" ), x, y-30, x+10, y-30 );		// right arm
		}
		XDrawLine( display, window, getGC( xInfo, "black" ), x+15, y-30, x+15, y-40 );		// neck
		XDrawArc( display, window, getGC( xInfo, "black" ), x+5, y-60, 20, 20, 75, 360*64 );		// head
		XDrawLine( display, window, getGC( xInfo, "black" ), x+10, y-53, x+12, y-55 );		// left eye
		XDrawLine( display, window, getGC( xInfo, "black" ), x+18, y-53, x+20, y-55 );		// right eye
		XDrawLine( display, window, getGC( xInfo, "black" ), x+12, y-45, x+18, y-45 );		// mouth
	}
}

/*
Bowser paint for mario
*/
void Mario::newPaint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;

	// Remove previous mario
	if ( jumped )
	{
		XFillRectangle ( display, window, getGC( xInfo, "black" ), x-65, y-100, 140, 151 );
		XDrawLine( display, window, getGC( xInfo, "white" ), x-5, y-15, x+15, y-15 ); 			// left foot
		XDrawLine( display, window, getGC( xInfo, "white" ), x+35, y-15, x+15, y-15 );			// right foot
		XFillRectangle ( display, window, getGC( xInfo, "white" ), x+10, y-35, 10, 20 );			// body
		if ( direction == 'r' )
		{
			XDrawLine( display, window, getGC( xInfo, "white" ), x+30, y-30, x+20, y-30 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "white" ), x+30, y-25, x+20, y-25 );		// right arm
		}
		else if ( direction == 'l' )
		{
			XDrawLine( display, window, getGC( xInfo, "white" ), x, y-25, x+10, y-25 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "white" ), x, y-30, x+10, y-30 );		// right arm
		}
		XDrawLine( display, window, getGC( xInfo, "white" ), x+15, y-30, x+15, y-40 );		// neck
		XDrawArc( display, window, getGC( xInfo, "white" ), x+5, y-60, 20, 20, 75, 360*64 );		// head
		XDrawLine( display, window, getGC( xInfo, "white" ), x+10, y-53, x+12, y-55 );		// left eye
		XDrawLine( display, window, getGC( xInfo, "white" ), x+18, y-53, x+20, y-55 );		// right eye
		XDrawArc( display, window, getGC( xInfo, "white" ), x+12, y-48, 5, 5, 75, 360*64 );		// mouth
	}
	else
	{
		XFillRectangle ( display, window, getGC( xInfo, "black" ), x-65, y-146, 140, 147 );
		XDrawLine( display, window, getGC( xInfo, "white" ), x, y, x+15, y-15 ); 			// left foot
		XDrawLine( display, window, getGC( xInfo, "white" ), x+30, y, x+15, y-15 );			// right foot
		XFillRectangle ( display, window, getGC( xInfo, "white" ), x+10, y-35, 10, 20 );			// body
		if ( direction == 'r' )
		{
			XDrawLine( display, window, getGC( xInfo, "white" ), x+30, y-30, x+20, y-30 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "white" ), x+30, y-25, x+20, y-25 );		// right arm
		}
		else if ( direction == 'l' )
		{
			XDrawLine( display, window, getGC( xInfo, "white" ), x, y-25, x+10, y-25 );			// left arm
			XDrawLine( display, window, getGC( xInfo, "white" ), x, y-30, x+10, y-30 );		// right arm
		}
		XDrawLine( display, window, getGC( xInfo, "white" ), x+15, y-30, x+15, y-40 );		// neck
		XDrawArc( display, window, getGC( xInfo, "white" ), x+5, y-60, 20, 20, 75, 360*64 );		// head
		XDrawLine( display, window, getGC( xInfo, "white" ), x+10, y-53, x+12, y-55 );		// left eye
		XDrawLine( display, window, getGC( xInfo, "white" ), x+18, y-53, x+20, y-55 );		// right eye
		XDrawLine( display, window, getGC( xInfo, "white" ), x+12, y-45, x+18, y-45 );			// mouth
	}
}

/*
Mario move function
*/
void Mario::move( XInfo& xInfo )
{
	if ( mario.onBox == true )
	{
		y += 32;
		if ( direction == 'l' && x > 10 )
		{
			x -= runSpeed;
		}
		else if ( direction == 'r' )
		{
			x += runSpeed;
		}
		mario.onBox = false;
	}
	else
	{
		if ( direction == 'l' && x > 10 )
		{
			for ( int i = 0; i < 60; i ++ )
			{
				if ( Stairs[ i ].inUse && x-runSpeed < Stairs[ i ].getX()+25 && x-runSpeed > Stairs[ i ].getX()-25 )
				{
					return;
				}
			}
			x -= runSpeed;
		}
		else if ( direction == 'r' )
		{
			for ( int i = 0; i < 60; i ++ )
			{
				if ( Stairs[ i ].inUse && x+runSpeed > Stairs[ i ].getX()-25 && x+runSpeed < Stairs[ i ].getX() + 25 )
				{
					return;
				}
			}
			x += runSpeed;
		}
		if ( distanceToBowser == -1 )
		{
			bowserMovement += 25;
		}
	}
}

/*
Mario jump function
*/
void Mario::jump( XInfo& xInfo )
{
	y -= 50;
	if ( direction == 'l' && x > 35 )
	{
		x -= 25;
	}
	else if ( direction == 'r' )
	{
		x += 25;
	}
	bowserMovement += 25;
}

/*
Mario land function
*/
void Mario::land( XInfo& xInfo )
{
	if ( mario.onBox == true )
	{
		y += 32;
		mario.onBox = false;
	}
	y += 50;
	if ( direction == 'l' && x > 10 )
	{
		x -= 25;
	}
	else if ( direction == 'r' )
	{
		x += 25;
	}
	if ( distanceToBowser == -1 )
	{
		bowserMovement += 25;
	}
}

/*
Mario land on box function
*/
void Mario::boxLand( XInfo& xInfo )
{
	y += 18;
	if ( direction == 'l' && x > 10 )
	{
		x -= 25;
	}
	else if ( direction == 'r' )
	{
		x += 25;
	}
}

/*
Constructor for ground
*/
Ground::Ground()
{
	x = 0;
	y = 0;
	p = 30;
}

/*
X Getter for ground
*/
int Ground::getX()
{
	return x;
}

/*
Y Getter for ground
*/
int Ground::getY()
{
	return y;
}

/*
setter for p in ground
*/
void Ground::setP( int i )
{
	p = i;
}

/*
getter for p in ground
*/
int Ground::getP()
{
	return p;
}

/*
paint for ground
*/
void Ground::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	mario.setX( mario.getX() - 25 );
	XFillRectangle( display, window, getGC( xInfo, "brown" ), 0, height-50, width, height );
	for ( int i = getP(); i < width; i+=50 )
	{
		XDrawArc( display, window, getGC( xInfo, "black" ), width-i, height-30, 10, 10, 0, 360*64 );
	}
	XDrawLine( display, window, getGC( xInfo, "red" ), 0, height-50, width, height-50 );
	XDrawLine( display, window, getGC( xInfo, "red" ), 0, height, width, height );
	for ( int i = 50; i < width; i+=50 )
	{
		XDrawLine( display, window, getGC( xInfo, "black" ), i, height-50, i, height-35 );
	}
	if ( getP() == 30 )
	{
		setP( 5 );
	}
	else
	{
		setP( 30 );
	}
}

/*
move for ground
*/
void Ground::move( XInfo& xInfo )
{
	x += 25;
}

/*
Bowser constructor
*/
Bowser::Bowser()
{
	x = width + 30;
	y = height - 270;
}

/*
Bowser paint
*/
void Bowser::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	//head	
	XDrawArc( display, window, getGC( xInfo, "redNew" ), x+15, y-71, 50, 50, 0, 360*64 );
	//neck	
	XFillRectangle ( display, window, getGC( xInfo, "redNew" ), x+35, y-23, 15, 25 );
	//body
	XFillRectangle ( display, window, getGC( xInfo, "redNew" ), x, y, 80, 180 );
	//spikes on back
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+20, x+100, y+25 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+30, x+100, y+25 );	
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+40, x+100, y+45 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+50, x+100, y+45 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+60, x+100, y+65 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+70, x+100, y+65 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+80, x+100, y+85 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+90, x+100, y+85 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+100, x+100, y+105 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+110, x+100, y+105 );	
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+120, x+100, y+125 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+130, x+100, y+125 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+140, x+100, y+145 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+150, x+100, y+145 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+160, x+100, y+165 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+80, y+170, x+100, y+165 );
	//legs
	XFillRectangle ( display, window, getGC( xInfo, "redNew" ), x+20, y+180, 15, 40 );
	XFillRectangle ( display, window, getGC( xInfo, "redNew" ), x+50, y+180, 15, 40 );
	//arms
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x, y+70, x-15, y+75 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x, y+80, x-15, y+75 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x, y+90, x-15, y+95 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x, y+100, x-15, y+95 );
	// eyes
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+35, y-40, x+25, y-50 );
	XDrawLine( display, window, getGC( xInfo, "redNew" ), x+45, y-40, x+55, y-50 );
}

/*
Bowser move
*/
void Bowser::move( XInfo& xInfo )
{
	x -= 1;
}

/*
Checks if bowser is in position for bowsermode to start
*/
bool Bowser::inPosition()
{
	return ( x == 650 );
}

/*
Window constructor
*/
Win::Win()
{
	colour = 'w';
}

/*
Window move
*/
void Win::move( XInfo& xInfo )
{
	if ( colour == 'b' )
	{
		colour = 'w';
	}
	else
	{
		colour = 'b';
	}
}

/*
Window paint
*/
void Win::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;

	if ( colour == 'b' )
	{
		XFillRectangle ( display, window, getGC( xInfo, "black" ), 0, 0, width, height );
	}
	else
	{
		XFillRectangle ( display, window, getGC( xInfo, "white" ), 0, 0, width, height );
	}
}

/*
Bullet constructor
*/
Bullet::Bullet()
{
	x = width - 180;
	y = height - 65;
	inUse = false;
	tablePos = -1;
}

/*
Bullet start
*/
void Bullet::start( XInfo& xInfo )
{
	inUse = true;
	tablePos = addToTable( "bullet", x, y - 2, x, y + 2 );
}

/*
Bullet move
*/
void Bullet::move( XInfo& xInfo )
{
	if ( inUse == true )
	{
		x -= 25;
		posn top( x, y - 2 );
		posn btm( x, y + 2 );
		lstOfObjects [ tablePos ].setTop( top );
		lstOfObjects [ tablePos ].setBtm( btm );
	}
	if ( x < -100 )
	{
		x = width - 180;
		inUse = false;
		lstOfObjects [ tablePos ].setUse( false );
	}
}

/*
Bullet paint
*/
void Bullet::paint( XInfo& xInfo )
{
	XFillRectangle ( xInfo.display, xInfo.window, getGC( xInfo, "black" ), x-10, y-10, 40, 25 );
	XDrawLine( xInfo.display, xInfo.window, getGC( xInfo, "yellow" ), x - 10, y, x, y );
}

/*
Mushroom constructor
*/
Mushroom::Mushroom()
{
	x = width - 55;
	y = height - 30;
	inUse = false;
	tablePos = -1;
}

/*
getter for x in mushrooms
*/
int Mushroom::getX()
{
	return x;
}

/*
getter for y in mushrooms
*/
int Mushroom::getY()
{
	return y;
}

/*
Mushroom start
*/
void Mushroom::start( XInfo& xInfo )
{
	inUse = true;
	tablePos = addToTable( "mushroom", x, y - 32, x, y );
}

/*
Mushroom move
*/
void Mushroom::move( XInfo& xInfo )
{
	if ( inUse == true )
	{
		x -= 25;
		posn top( x, y - 32 );
		posn btm( x, y );
		lstOfObjects [ tablePos ].setTop( top );
		lstOfObjects [ tablePos ].setBtm( btm );
	}
	if ( x < -100 )
	{
		inUse = false;
		lstOfObjects [ tablePos ].setUse( false );
	}
}

/*
Mushroom paint
*/
void Mushroom::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		XFillArc( xInfo.display, xInfo.window, getGC( xInfo, "darkBlue" ), x+25, y-32, 13, 10, 0, 360*64 );
	}
	else if ( distanceToBowser <= 1000 )
	{
		XFillArc( xInfo.display, xInfo.window, getGC( xInfo, "darkestBlue" ), x+25, y-32, 13, 10, 0, 360*64 );
	}
	else
	{
		XFillArc( xInfo.display, xInfo.window, getGC( xInfo, "blue" ), x+25, y-32, 13, 10, 0, 360*64 );
	}
	XFillArc( xInfo.display, xInfo.window, getGC( xInfo, "green" ), x, y-32, 13, 10, 0, 360*64 );
}

/*
Shell constructor
*/
Shell::Shell()
{
	x = width - 55;
	y = height - 30;
	inUse = false;
	tablePos = -1;
}

/*
getter for x in Shell
*/
int Shell::getX()
{
	return x;
}

/*
getter for y in Shell
*/
int Shell::getY()
{
	return y;
}

/*
Shell start
*/
void Shell::start( XInfo& xInfo )
{
	inUse = true;
	tablePos = addToTable( "shell", x, y - 32, x, y );
}

/*
Shell move
*/
void Shell::move( XInfo& xInfo )
{
	if ( inUse == true )
	{
		x -= 25;
		posn top( x, y - 32 );
		posn btm( x, y );
		lstOfObjects [ tablePos ].setTop( top );
		lstOfObjects [ tablePos ].setBtm( btm );
	}
	if ( x < -100 )
	{
		inUse = false;
		lstOfObjects [ tablePos ].setUse( false );
	}
}

/*
Shell paint
*/
void Shell::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		XFillRectangle ( display, window, getGC( xInfo, "darkBlue" ), x+25, y-32, 5, 11 );
		XFillRectangle ( display, window, getGC( xInfo, "red" ), x, y-32, 5, 11 );
	}
	else if ( distanceToBowser <= 1000 )
	{
		XFillRectangle ( display, window, getGC( xInfo, "darkestBlue" ), x+25, y-32, 5, 11 );
		XFillRectangle ( display, window, getGC( xInfo, "red" ), x, y-32, 5, 11 );
	}
	else
	{
		XFillRectangle ( display, window, getGC( xInfo, "blue" ), x+25, y-32, 5, 11 );
		XFillRectangle ( display, window, getGC( xInfo, "red" ), x, y-32, 5, 11 );
	}
}

/*
Stair constructor
*/
Stair::Stair()
{
	x = width - 55;
	y = height - 30;
	inUse = false;
	tablePos = -1;
}

/*
getter for x in Shell
*/
int Stair::getX()
{
	return x;
}

/*
getter for y in Shell
*/
int Stair::getY()
{
	return y;
}

/*
Stair start
*/
void Stair::start( XInfo& xInfo )
{
	inUse = true;
	tablePos = addToTable( "stair", x, y - 50, x, y );
}

/*
Stair move
*/
void Stair::move( XInfo& xInfo )
{
	if ( inUse == true )
	{
		x -= 25;
		posn top( x, y - 50 );
		posn btm( x, y );
		lstOfObjects [ tablePos ].setTop( top );
		lstOfObjects [ tablePos ].setBtm( btm );
	}
	if ( x < -100 )
	{
		inUse = false;
		lstOfObjects [ tablePos ].setUse( false );
	}
	erased = false;
}

/*
Stair paint
*/
void Stair::paint( XInfo& xInfo )
{
	Display* display = xInfo.display;
	Window window = xInfo.window;
	if ( 1000 < distanceToBowser && distanceToBowser <= 2000 )
	{
		if ( erased == false )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkBlue" ), x+25, y-50, 30, 29 );
		}
		XFillRectangle ( display, window, getGC( xInfo, "brown" ), x, y-50, 25, 29 );
	}
	else if ( distanceToBowser <= 1000 )
	{
		if ( erased == false )
		{
			XFillRectangle ( display, window, getGC( xInfo, "darkestBlue" ), x+25, y-50, 30, 29 );
		}
		XFillRectangle ( display, window, getGC( xInfo, "brown" ), x, y-50, 25, 29 );
	}
	else
	{
		if ( erased == false )
		{
			XFillRectangle ( display, window, getGC( xInfo, "blue" ), x+25, y-50, 30, 29 );
		}
		XFillRectangle ( display, window, getGC( xInfo, "brown" ), x, y-50, 25, 29 );
	}
	erased = true;
}
