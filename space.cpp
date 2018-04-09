/**************************************************************************************************
 * Program: Final Project: Ride the Worm Space class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Space class, an abstract class used
 * to create the game board for Ride the Worm.
 *************************************************************************************************/

#include "space.hpp"

/**************************************************************************************************
 * Space::Space: Constuctor sets Space pointers, spice and wormSwap
 *************************************************************************************************/
Space::Space(Space* north, Space* east, Space* south, Space* west):
    north(north), east(east), south(south), west(west), spice(false), wormSwap(false),
    nextSegment(nullptr), prevSegment(nullptr), submerged(false)
{}

/**************************************************************************************************
 * Space::Space: Virtual base class destructor put in place to allow deletion of derived Space
 * class objects through pointer to base class
 *************************************************************************************************/
Space::~Space()
{}
