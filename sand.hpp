/**************************************************************************************************
 * Program: Final Project: Ride the Worm Sand class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Sand class, a Space class derived object. Sand is the
 * most prevalent type of Space object in the Ride the Worm game. When a player moves onto a Sand
 * class object / container, there is always a chance they will have a Spice object added to their
 * inventory (assuming there is room).
 *************************************************************************************************/

#ifndef SAND_H
#define SAND_H

#include "space.hpp"
#include "player.hpp"

class Sand : public Space
{
    private:
        Sand(Space*, Space*, Space*, Space*);   // Constructor sets Space pointers and has chance
                                                // of adjusting spice to true

        void move(Player*);     // If spice is true, puts Spice object into player's inventory.
                                // Decrements player's thirst counter

        bool isWorm();          // Returns true if worm (therefore returns false for all Sand obj)

        void print(Player*);    // Prints character representing Sand

        void emerge();

        void submerge();

        friend class Board;
};

#endif
