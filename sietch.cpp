/**************************************************************************************************
 * Program: Final Project: Ride the Worm Sietch class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Sietch class, a derived Space class
 * used to create the game board for Ride the Worm.
 *************************************************************************************************/

#include "space.hpp"
#include "sietch.hpp"
#include "player.hpp"

#include <iostream>
using std::cout;

/**************************************************************************************************
 * Sietch::Sietch: Constructor
 *************************************************************************************************/
Sietch::Sietch(Space* north, Space* east, Space* south, Space* west, bool hasArrived):
    Space(north, east, south, west)
{}

/**************************************************************************************************
 * Sietch::move: Restores thirst counter to startThirst, replenishes hook and thumper containers
 *************************************************************************************************/
void Sietch::move(Player* player)
{
    player->restoreThirstCounter();

    player->fillHooks();
    player->fillThumpers();
}

/**************************************************************************************************
 * Sietch::isWorm
 *************************************************************************************************/
bool Sietch::isWorm()
{
    return false;
}

/**************************************************************************************************
 * Sietch::print
 *************************************************************************************************/
void Sietch::print(Player* player)
{
    cout << 'S';
}

/**************************************************************************************************
 * Sietch::emerge
 *************************************************************************************************/
void Sietch::emerge()
{
    return;
}

/**************************************************************************************************
 * Sietch::submerge
 *************************************************************************************************/
void Sietch::submerge()
{
    return;
}
