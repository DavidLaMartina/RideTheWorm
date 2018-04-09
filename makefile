# Program name: Final Project: Ride the Worm
# Author: David LaMartina
# Date: March 20, 2018
# Description: This makefile compiles the source and header files for my Final Project, a
# linked-space structured game called Ride the Worm, into an executable called RideWorm. It also
# allows for the object and executable files created from the source and header files to be removed
# using the target "clean."

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -g

OBJS = space.o sand.o sietch.o bush.o worm.o board.o wormMove.o playerMove.o player.o wormGame.o menu.o utility.o main.o

SRCS = space.cpp sand.cpp sietch.cpp bush.cpp worm.cpp board.cpp wormMove.cpp playerMove.cpp player.cpp wormGame.cpp menu.cpp utility.cpp main.cpp

HEADERS = space.hpp sand.hpp sietch.hpp bush.hpp worm.hpp board.hpp player.hpp item.hpp wormGame.hpp menu.hpp utility.hpp

RideWorm: $(OBJS) $(HEADERS)
	$(CXX) $(LDFLAGS) $(OBJS) -o RideWorm

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp)

clean:
	rm $(OBJS) RideWorm
