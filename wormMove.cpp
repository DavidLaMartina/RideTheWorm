/**************************************************************************************************
 * Program: Final Project: Ride the Worm Board class worm movement functions
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines additional Board class member functions - those which 
 * govern the movement of "Sandworms," which are connected sequences of Worm objects.
 *************************************************************************************************/

#include "worm.hpp"
#include "space.hpp"
#include "board.hpp"

#include "utility.hpp"

/**************************************************************************************************
 * Board::placeWorms: Places worms on board according to density, sets head to true
 *************************************************************************************************/
void Board::placeWorms()
{
    int wormCount = 0;  // Counter for assigning worms array pointers to new Worms

    // Loop through sets of wormDensity rows along leftmost column
    for ( int i = 0; i < numRows / wormDensity; i ++ )
    {
        // Loop through sets of wormDensity columns along given row
        for ( int j = 0; j < numCols / wormDensity; j++ )
        {
            // Create integer variables for holding coordaintes
            int row, col;

            // Generate random coordinates; repeat if that space can't be swapped
            do
            {
                row = generateRandInt( ( i * wormDensity + 1 ), ( i + 1 ) * wormDensity );
                col = generateRandInt( ( j * wormDensity + 1 ), ( j + 1 ) * wormDensity );
            }
            while ( !(goToSpace( row, col )->wormSwap ) );

            // Once a swappable space has been found, allocate a new Worm to appropriate pointer
            // in worms array and swap it with that space

            worms[wormCount] = new Worm(nullptr, nullptr, nullptr, nullptr, true);

            spaceSwap( goToSpace( row, col ), worms[wormCount] );

            wormCount++;
        }
    }
}

/**************************************************************************************************
 * Board::growWorms: Elongates / grows worms using the pointers stored in worms array
 *************************************************************************************************/
void Board::growWorms()
{
    // Loop through entire worms array
    for ( int i = 0; i < wormsSize; i++ )
    {
        // Pointer for traversing worm
        Space* traverseWorm = worms[i];

        // For each worm, "try" maxWormSize times to grow with a given probability
        for ( int j = 0; j < maxWormSize; j++ )
        {
            // Try to grow worm with given probability and random direction
            // If worm can grow in the given direction, swap Sand for Worm segment and point
            //    previous segment's nextSegment pointer to the new segment, and point new
            //    segment's prevSegment pointer to the previous segment
            if ( generateRandInt(1, 4) >= 3 )
            {
                int growDir = generateRandInt(1, 4);

                switch (growDir)
                {
                    case 1:
                    {
                        if ( traverseWorm->north != nullptr && (traverseWorm->north)->wormSwap )
                        {
                            Space* tempWorm = new Worm(nullptr, nullptr, nullptr, nullptr, false);
                            spaceSwap( traverseWorm->north, tempWorm );
                            traverseWorm->nextSegment = tempWorm;
                            tempWorm->prevSegment = traverseWorm;
                            traverseWorm = tempWorm;
                        }
                        break;
                    }
                    case 2:
                    {
                        if ( traverseWorm->east != nullptr && (traverseWorm->east)->wormSwap )
                        {
                            Space* tempWorm = new Worm(nullptr, nullptr, nullptr, nullptr, false);
                            spaceSwap( traverseWorm->east, tempWorm );
                            traverseWorm->nextSegment = tempWorm;
                            tempWorm->prevSegment = traverseWorm;
                            traverseWorm = tempWorm;
                        }
                        break;
                    }
                    case 3:
                    {
                        if ( traverseWorm->south != nullptr && (traverseWorm->south)->wormSwap )
                        {
                            Space* tempWorm = new Worm(nullptr, nullptr, nullptr, nullptr, false);
                            spaceSwap( traverseWorm->south, tempWorm );
                            traverseWorm->nextSegment = tempWorm;
                            tempWorm->prevSegment = traverseWorm;
                            traverseWorm = tempWorm;
                        }
                        break;
                    }
                    case 4:
                    {
                        if ( traverseWorm->west != nullptr && (traverseWorm->west)->wormSwap )
                        {
                            Space* tempWorm = new Worm(nullptr, nullptr, nullptr, nullptr, false);
                            spaceSwap( traverseWorm->west, tempWorm );
                            traverseWorm->nextSegment = tempWorm;
                            tempWorm->prevSegment = traverseWorm;
                            traverseWorm = tempWorm;
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**************************************************************************************************
 * Board::moveWorms: Makes worms move after each turn
 *************************************************************************************************/
void Board::moveWorms()
{
    // Loop through all worms, conducting movement via the "head" (pointer contained in worms array)
    for ( int i = 0; i < wormsSize; i++ )
    {
        // Try to move in a random direction - move if space is not null and wormSwap is true
        // ***Also do not move onto space if it is occupied by player
        int moveDir = generateRandInt(1, 4);

        switch (moveDir)
        {
            case 1:
            {
                if ( worms[i]->north != nullptr && (worms[i]->north)->wormSwap && worms[i]->north != player )
                {
                    // Swap original worm head with Sand space north of it.
                    Space* vacatedSpace = sandSwap( worms[i], worms[i]->north );

                    // Have the rest of the worm segments "follow"
                    wormFollow( worms[i], vacatedSpace );
                }
                break;
            }
            case 2:
            {
                if ( worms[i]->east != nullptr && (worms[i]->east)->wormSwap && worms[i]->east != player )
                {
                    Space* vacatedSpace = sandSwap( worms[i], worms[i]->east );
                    wormFollow( worms[i], vacatedSpace );
                }
                break;
            }
            case 3:
            {
                if ( worms[i]->south != nullptr && (worms[i]->south)->wormSwap && worms[i]->south != player )
                {
                    Space* vacatedSpace = sandSwap( worms[i], worms[i]->south );
                    wormFollow( worms[i], vacatedSpace );
                }
                break;
            }
            case 4:
            {
                if ( worms[i]->west != nullptr && (worms[i]->west)->wormSwap && worms[i]->west != player )
                {
                    Space* vacatedSpace = sandSwap( worms[i], worms[i]->west );
                    wormFollow( worms[i], vacatedSpace );
                }
                break;
            }
        }
    }
}

/**************************************************************************************************
 * Board::wormFollow: Makes other worm segments "follow" the head as it moves; based on premise
 * that all segments following head will come to occupy spaces previously occupied by other Worm
 * objects (other segments of same worm)
 *************************************************************************************************/
void Board::wormFollow(Space* wormHead, Space* vacatedSpace)
{
    Space* traverseWorm = wormHead->nextSegment;
    Space* traverseVacant = vacatedSpace;

    while ( traverseWorm != nullptr )
    {
        traverseVacant = sandSwap( traverseWorm, traverseVacant );
        traverseWorm = traverseWorm->nextSegment;
    }
}

/**************************************************************************************************
 * Board::thump: Causes worm to emerge if within a given radius of the player. "Kills" player if 
 * standing right on top of worm when it emerges, returns true to indicate that
 *************************************************************************************************/
bool Board::thump()
{
    // If player is standing on top of worm, return true --> means player is dead
    if ( player->isWorm() )
    {
        return true;
    }
    // Call emerge on all surrounding spaces in a 5-sided square of spaces (if not null)
    Space* center = player;
    Space* travel = center;

    if ( travel->east != nullptr )
    {
        (travel->east)->emerge();
        
        if ( (travel->east)->east != nullptr )
        {
            ((travel->east)->east)->emerge();
        }
    }
    if ( travel->west != nullptr )
    {
        (travel->west)->emerge();

        if ( (travel->west)->west != nullptr )
        {
            ((travel->west)->west)->emerge();
        }
    }

    if ( center->north != nullptr )
    {
        travel = center->north;
        travel->emerge();

        if ( travel->east != nullptr )
        {
            (travel->east)->emerge();

            if ( (travel->east)->east != nullptr )
            {
                ((travel->east)->east)->emerge();
            }
        }
        if ( travel->west != nullptr )
        {
            (travel->west)->emerge();

            if ( (travel->west)->west != nullptr )
            {
                ((travel->west)->west)->emerge();
            }
        }
        if ( (center->north)->north != nullptr )
        {
            travel = (center->north)->north;
            travel->emerge();

            if ( travel->east != nullptr )
            {
                (travel->east)->emerge();

                if ( (travel->east)->east != nullptr )
                {
                    ((travel->east)->east)->emerge();
                }
            }
            if ( travel->west != nullptr )
            {
                (travel->west)->emerge();

                if ( (travel->west)->west != nullptr )
                {
                    ((travel->west)->west)->emerge();
                }
            }
        }
    }

    if ( center->south != nullptr )
    {
        travel = center->south;
        travel->emerge();

        if ( travel->east != nullptr )
        {
            (travel->east)->emerge();

            if ( (travel->east)->east != nullptr )
            {
                ((travel->east)->east)->emerge();
            }
        }
        if ( travel->west != nullptr )
        {
            (travel->west)->emerge();

            if ( (travel->west)->west != nullptr )
            {
                ((travel->west)->west)->emerge();
            }
        }
        if ( (center->south)->south != nullptr )
        {
            travel = (center->south)->south;
            travel->emerge();

            if ( travel->east != nullptr )
            {
                (travel->east)->emerge();

                if ( (travel->east)->east != nullptr )
                {
                    ((travel->east)->east)->emerge();
                }
            }
            if ( travel->west != nullptr )
            {
                (travel->west)->emerge();

                if ( (travel->west)->west != nullptr )
                {
                    ((travel->west)->west)->emerge();
                }
            }
        }
    }
    return false;
}

/**************************************************************************************************
 * Board::submergeWorms: Calls submerge via every Space pointer; will only cause action via Worm
 * spaces (function immediately returns for all other Space derived classes)
 *************************************************************************************************/
void Board::submergeWorms()
{
    // Traverse entire board, calling submerge via every space
    Space* traverseColumn = upperLeft;

    for ( int i = 0; i < numRows; i++ )
    {
        Space* traverseRow = traverseColumn;

        for ( int j = 0; j < numCols; j++ )
        {
            traverseRow->submerge();
            traverseRow = traverseRow->east;
        } 
        traverseColumn = traverseColumn->south;
    }
}
