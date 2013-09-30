/*
 * .h file for all classes
 */

#ifndef CLASSES_H
#define CLASSES_H

// Required files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

/*
XInfo structure to keep track of initial information
*/
class XInfo
{
	public:
	Display* display;
	int screen;
	Window window;
};

/*
Class to keep track of x and y posns of objects
*/
class posn {
	public:
	int x0;
	int y0;
	posn();
	posn( int a, int b );
	void increment();
	bool operator!= ( posn a ); 
	bool operator== ( posn a );
};

/*
Keeps track of all objects on map that mario can collide with
*/
class Object
{
	public:
		Object();
		Object( std::string t, int x, int y, int a, int b , bool use );
		std::string getType();
		void setType( std::string s );
		posn getTop();
		posn getBtm();
		void setTop( posn p );
		void setBtm( posn p );
		bool getUse();
		void setUse( bool b );
	private:
		std::string type;
		posn btmleft;
		posn topleft;
		bool used;
};

/* 
Class for Mario
*/
class Mario
{
	public:
		Mario();
		void paint( XInfo& xInfo );
		void newPaint( XInfo& xInfo );
		void move( XInfo& xInfo );
		void jump( XInfo& xInfo );
		void land( XInfo& xInfo );
		void boxLand( XInfo& xInfo );
		int getX();
		int getY();
		void setX( int a );
		void setY( int a );
		void setD( char c );
		char getD();
		void setMove( int i );
		int getMove();
		int bowserMovement;
		bool getJumped();
		void setJumped( bool j );
		posn getBtmRight();
		posn getTopRight();
		bool onBox;
	private:
		int x;
		int y;
		int movement;
		char direction;
		bool jumped;
};

/*
Class for Sun
*/
class Sun
{
	public:
		Sun();
		void paint( XInfo& xInfo );
		void move ( XInfo& xInfo );
		int getX();
		int getY();
	private:
		int x;
		int y;
		int direction;
};

/*
Class for Ground
*/
class Ground
{
	public:
		Ground();
		void paint( XInfo& xInfo );
		void move( XInfo& xInfo );
		int getX();
		int getY();
		int getP();
		void setP( int i );
	private:
		int x;
		int y;
		int p;
};

/*
Class for Bowser
*/
class Bowser
{
	public:
		Bowser();
		void paint( XInfo& xInfo );
		void move( XInfo& xInfo );
		bool inPosition();
	private:
		int x;
		int y;
		bool ready;
};

/*
Class for Bullets that Bowser shoots
*/
class Bullet
{
	public:
		Bullet();
		void start( XInfo& xInfo );
		void move( XInfo& xInfo );
		void paint( XInfo& xInfo );
		bool inUse;
		int tablePos;
	private:
		int x;
		int y;
};

/*
Class for Mushrooms
*/
class Mushroom
{
	public:
		Mushroom();
		int getX();
		int getY();
		void start( XInfo& xInfo );
		void move( XInfo& xInfo );
		void paint( XInfo& xInfo );
		bool inUse;
		int tablePos;
	private:
		int x;
		int y;
};

/*
Class for Shells
*/
class Shell
{
	public:
		Shell();
		int getX();
		int getY();
		void start( XInfo& xInfo );
		void move( XInfo& xInfo );
		void paint( XInfo& xInfo );
		bool inUse;
		int tablePos;
	private:
		int x;
		int y;
};

/*
Class for Stairs
*/
class Stair
{
	public:
		Stair();
		int getX();
		int getY();
		void start( XInfo& xInfo );
		void move( XInfo& xInfo );
		void paint( XInfo& xInfo );
		bool inUse;
		int tablePos;
		bool erased;
	private:
		int x;
		int y;
};

/*
Class for window
*/
class Win
{
	public:
		Win();
		void move( XInfo& xInfo );
		void paint( XInfo& xInfo );
	private:
		char colour;
};

/*
Class for random block generator
*/
class randBlock
{
	std::string block;
	posn p;
};

#endif

