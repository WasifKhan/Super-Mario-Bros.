# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -o MarioGame main.cpp init.cpp error.cpp drawings.cpp gc.cpp events.cpp classes.cpp collisions.cpp PRNG.cpp -L/usr/X11R6/lib -lX11 -lstdc++ 

run: all
	@echo "Running..."
	./MarioGame
