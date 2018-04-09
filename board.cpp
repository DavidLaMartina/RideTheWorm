/**************************************************************************************************
 * Program: Final Project: Ride the Worm Board class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Board class, which is used to create
 * the game board for the Ride the Worm game.
 *************************************************************************************************/

#include "board.hpp"
#include "space.hpp"
#include "sand.hpp"
#include "sietch.hpp"
#include "bush.hpp"
#include "worm.hpp"

#include "utility.hpp"

#include <iostream>
using std::cout;
using std::endl;

/**************************************************************************************************
 * Board::Board: Constructor initializes numRows, numCols, wormDensity and maxWormSize to allow
 * for easy manipulation of game variables
 *************************************************************************************************/
Board::Board(int numRows, int numCols, int wormDensity, int maxWormSize):
    numRows(numRows), numCols(numCols), wormDensity(wormDensity), maxWormSize(maxWormSize)
{
    // Establish upper left corner Sand space
    upperLeft = new Sand(nullptr, nullptr, nullptr, nullptr);

    // Create first column of Sand spaces (1st space of every row)
    Space* traverseColumn = upperLeft;

    for ( int i = 0; i < numRows - 1; i++ )
    {
        // Use a temporary Space pointer to create new Sand space, point north to traverseColumn
        Space* tempSand = new Sand(traverseColumn, nullptr, nullptr, nullptr);

        // Point south of traverseColumn to the new Sand space
        traverseColumn->south = tempSand;

        // Set traverseColumn to the new Sand space
        traverseColumn = tempSand;
    }

    // Create every row, starting from its respective Sand space in the first column
    traverseColumn = upperLeft;

    for ( int i = 0; i < numRows; i++ )
    {
        Space* traverseRow = traverseColumn;

        for ( int i = 0; i < numCols - 1; i++ )
        {
            // Use a temporary Space pointer to create new Sand space, point west to traverseRow
            Space* tempSand = new Sand(nullptr, nullptr, nullptr, traverseRow);

            // Point east of traverseRow to the new Sand space
            traverseRow->east = tempSand;

            // Set traverseRow to the new Sand space
            traverseRow = tempSand;
        }
        // Set traverseColumn to the next Space down, so traverseRow can start at the next row
        traverseColumn = traverseColumn->south;
    }

    // Now that all rows are in place and connected to the left-most column, connect rows via
    // north and south pointers
    traverseColumn = upperLeft;
    
    for ( int i = 0; i < numRows - 1; i++ )
    {
        Space* traverseRowTop = traverseColumn;
        Space* traverseRowBottom = traverseColumn->south;

        for ( int i = 0; i < numCols - 1; i++ )
        {
            // Move traverseRowTop and traverseRowBottom one space to the right (each)
            traverseRowTop = traverseRowTop->east;
            traverseRowBottom = traverseRowBottom->east;

            // Set the pointers' respective spaces' south and north pointers to each other
            traverseRowTop->south = traverseRowBottom;
            traverseRowBottom->north = traverseRowTop;
        }
        // Move traverseColumn down one space
        traverseColumn = traverseColumn->south;
    }

    // Set wormSize according to wormDensity
    wormsSize = ( numRows / wormDensity ) * ( numCols / wormDensity );

    // Allocate worms pointer to array of Space pointers
    worms = new Space*[wormsSize];

    // Places sietches, bushes and worms; grow worms
    placeSietches();
    placeBushes();
    placeWorms();
    growWorms();
}

/**************************************************************************************************
 * Board::spaceSwap: Generic function for swapping out one space for another
 *************************************************************************************************/
void Board::spaceSwap(Space* oldSpace, Space* newSpace)
{
    // Change out north, east, south and west pointers for new space and 4 surrounding spaces.
    // Account for corners and sides with logic that if a pointer was null before, it will remain
    //      null after the swap.
    //
    // ***Assume newly created Space object is instantiated with all 4 pointers set to nullptr
    if ( oldSpace->north != nullptr )
    {
        (oldSpace->north)->south = newSpace;
        newSpace->north = oldSpace->north;
    }
    if ( oldSpace->east != nullptr )
    {
        (oldSpace->east)->west = newSpace;
        newSpace->east = oldSpace->east;
    }
    if ( oldSpace->south != nullptr )
    {
        (oldSpace->south)->north = newSpace;
        newSpace->south = oldSpace->south;
    }
    if ( oldSpace->west != nullptr )
    {
        (oldSpace->west)->east = newSpace;
        newSpace->west = oldSpace->west;
    }
    // If upperLeft pointed to oldSpace, re-point it to newSpace
    if ( upperLeft == oldSpace )
    {
        upperLeft = newSpace;
    }
    // If player pointed to oldSpace, re-point it to newSpace
    if ( player == oldSpace )
    {
        player = newSpace;
    }
    // Now that pointers are in place for new Space and surrounding spaces, delete the old Space
    delete oldSpace;
}

/**************************************************************************************************
 * Board::sandSwap: Swaps existing old space for existing new space, puts new Sand space in old
 * space's place. Returns pointer to new Sand space
 *************************************************************************************************/
Space* Board::sandSwap(Space* oldSpace, Space* newSpace)
{
    // Put new Sand space "on top of" oldSpace, pointing surrounding directional pointers to that new
    // Sand space but keeping oldSpace's directional pointers pointed to surrounding spaces (for now)
    Space* newSand = new Sand(nullptr, nullptr, nullptr, nullptr);

    if ( oldSpace->north != nullptr )
    {
        (oldSpace->north)->south = newSand;
        newSand->north = oldSpace->north;
    }
    if ( oldSpace->east != nullptr )
    {
        (oldSpace->east)->west = newSand;
        newSand->east = oldSpace->east;
    }
    if ( oldSpace->south != nullptr )
    {
        (oldSpace->south)->north = newSand;
        newSand->south = oldSpace->south;
    }
    if ( oldSpace->west != nullptr )
    {
        (oldSpace->west)->east = newSand;
        newSand->west = oldSpace->west;
    }
    // If upperLeft pointed to oldSpace, re-point it to the new Sand space
    if ( upperLeft == oldSpace )
    {
        upperLeft = newSand;
    }
    // If player pointed to oldSpace, re-point it to the new Sand space
    if ( player == oldSpace )
    {
        player = newSand;
    }
    // Swap oldSpace for newSpace - Do so by calling spaceSwap with newSpace as the "old" space
    // and oldSpace as the "new" space. Set all oldSpace pointers to null before passing, since
    // spaceSwap assumes newSpace pointers "start" at null
    oldSpace->north = nullptr;
    oldSpace->east  = nullptr;
    oldSpace->south = nullptr;
    oldSpace->west  = nullptr;

    spaceSwap( newSpace, oldSpace );

    return newSand;
}

/**************************************************************************************************
 * Board::goToSpace: Returns Space pointer corresponding to passed-in coordinates; prevents 
 * traversal code from having to be re-written
 *************************************************************************************************/
Space* Board::goToSpace(int row, int col)
{
    // Create pointer for traversing Board; start at upper left corner
    Space* traverseBoard = upperLeft;

    // Travel south along left-most column
    for ( int i = 1; i < row; i++ )
    {
        traverseBoard = traverseBoard->south;
    }
    // Travel east along arrived-at row
    for ( int j = 1; j < col; j++ )
    {
        traverseBoard = traverseBoard->east;
    }
    // Return current pointer
    return traverseBoard;
}

/**************************************************************************************************
 * Board::placeSietches:
 *************************************************************************************************/
void Board::placeSietches()
{
    int sietch1Row, sietch1Col, sietch2Row, sietch2Col;

    // Coordinates for starting sietch will be in upper left 16th of board
    sietch1Row = generateRandInt(2, ( numRows / 4 ));
    sietch1Col = generateRandInt(2, ( numCols / 4 ));

    // Coordinates for ending sietch will be in lower right 16th of board
    sietch2Row = generateRandInt( (numRows - (numRows / 4)), (numRows - 1) );
    sietch2Col = generateRandInt( (numCols - (numCols / 4)), (numCols - 1) );

    // Instantiate starting and ending sietches
    Space* startSietch = new Sietch(nullptr, nullptr, nullptr, nullptr, true);
    Space* endSietch   = new Sietch(nullptr, nullptr, nullptr, nullptr, false);

    // Point player pointer to startSietch and destination pointer to endSietch
    player = startSietch;
    destination = endSietch;

    // Place sietches based on coordiantes - Use coordinates to traverse board to swap-out Spaces
    spaceSwap( goToSpace(sietch1Row, sietch1Col), startSietch );
    spaceSwap( goToSpace(sietch2Row, sietch2Col), endSietch ); 

    // Set wormSwap to false for the 8 spaces surrounding each sietch
    wormSafe(startSietch);
    wormSafe(endSietch);
}

/**************************************************************************************************
* Board::wormSafe: Sets wormSwap to false for the 8 spaces surrounding a passed-in Space pointer
*************************************************************************************************/
void Board::wormSafe(Space* safeSpace)
{
    // Start on space north of safeSpace, travel clockwise around the sietch
    Space* perimeter = safeSpace->north;
    perimeter->wormSwap = false;

    perimeter = perimeter->east;
    perimeter->wormSwap = false;

    perimeter = perimeter->south;
    perimeter->wormSwap = false;
    perimeter = perimeter->south;
    perimeter->wormSwap = false;

    perimeter = perimeter->west;
    perimeter->wormSwap = false;
    perimeter = perimeter->west;
    perimeter->wormSwap = false;

    perimeter = perimeter->north;
    perimeter->wormSwap = false;
    perimeter = perimeter->north;
    perimeter->wormSwap = false;
}

/**************************************************************************************************
 * Board::placeBushes: Randomly places bushes throughout the board with given probability; bushes
 * can only be swapped with Sand spaces for which wormSwap is true
 *************************************************************************************************/
void Board::placeBushes()
{
    // Loop through board, with each space having a chance to be swapped for a bush
    for ( int i = 1; i < numRows; i++ )
    {
        for ( int j = 1; j < numCols; j++ )
        {
            if ( generateRandInt( 1, 50 ) == 25 )
            {
                // wormSwap == true condition to avoid placing bushes inside Sietch perimeter
                // (visual consideration more than practical)
                if ( goToSpace(i, j)->wormSwap )
                {
                    spaceSwap( goToSpace(i, j), new Bush(nullptr, nullptr, nullptr, nullptr) );
                }
            }
        }
    }
}

/**************************************************************************************************
 * Board::~Board: Destructor traverses entire board, deleting each Space object. Also deletes 
 * memory allocated to worms (array of Space pointers)
 *************************************************************************************************/
Board::~Board()
{
    // Set up pointer for traversing first column
    Space* traverseColumn = upperLeft;

    // Loop through rows, deleting every space except for the first, leaving first column intact
    // for traversal
    for ( int i = 0; i < numRows; i++ )
    {
        Space* traverseRow = traverseColumn->east;

        // Delete every space except first and last in row
        for ( int i = 0; i < numCols - 2; i++ )
        {
            Space* garbage = traverseRow;

            traverseRow = traverseRow->east;

            delete garbage;
        }
        // Delete last space
        delete traverseRow;

        // Move traverseColumn down one space
        traverseColumn = traverseColumn->south;
    }
    // Now delete the left-most column
    traverseColumn = upperLeft;

    for ( int i = 0; i < numRows - 1; i++ )
    {
        Space* garbage = traverseColumn;

        traverseColumn = traverseColumn->south;

        delete garbage;
    }
    delete traverseColumn;

    // Delete worms array of Space pointers
    delete[] worms;
}

/**************************************************************************************************
 * Board::printBoard: Prints board by calling print function via every Space. Takes Player object, 
 * which can be passed to each Space's print function to analyze whether or not prescience is
 * activated for that player
 **************************************************************************************************/
void Board::printBoard(Player* gamePlayer)
{
    // Traverse entire list, calling print on every space
    Space* traverseColumn = upperLeft;

    for ( int i = 0; i < numRows; i++ )
    {
        Space* traverseRow = traverseColumn;

        for ( int j = 0; j < numCols - 1; j++ )
        {
            // Print X for player; else print appropriate character by calling move function
            if ( traverseRow == player )
            {
                cout << 'X';
            }
            else
            {
                traverseRow->print(gamePlayer);
            }
            // Print empty space between spaces
            cout << ' ';
            // Move to the next space
            traverseRow = traverseRow->east;
        }
        // Print the last space in the row, again qualifying for player / not player
        if ( traverseRow == player )
        {
            cout << 'X';
        }
        else
        {
            traverseRow->print(gamePlayer);
        }
        // End line before printing the next line
        cout << endl;

        traverseColumn = traverseColumn->south;
    }
}
