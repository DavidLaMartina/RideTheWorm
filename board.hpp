/**************************************************************************************************
 * Program: Final Project: Ride the Worm Board class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Board class, the primary class responsible for the 
 * implementation of the Ride the Worm game. The Board class contains seveeral pointers used to 
 * create the board structure, move the player around the board and swap spaces to simulate the 
 * movement of sandworms.
 *************************************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "space.hpp"
#include "sand.hpp"
#include "sietch.hpp"
#include "bush.hpp"
#include "worm.hpp"

enum Direction { NORTH, EAST, SOUTH, WEST };

enum MoveSuccess { BADMOVE, GOODMOVE, NOWORMMOVE, WORMMOVE, NOMOVE };

class Board
{
    private:
        Space*  upperLeft;      // Points to upper-left space at all times (place holder)

        Space*  player;         // Points to space on which player "resides"

        Space*  destination;    // Points to destination sietch

        Space** worms;          // Points to array of Space pointers, which are used to point to
                                // Worm objects in order to control movement of "Sandworms"

        int     wormDensity;    // Determines size of unit square per worm

        int     maxWormSize;    // Maximum length of any given worm

        int     wormsSize;      // Size of worms array

        int     numRows;        // number of rows on the board

        int     numCols;        // number of columsn on the board

    public:
        Board(int, int, int, int);      // Constructor initializes numRows, numCols, wormDensity,
                                        // maxWormSize

        void spaceSwap(Space*, Space*); // Generic function for swapping out one space for another

        Space* sandSwap(Space*, Space*);// Swaps existing old space for existing new space, puts
                                        // new Sand space in the old space's place. Returns pointer
                                        // to the new Sand space

        Space* goToSpace(int, int);     // Returns pointer to specific space based on coordinates

        void placeSietches();           // Places 2 sietches (start and destination)

        void wormSafe(Space*);          // Sets wormSwap to false for 8 spaces surrounding space

        void placeBushes();             // Swaps Sand objects for Bush objects at random intervals

        ~Board();                       // Deletes all spaces' memory

        void printBoard(Player*);       // Prints current board

        // Worm-specific functions
        void placeWorms();              // Places worms psuedo-randomly according to wormDensity

        void growWorms();               // Grows / elongates worms after placement

        void moveWorms();               // Makes worms move after each turn

        void wormFollow(Space*, Space*);// Makes other segments "follow" the head as it moves

        bool thump();                   // Makes worm come to surface if they're submerged and within
                                        // given radius of player. Returns true if player is standing
                                        // right on top of worm when called

        void submergeWorms();           // Calls submerge via every Space pointer; will only cause 
                                        // action via Worm spaces

        // Player movement functions
        MoveSuccess movePlayer(Direction, Player*); // Move function that returns results based on
                                                    // nature and success of move

        bool placePlayer(Direction, int);   // Places player pointer at a certain spot; returns false if
                                            // that's going to be an invalid move
                                            // Intended only for use by the rideWorm function of wormGame

        bool hasArrived();              // Returns true if player and destination pointers are same
};

#endif
