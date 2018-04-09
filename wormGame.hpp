/**************************************************************************************************
 * Program: Final Project: Ride the Worm WormGame class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the WormGame class, which is used to implement the Ride 
 * the Worm game. A WormGame object has a Board object and a Player object, which are used in
 * combination to create the game.
 *************************************************************************************************/

#ifndef WORMGAME_H
#define WORMGAME_H

#include "board.hpp"
#include "player.hpp"

enum TurnResult { CONTINUE, DEAD, ARRIVED };

class WormGame
{
    private:
        Board*  gameBoard;

        Player* gamePlayer;

        // Board variables to be set if user chooses fixed board variables
        int     numRows, numCols, wormDensity, maxWormSize;

        int     isBoardRandom;  // flag for whether or not board generation will be random

    public:
        WormGame();

        ~WormGame();

        void newPlayer();

        void deletePlayer();

        void setBoard();

        void newBoard(bool);

        void deleteBoard();

        void useSpice();

        bool useThumper();

        void makeMove();

        void rideWorm();

        void printStats();
        
        TurnResult runTurn();

        bool runGame();

        void runSeries();
};

#endif
