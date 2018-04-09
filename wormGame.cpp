/**************************************************************************************************
 * Program: Final Project: Ride the Worm WormGame class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header files defines the functions of the WormGame class, which is used to
 * implement the Ride the Worm game. A WormGame object has a Board object and a Player object, 
 * which are used in combination to create the game.
 *************************************************************************************************/

#include "wormGame.hpp"
#include "board.hpp"
#include "player.hpp"

#include "utility.hpp"
#include "menu.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

/**************************************************************************************************
 * WormGame::WormGame
 *************************************************************************************************/
WormGame::WormGame():
    gameBoard(nullptr), gamePlayer(nullptr), numRows(0), numCols(0), wormDensity(0), maxWormSize(0),
    isBoardRandom(false)
{}

/**************************************************************************************************
 * WormGame::~WormGame: Destructor
 *************************************************************************************************/
WormGame::~WormGame()
{}

/**************************************************************************************************
 * WormGame::newPlayer: Creates new player object with calling Player constructor with parameters
 * in this order: starting thirstCounter, spice container size, hook container size and thumper
 * container size
 *************************************************************************************************/
void WormGame::newPlayer()
{
    gamePlayer = new Player(30, 1, 10, 10);
}

/**************************************************************************************************
 * WormGame::deletePlayer: Deletes gamePlayer, so new player can be created for another run of the
 * game
 *************************************************************************************************/
void WormGame::deletePlayer()
{
    delete gamePlayer;
    gamePlayer = nullptr;
}

/**************************************************************************************************
 * WormGame::setBoard: Sets board parameters to be used for each board in the game, if user 
 * chooses the fixed option
 *************************************************************************************************/
void WormGame::setBoard()
{
    cout << "How many rows will the board have? Enter an integer between 15 and 50" << endl;
    numRows = returnValidInt(15, 50);

    cout << "How many columns will the board have? Enter an integer between 15 and 50" << endl;
    numCols = returnValidInt(15, 50);

    cout << "What will the worm density be? The number you enter is the size of the unit square";
    cout << "\nper worm, so a smaller number means more worms in your game board. Enter an integer";
    cout << "\nbetween 5 and 15" << endl;
    wormDensity = returnValidInt(5, 15);

    cout << "What will be the max worm size (maximum length in number of segments)? Enter an";
    cout << "\ninteger between 5 and 15" << endl;
    maxWormSize = returnValidInt(5, 15);
}
/**************************************************************************************************
 * WormGame::newBoard: Instantiates / creates a new game board that can be either semi-randomly
 * sized or a fixed size, based on user's menu selection
 *************************************************************************************************/
void WormGame::newBoard(bool isRandom)
{
    // If random, set parameters randomly; otherwise, board parameters will already have been set
    if ( isRandom )
    {
        numRows =       5 * generateRandInt( 3, 10 );
        numCols =       5 * generateRandInt( 3, 10 );

        // Don't allow wormDensity unit square to exceed length or width of board
        if ( numRows < numCols )
        {
            wormDensity = 5 * generateRandInt( 3, ( numRows / 5 ) );
        }
        else
        {
            wormDensity = 5 * generateRandInt( 3, ( numCols / 5 ) );
        }

        maxWormSize = generateRandInt( 5, 10 );
    }
    
    gameBoard = new Board(numRows, numCols, wormDensity, maxWormSize);
}

/**************************************************************************************************
 * WormGame::deleteBoard: Deletes game board so another may be created
 *************************************************************************************************/
void WormGame::deleteBoard()
{
    delete gameBoard;
    gameBoard = nullptr;
}

/**************************************************************************************************
 * WormGame::useSpice: Asks the player if they want to use a spice object (if available)
 *************************************************************************************************/
void WormGame::useSpice()
{
    // Create spice menu
    Menu spiceMenu(2);
    spiceMenu.setOption(1, "Yes, use spice");
    spiceMenu.setOption(2, "No, don't use spice");

    // Only allow the use of spice if prescience is not active and there is at least one spice in
    // the inventory 
    if ( gamePlayer->getNumSpice() > 0 && !gamePlayer->getPrescience() )
    {
        cout << "\nWould you like to use spice to see all of the worms?\n";
        
        if ( spiceMenu.presentOptions() == 1 )
        {
            // If they choose yes, use up a spice object, activate prescience and re-print board
            gamePlayer->useSpice();

            gamePlayer->setPrescience(true);

            gameBoard->printBoard(gamePlayer);

            printStats();
        }
    }
}

/**************************************************************************************************
 * WormGame::useThumper(): Asks the player if they want to use a thumper to emerge nearby worms
 * (if thumper is available)
 *************************************************************************************************/
bool WormGame::useThumper()
{
    // Create a thumper menu
    Menu thumperMenu(2);
    thumperMenu.setOption(1, "Yes, use a thumper");
    thumperMenu.setOption(2, "No, don't use a thumper");

    if ( gamePlayer->getNumThumpers() > 0 )
    {
        cout << "Would you like to use a thumper to emerge nearby worms?\n";

        if ( thumperMenu.presentOptions() == 1 )
        {
            // If they choose yes, use up a thumper object and call thump; if it returns true,
            // return true (player dead)
            gamePlayer->useThumper();

            if ( gameBoard->thump() )
            {
                return true;
            }
            // Print board with potentially emerged worms
            gameBoard->printBoard(gamePlayer);
        }
    }
    return false;
}

/**************************************************************************************************
 * WormGame::makeMove: Ask player in what direction they want to move
 *************************************************************************************************/
void WormGame::makeMove()
{
    // Create moveMenu
    Menu moveMenu(5);
    moveMenu.setOption(1, "Move north");
    moveMenu.setOption(2, "Move east");
    moveMenu.setOption(3, "Move south");
    moveMenu.setOption(4, "Move west");
    moveMenu.setOption(5, "Don't move");

    cout << "In what direction do you want to move?\n";

    bool moveFlag = false;

    do
    {
        int userMoveChoice = moveMenu.presentOptions(); // Stores user's movement choice

        MoveSuccess moveResult = NOMOVE;                         // Stores result of attempt to move

        switch (userMoveChoice)
        {
            case 1:
            {
                moveResult = gameBoard->movePlayer(NORTH, gamePlayer);
                break;
            }
            case 2:
            {
                moveResult = gameBoard->movePlayer(EAST, gamePlayer);
                break;
            }
            case 3:
            {
                moveResult = gameBoard->movePlayer(SOUTH, gamePlayer);
                break;
            }
            case 4:
            {
                moveResult = gameBoard->movePlayer(WEST, gamePlayer);
                break;
            }
            case 5:
            {
                moveFlag = true;
                break;
            }
        }
        // If move is no good (past edge / corner), break and keep moveFlag false
        if ( moveResult == BADMOVE )
        {
            cout << "Invalid move. Make another selection" << endl;
        }
        // If move is to a worm but no hooks, break and keep moveFlag flase
        else if ( moveResult == NOWORMMOVE )
        {
            cout << "You can't ride a worm without any hooks! Make another selection" << endl;
        }
        // If move is to a space that is not an emerged worm, make the move
        else if ( moveResult == GOODMOVE )
        {
            cout << "Successful move" << endl;
            moveFlag = true;
        }
        // If move is to an emerged worm and player has at least one hook, ride the worm
        // Print board again so player can see where they're standing before they choose their move
        else if ( moveResult == WORMMOVE )
        {
            // Print board again
            gameBoard->printBoard(gamePlayer);
            // Call rideWorm, set moveFlag to true
            rideWorm();
            moveFlag = true;
        }
    }
    while ( !moveFlag ); 
}

/**************************************************************************************************
 * WormGame::rideWorm: Lets the player "ride the worm" - pick a number of spaces to move further
 * than they would be able to walk.
 *
 * ***Note: If player attempts a move of a given number of spaces, and there are fewer than that
 * many spaces until an edge, the player will be moved to the edge
 *************************************************************************************************/
void WormGame::rideWorm()
{
    // Use a maker hook
    gamePlayer->useHook();

    int maxDistance = 10;       // maximum distance player can ride
    int rideDistance = 0;       // distance player has ridden thus far
    int spacesChoice;           // User's choice of number of spaces to move

    // Create a directional menu
    Menu dirMenu(4);
    dirMenu.setOption(1, "North");
    dirMenu.setOption(2, "East");
    dirMenu.setOption(3, "South");
    dirMenu.setOption(4, "West");

    // Allow the player to move up to maxDistance spaces in up to 2 directions

    bool rideFlag = false;

    do
    {
        cout << "You're riding a worm! What is the first direction you want to move?\n";
    
        int dirChoice = dirMenu.presentOptions();

        cout << "You have " << maxDistance - rideDistance << " spaces left to move";
        cout << "\nHow many spaces do you want to move in your first direction? ";

        spacesChoice = returnValidInt( 0, maxDistance - rideDistance );

        // Attempt the move
        if ( gameBoard->placePlayer( static_cast<Direction>(dirChoice - 1), spacesChoice ) )
        {
            rideFlag = true;

            // Print board to show player where they moved the first time
            gameBoard->printBoard(gamePlayer);
            cout << endl;
        }
        else
        {
            cout << "Invalid move - You can't ride on top of another emerged worm." << endl;
        }
    }
    while ( !rideFlag );

    // Update rideDistance based on spacesChoice & set rideFlag back to false
    rideDistance = spacesChoice;

    rideFlag = false;

    // If there are spaces left to move, prompt for the second move
    if ( rideDistance < maxDistance )
    {
        do
        {
            cout << "What is the second direction you want to move?\n";

            int dirChoice = dirMenu.presentOptions();

            cout << "You have " << maxDistance - rideDistance << " spaces left to move";
            cout << "\nHow many spaces do you want to move in your first direction? ";

            spacesChoice = returnValidInt( 0, maxDistance - rideDistance );

            // Attempt the move
            if ( gameBoard->placePlayer( static_cast<Direction>(dirChoice - 1), spacesChoice ) )
            {
                rideFlag = true;
            }
            else
            {
                cout << "Invalid move - You can't ride on top of another emerged worm." << endl;
            }
        }
        while ( !rideFlag );
    }
}

/**************************************************************************************************
 * WormGame::printStats: Prints player stats (numbers of items, thirst counter)
 *************************************************************************************************/
void WormGame::printStats()
{
    cout << "Thirst counter: " << gamePlayer->getThirstCounter() << endl;

    cout << "Prescience: ";
    if ( gamePlayer->getPrescience() )
    {
        cout << "Active" << endl;
    }
    else
    {
        cout << "Inactive" << endl;
    }

    cout << "Spice: " << gamePlayer->getNumSpice() << endl;
    
    cout << "Maker Hooks: " << gamePlayer->getNumHooks() << endl;

    cout << "Thumpers: " << gamePlayer->getNumThumpers() << endl;
}

/**************************************************************************************************
 * WormGame::runTurn
 *************************************************************************************************/
TurnResult WormGame::runTurn()
{
    int movesPerTurn = 5;

    int moveCounter = 0;

    // Continue turn while 1. there are moves remaining 2. the player has not arrived at the
    // destination sietch 3. the player's thirst counter has not run dry
    while( moveCounter < movesPerTurn && !gameBoard->hasArrived() && gamePlayer->getThirstCounter() > 0 )
    {
        // Print the current board and stats
        gameBoard->printBoard(gamePlayer);
        printStats();
        cout << "\nMoves remaining in turn: " << movesPerTurn - moveCounter << endl;

        // Allow player to use spice if they choose
        useSpice();

        // Allow player to use thumper if they choose; Player is dead if useThumper returns true
        if ( useThumper() )
        {
            cout << "You've thumped on top of a worm - You're dead! GAME OVER" << endl;
            return DEAD;
        }

        // Allow player to move
        makeMove();

        // Move worms, print board and stats
        gameBoard->moveWorms();

        // Increment moveCounter
        moveCounter++;
    }
    // Submerge any visible worms before the next turn
    gameBoard->submergeWorms();

    // Turn prescience back to false
    gamePlayer->setPrescience(false);

    // If player has arrived at the sietch, signal successful end of game. Check for this first, so
    // if player arrives at sietch in the nick of time, they still win the game.
    if ( gameBoard->hasArrived() )
    {
        return ARRIVED;
    }
    // If player's thirst counter has run dry, signal their death / unsuccessful end of game
    else if ( gamePlayer->getThirstCounter() <= 0 )
    {
        cout << "You've died of thirst! GAME OVER" << endl;
        return DEAD;
    }
    // If thirst counter not 0 and player has not arrived, continue to the next turn
    else
    {
        return CONTINUE;
    }
}

/**************************************************************************************************
 * WormGame::runGame: Runs a single game of Ride the Worm, part of a series
 *************************************************************************************************/
bool WormGame::runGame()
{
    // Instantiate new board
    newBoard(isBoardRandom);

    // Print key
    ifstream inputFile;
    string outputString;

    inputFile.open("wormKey.txt");

    while ( !inputFile.eof() )
    {
        getline(inputFile, outputString);
        cout << outputString << endl;
    }
    // Run turns until player dies or arrives
    TurnResult thisTurnResult;

    do
    {
        thisTurnResult = runTurn();

        cout << "\nThat concludes this turn. Press enter to continue.";
        cin.get();
    }
    while ( thisTurnResult == CONTINUE );

    // If player died, the game and series are over. Delete board.
    if ( thisTurnResult == DEAD )
    {
        deleteBoard();
        return false;
    }
    // If player arrived, the game is over but the series continues. Delete board.
    if ( thisTurnResult = ARRIVED )
    {
        deleteBoard();
        return true;
    }
}

/**************************************************************************************************
 * WormGame::runSeries: Sets up and runs a series of Ride the Worm games, adding to the win
 * counter for every successful game
 *************************************************************************************************/
void WormGame::runSeries()
{
    // Ask for a maximum number of games
    cout << "What is the maximum number of games you'll want to run? Pick an integer from 1 to 10 ";
    
    int maxGames = returnValidInt(1, 10);

    // Set up game board - random / chosen / fixed
    Menu chooseFix(3);
    chooseFix.setOption(1, "Random for every game");
    chooseFix.setOption(2, "Chosen and fixed");
    chooseFix.setOption(3, "Selected by the programmer and fixed (strongly recommended)");
    
    cout << "\nDo you want the game board to be random for each game, user-chosen and fixed, or";
    cout << "\nselected by the programmer and fixed?\n";

    int randFixChoice = chooseFix.presentOptions();

    switch(randFixChoice)
    {
        case 1:
        {
            isBoardRandom = true;
            break;
        }
        case 2:
        {
            setBoard();
            break;
        }
        case 3:
        {
            numRows = 30;
            numCols = 30;
            wormDensity = 6;
            maxWormSize = 10;
            break;
        }
    }

    // Create the player
    newPlayer();

    // Loop according to maxGames
    int gamesPlayed = 0;

    bool continueFlag = true;

    while( gamesPlayed < maxGames && continueFlag )
    {
        continueFlag = runGame();

        gamesPlayed++;

        if ( continueFlag )
        {
            cout << "Great job! You've won " << gamesPlayed << " games so far!" << endl;
        }
        else
        {
            cout << "\nYou successfully completed " << gamesPlayed - 1 << " games." << endl;
        }
    }

    // If this loop ends with continueFlag true, player won all maxGames games
    if ( continueFlag )
    {
        cout << "Great job! You won all " << maxGames << " games!";
    }

    cout << "\nThat concludes this series of Ride the Worm!" << endl;

    // Delete player
    deletePlayer();
}
