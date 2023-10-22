##############################################################################
# Program:
#     Project 13, Asteroids
#     Brother Comeau, CS165
# Author:
#     James D. Downer
# Summary:
#     This program emulates an Asteroids game where the user has
#     a spaceship and must shoot bullets/lasers to destroy
#     oncoming asteroids to gain points. 
# Above and Beyond
#     I added color to my program.
#     I added shooting stars and normal moving stars in the background.
#     The user can press [Z] after gaining 20 points, and a shockwave will
#     be generated, wiping out all asteroids in its path.
#     The user can also press [X] to fire a continuous line of bullets.
#     The user gains points for every asteroid destroyed.
#     Every 30 points gained, the user gains a life.
##############################################################################

LFLAGS = -lglut -lGLU -lGL

##############################################################################
# Build the main game
##############################################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o moveable.o ship.o bullet.o stars.o color.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o moveable.o ship.o bullet.o stars.o color.o $(LFLAGS)

##############################################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    moveable.o     Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
##############################################################################
uiDraw.o: uiDraw.cpp uiDraw.hpp color.hpp
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.hpp
	g++ -c uiInteract.cpp

point.o: point.cpp point.hpp
	g++ -c point.cpp

driver.o: driver.cpp game.hpp
	g++ -c driver.cpp

game.o: game.cpp game.hpp uiDraw.hpp uiInteract.hpp point.hpp velocity.hpp moveable.hpp bullet.hpp stars.hpp ship.hpp color.hpp
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.hpp point.hpp
	g++ -c velocity.cpp

moveable.o: moveable.cpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp
	g++ -c moveable.cpp

ship.o: ship.cpp ship.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	g++ -c bullet.cpp

stars.o: stars.cpp stars.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	g++ -c stars.cpp

color.o: color.cpp color.hpp
	g++ -c color.cpp

##############################################################################
# General rules
##############################################################################
clean:
	rm a.out *.o
