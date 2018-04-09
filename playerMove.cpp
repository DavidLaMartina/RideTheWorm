/**************************************************************************************************
 * Program: Final Project: Ride the Worm Board class player movement functions
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the specific Board class functions responsible for moving
 * the "player" (the pointer that points to a given space, representing the space the player is 
 * "occupying."
 *************************************************************************************************/

#include "worm.hpp"
#include "space.hpp"
#include "board.hpp"

#include "utility.hpp"

/**************************************************************************************************
 * Board::movePlayer: Moves player one space according to passed-in direction
 *************************************************************************************************/
MoveSuccess Board::movePlayer(Direction moveDir, Player* gamePlayer)
{
    if ( moveDir == NORTH )
    {
        // Check that space isn't null (edge / corner cases)
        if ( player->north != nullptr )
        {
            // Check whether emerged worm is there
            if ( (player->north)->isWorm() && !(player->north)->submerged )
            {
                // Check whether player has a maker hook
                if ( (gamePlayer->getNumHooks() > 0 ) )
                {
                    // If so, move onto the worm and return appropriately
                    player = player->north;

                    player->move(gamePlayer);

                    return WORMMOVE;
                }
                // If not, return NOWORMMOVE
                else
                {
                    return NOWORMMOVE;
                }
            }
            // If no emerged worm, move normally
            else
            {
                player = player->north;

                player->move(gamePlayer);

                return GOODMOVE;
            }
        }
        else
        {
            return BADMOVE;
        }
    }
    else if ( moveDir == EAST )
    {
        if ( player->east != nullptr )
        {
            if ( (player->east)->isWorm() && !(player->east)->submerged )
            {
                if ( (gamePlayer->getNumHooks() > 0 ) )
                {
                    player = player->east;
                    player->move(gamePlayer);
                    return WORMMOVE;
                }
                else
                {
                    return NOWORMMOVE;
                }
            }
            else
            {
                player = player->east;
                player->move(gamePlayer);
                return GOODMOVE;
            }
        }
        else
        {
            return BADMOVE;
        }
    }
    else if ( moveDir == SOUTH )
    {
        if ( player->south != nullptr )
        {
            if ( (player->south)->isWorm() && !(player->south)->submerged )
            {
                if ( (gamePlayer->getNumHooks() > 0 ) )
                {
                    player = player->south;
                    player->move(gamePlayer);
                    return WORMMOVE;
                }
                else
                {
                    return NOWORMMOVE;
                }
            }
            else
            {
                player = player->south;
                player->move(gamePlayer);
                return GOODMOVE;
            }
        }
        else
        {
            return BADMOVE;
        }
    }
    else if ( moveDir == WEST )
    {
        if ( player->west != nullptr )
        {
            if ( (player->west)->isWorm() && !(player->west)->submerged )
            {
                if ( (gamePlayer->getNumHooks() > 0 ) )
                {
                    player = player->west;
                    player->move(gamePlayer);
                    return WORMMOVE;
                }
                else
                {
                    return NOWORMMOVE;
                }
            }
            else
            {
                player = player->west;
                player->move(gamePlayer);
                return GOODMOVE;
            }
        }
        else
        {
            return BADMOVE;
        }
    }
}

/**************************************************************************************************
 * Board::hasArrived: Returns true if player and destination pointers are the same (player has
 * arrived)
 **************************************************************************************************/
bool Board::hasArrived()
{
    if ( player == destination )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**************************************************************************************************
 * Board::placePlayer: Places player pointer at a certain spot; returns false if that's going to be
 * an invalid move. Intended only for use by the rideWorm function of wormGame
 *************************************************************************************************/
bool Board::placePlayer(Direction moveDir, int numSpaces)
{
    Space* travel = player; // Used to "scout ahead" and see if the space is valid for a move

    // Move travel to the appropriate spot
    if ( moveDir == NORTH )
    {
        for ( int i = 0; i < numSpaces; i++ )
        {
            if ( travel->north != nullptr )
            {
                travel = travel->north;
            }
        }
    }
    else if ( moveDir == EAST )
    {
        for ( int i = 0; i < numSpaces; i++ )
        {
            if ( travel->east != nullptr )
            {
                travel = travel->east;
            }
        }
    }
    else if ( moveDir == SOUTH )
    {
        for ( int i = 0; i < numSpaces; i++ )
        {
            if ( travel->south != nullptr )
            {
                travel = travel->south;
            }
        }
    }
    else if ( moveDir == WEST )
    {
        for ( int i = 0; i < numSpaces; i++ )
        {
            if ( travel->west != nullptr )
            {
                travel = travel->west;
            }
        }
    }

    // If travel has landed on any space other than an emerged worm, set player to that space,
    // return true
    if ( !( travel->isWorm() && !travel->submerged ) )
    {
        player = travel;
        
        return true;
    }

    // If travel lands on an emerged worm, return false and DO NOT conduct the move
    else
    {
        return false;
    }
}

/**************************************************************************************************
 * Board::
 *************************************************************************************************/




