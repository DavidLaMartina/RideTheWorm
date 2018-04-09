/**************************************************************************************************
 * Program: Final Project: Ride the Worm
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This is the Ride the Worm game, the Final Project for CS162. Based on the 1965
 * science fiction novel Dune by Frank Herbert, Ride the Worm requires the player - a fremen - to
 * cross the desert from one sietch (safe spot) to the next. If the player just tries to walk the 
 * whole way, though, they'll die of thirst. To make it across the desert in time, they'll have to
 * go faster by riding a sandworm!
 *************************************************************************************************/

#include "menu.hpp"
#include "utility.hpp"
#include "board.hpp"
#include "player.hpp"
#include "item.hpp"
#include "wormGame.hpp"

#include <ctime>
using std::srand;

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <unistd.h> // Needed for usleep function

int main()
{
    // Seed random number generator
    srand(time(NULL));

    // Create menu for playing game, testing worms, or quitting
    Menu playQuit(3);
    playQuit.setOption(1, "Play the game");
    playQuit.setOption(2, "Test the worms");
    playQuit.setOption(3, "Exit the program");

    // Present game and ask what player wants to do next
    ifstream inputFile;
    string outputString;

    inputFile.open("wormRules.txt");

    while ( !inputFile.eof() )
    {
        getline(inputFile, outputString);
        cout << outputString << endl;
    }

    cout << "\nWhat would you like to do? " << endl;

    int userChoice = playQuit.presentOptions();

    while( userChoice != 3 )
    {
        if ( userChoice == 1 )
        {
            // Instantiate WormGame and run series
            WormGame game;
            game.runSeries();
        }
        else if ( userChoice == 2 )
        {
            // Prompt for test parameters and run tes
            cout << "How many rows will the board have? Enter an integer between 15 and 50" << endl;
            int numRows = returnValidInt(15, 50);

            cout << "How many columns will the board have? Enter an integer between 15 and 50" << endl;
            int numCols = returnValidInt(15, 50);

            cout << "What will the worm density be? The number you enter is the size of the unit square";
            cout << "\nper worm, so a smaller number means more worms in your game board. Enter an integer";
            cout << "\nbetween 5 and 15" << endl;
            int wormDensity = returnValidInt(5, 15);

            cout << "What will be the max worm size (maximum length in number of segments)? Enter an";
            cout << "\ninteger between 5 and 15" << endl;
            int maxWormSize = returnValidInt(5, 15);

            Board arrakis(numRows, numCols, wormDensity, maxWormSize);

            cout << "For how many turns do you want to progress the simulator? Enter an integer";
            cout << "\nbetween 100 and 10,000 "; 
            int numTurns = returnValidInt( 100, 10000 );

            Player player(5, 5, 5, 5);
            player.setPrescience(true);

            arrakis.printBoard(&player);

            cout << "Press enter to begin the simulation!" << endl;
            cin.get();

            for ( int i = 0; i < numTurns; i++ )
            {
                arrakis.moveWorms();

                arrakis.printBoard(&player);

                cout << endl;

                // pause 30 milliseconds between iterations
                usleep(30000);
            }
            cout << "That concludes the simulation! Some worms do get stuck :)" << endl;
        }

        cout << "Now what would you like to do? " << endl;
        userChoice = playQuit.presentOptions();
    }

    return 0;
}
