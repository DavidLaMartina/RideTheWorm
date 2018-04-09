/**************************************************************************************************
 * Program: Final Project: Ride the Worm Worm class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Worm class
 *************************************************************************************************/

#ifndef WORM_H
#define WORM_H

#include "space.hpp"

class Worm : public Space
{
    private: 
        bool head;              // If true, object is head segment of worm
        
        Worm(Space*, Space*, Space*, Space*, bool);

        void move(Player*);     // 

        bool isWorm();          // 

        void print(Player*);    // 

        void emerge();

        void submerge();

        friend class Board;
};

#endif
