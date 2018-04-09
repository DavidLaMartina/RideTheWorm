/**************************************************************************************************
 * Program: Final Project: Ride the Worm Worm class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Worm class, a derived Space class
 * used to create the game board for Ride the Worm.
 *************************************************************************************************/

#include "space.hpp"
#include "worm.hpp"
#include "player.hpp"

#include "utility.hpp"

#include <iostream>
using std::cout;

/**************************************************************************************************
 * Worm::Worm: Constructor sets directional pointers, head true / false and visible to false
 * ***Only constructor that sets visible to false from the get-go
 * ***Only constructor that sets submerged to true from the get-go
 *
 * ***Also has a chance of setting sand to true because Worm move function will behave as Sand
 *    move function when Worm is submerged
 *************************************************************************************************/
Worm::Worm(Space* north, Space* east, Space* south, Space* west, bool head):
    Space(north, east, south, west), head(head)
{
    submerged = true;

    // spice default is false; chance of setting to true
    if ( generateRandInt(1, 4) == 1 )
    {
        spice = true;
    }
}

/**************************************************************************************************
 * Worm::move: Acts like sand when worm is submerged
 *************************************************************************************************/
void Worm::move(Player* player)
{
    if ( submerged )
    {
        if ( spice )
        {
            player->addSpice();
        }
        spice = false;
    }
    // Decrement thirst counter whether worm is visible or not
    player->decrementThirstCounter();
}

/**************************************************************************************************
 * Worm::isWorm
 *************************************************************************************************/
bool Worm::isWorm()
{
    return true;
}

/**************************************************************************************************
 * Worm::print: Prints character based on 1. whether or not segment is visible and 2. whether or
 * not player's prescience ability is active
 *************************************************************************************************/
void Worm::print(Player* player)
{
    if ( !submerged )
    {
        if ( head )
        {
            cout << 'H';
        }
        else
        {
            cout << 'W';
        }
    }
    else
    {
        if ( player->getPrescience() )
        {
            if ( head )
            {
                cout << 'U';
            }
            else
            {
                cout << 'O';
            }
        }
        else
        {
            cout << '+';
        }
    }
}

/**************************************************************************************************
 * Worm::emerge: Makes a submerged worm segment emerge
 *************************************************************************************************/
void Worm::emerge()
{
    submerged = false;

    if ( nextSegment != nullptr )
    {
        if ( nextSegment->submerged )
        {
            nextSegment->emerge();
        }
    }
    if ( prevSegment != nullptr )
    {
        if ( prevSegment->submerged )
        {
            prevSegment->emerge();
        }
    }
}

/**************************************************************************************************
 * Worm::submerge: Makes an emerged worm segment submerge; to be called via every space at the end
 * of a turn
 *************************************************************************************************/
void Worm::submerge()
{
    submerged = true;
}
