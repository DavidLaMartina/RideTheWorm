/**************************************************************************************************
 * Program: Final Project: Ride the Worm Space class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Bush class
 *************************************************************************************************/

#ifndef BUSH_H
#define BUSH_H

#include "space.hpp"

#include "player.hpp"

class Bush : public Space
{
    private:
        Bush(Space*, Space*, Space*, Space*);

        void move(Player*);

        bool isWorm();

        void print(Player*);

        void submerge();

        void emerge();

        friend class Board;
};

#endif
