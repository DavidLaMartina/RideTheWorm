/**************************************************************************************************
 * Program: Final Project: Ride the Worm Space class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Sietch class, the starting and ending "safe" spaces
 * where a player's maker hooks, thumpers and thirst counter are replenished
 *************************************************************************************************/

#ifndef SIETCH_H
#define SIETCH_H

#include "space.hpp"

#include "player.hpp"

class Sietch : public Space
{
    private:
        Sietch(Space*, Space*, Space*, Space*, bool);

        void move(Player*); 

        bool isWorm(); 

        void print(Player*); 

        void emerge();

        void submerge();

        friend class Board;
};

#endif
