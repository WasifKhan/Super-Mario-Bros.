/*
 * .cpp file for error messages
*/

// Required files
#include "include/error.h"
#include <cstdlib>

// Using the standard namespace
using namespace std;


/*
Function that prints error messages and exits
*/
void error( string str )
{
	cout << str << endl;
	exit(0);
}

