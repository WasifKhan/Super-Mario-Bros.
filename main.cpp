/*
 * This is the file that contains the main prgoram
*/

// Required Files
#include <cstdlib>
#include <string>
#include "include/init.h"
#include "include/classes.h"
#include "include/events.h"
#include "include/error.h"

// Using the standard namespace
using namespace std;

// Global variables for settings
int FPS = 45;
int runSpeed = 25;
int sunSpeed = 4;
int jumpSpeed = 15;

/*
Main function
*/
int main( int argc, char* argv[] )
{
	string arg1;
	string arg2;
	string arg3;
	string arg4;
	if ( argc > 5 )
	{
		error( "Too many command line parameters. Please refer to readme.txt" );
	}
	if ( argc > 4 )
	{
		arg4 = argv[ 4 ];
		if ( arg4.compare( "low" ) == 0 )
		{
			jumpSpeed = 5;
		}
		else if ( arg4.compare( "medium" ) == 0 )
		{
			jumpSpeed = 15;
		}
		else if ( arg4.compare( "high" ) == 0 )
		{
			jumpSpeed = 25;
		}
		else
		{
			error( "Miss use of parameters, please refer to readme.txt" );
		}
	}
	else if ( argc > 3 )
	{
		arg3 = argv[ 3 ];
		if ( arg3.compare( "low" ) == 0 )
		{
			sunSpeed = 2;
		}
		else if ( arg3.compare( "medium" ) == 0 )
		{
			sunSpeed = 4;
		}
		else if ( arg3.compare( "high" ) == 0 )
		{
			sunSpeed = 6;
		}
		else
		{
			error( "Miss use of parameters, please refer to readme.txt" );
		}
	}
	if ( argc > 2 )
	{
		arg2 = argv[ 2 ];
		if ( arg2.compare( "low" ) == 0 )
		{
			runSpeed = 10;
		}
		else if ( arg2.compare( "medium" ) == 0 )
		{
			runSpeed = 25;
		}
		else if ( arg2.compare( "high" ) == 0 )
		{
			runSpeed = 30;
		}
		else
		{
			error( "Miss use of parameters, please refer to readme.txt" );
		}
	}
	if ( argc > 1 )
	{
		arg1 = argv[ 1 ];
		if ( arg1.compare( "low" ) == 0 )
		{
			FPS = 30;
		}
		else if ( arg1.compare( "medium" ) == 0 )
		{
			FPS = 45;
		}
		else if ( arg1.compare( "high" ) == 0 )
		{
			FPS = 60;
		}
		else
		{
			error( "Miss use of parameters, please refer to readme.txt" );
		}
	}
	XInfo xInfo;
	initX( argc, argv, xInfo );
	eventLoop( xInfo );
    XCloseDisplay( xInfo.display );
}

