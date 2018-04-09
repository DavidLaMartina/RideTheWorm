/**************************************************************************************************
 * Program: Final Project: Ride the Worm Sand class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Sand class, a derived Space class
 * used to create the game board for Ride the Worm.
 *************************************************************************************************/

#include "space.hpp"
#include "sand.hpp"
#include "player.hpp"

#include "utility.hpp"

#include <iostream>
using std::cout;

/**************************************************************************************************
 * Sand::Sand: Constructor calls Space constructor, has a certain probability of setting spice to
 * true, by default sets wormSwap to true
 *************************************************************************************************/
Sand::Sand(Space* north, Space* east, Space* south, Space* west):
    Space(north, east, south, west)
{
    // spice default is false; chance of setting to true
    if ( generateRandInt(1, 4) == 1 )
    {
        spice = true;
    }

    wormSwap = true;
}

/**************************************************************************************************
 * Sand::move: Adds spice object to player's spice inventory if there spice is true; sets spice to
 * false afterwards. Decrements thirst counter
 *************************************************************************************************/
void Sand::move(Player* player)
{
    if ( spice )
    {
        player->addSpice();
    }
    spice = false;

    player->decrementThirstCounter();
}

/**************************************************************************************************
* Sand::isWorm: Returns false because not worm segment
*************************************************************************************************/
bool Sand::isWorm()
{
    return false;
}

/**************************************************************************************************
 * Sand::print: Prints empty space to represent sand
 *************************************************************************************************/
void Sand::print(Player* player)
{
    if ( wormSwap )
    {
        cout << '+';
    }
    else
    {
        cout << ' ';
    }
}

/**************************************************************************************************
 * Sand::emerge:
 *************************************************************************************************/
void Sand::emerge()
{
    return;
}

/**************************************************************************************************
 * Sand::submerge
 *************************************************************************************************/
void Sand::submerge()
{
    return;
}
