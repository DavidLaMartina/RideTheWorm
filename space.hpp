/**************************************************************************************************
 * Program: Final Project: Ride the Worm Space class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Space class, an abstract class used to create the game
 * board for Ride the Worm.
 *************************************************************************************************/

#ifndef SPACE_H
#define SPACE_H

#include "player.hpp"

class Space
{
    protected:
        // 4 directional pointers to other spaces on board
        Space*  north;
        Space*  east;
        Space*  south;
        Space*  west;

        Space*  nextSegment;    // Used to point to subsequent spaces in a sequence
        Space*  prevSegment;    // Used to point to previous spaces in a sequence

        bool    spice;          // Flag for presence of spice

        bool    wormSwap;       // Determines whether or not worm space can be swapped

        bool    submerged;      // Determines whether space is submerged (applies only to worms)

        Space(Space*, Space*, Space*, Space*);  // Constructor sets Space pointers and by default
                                                // sets spice and wormSwap to false

        virtual ~Space();       // virtual destructor necessary for deletion of derived Space
                                // objects via base Space pointers (north, east, south and west)

        virtual void move(Player*) = 0;     // Executes action when player moves into space

        virtual bool isWorm() = 0;          // returns true if Space is Worm segment

        virtual void print(Player*) = 0;    // called when board is to be printed

        virtual void emerge() = 0;          // Makes a submerged space emerge

        virtual void submerge() = 0;        // Makes an emerged space submerge

        friend class Board;

        friend class Worm;      // Allows emerge to be called from within a Worm segment
};

#endif
