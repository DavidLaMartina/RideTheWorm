/**************************************************************************************************
 * Project: Menu Class
 * Author: David LaMartina
 * Date: January 17, 2018
 * Description: This is a general Menu class that can be used to create, present and validate 
 * entries for numbered menus. Each Menu object has a single dyanmically allocated array of strings
 * (the menu options), as well as an integer member that stores the menu's number of options.
 *************************************************************************************************/

#include "menu.hpp"
#include "utility.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

/**************************************************************************************************
 * Menu::Menu: Default constructor, creates Menu object with zero options
 *************************************************************************************************/
Menu::Menu()
{
    menuSize = 0;
    options = new string[menuSize];
}

/**************************************************************************************************
 * Menu::Menu(int): Constructor that allocates memory to the array of options (strings) according
 * to an integer parameter
 *************************************************************************************************/
Menu::Menu(int sizeIn)
{
    menuSize = sizeIn;
    options = new string[menuSize];
}

/**************************************************************************************************
 * Menu::setOption: Reads string values into the elements of the options array, which has been set
 * to a given size by the constructor.
 *************************************************************************************************/
void Menu::setOption(int optionNum, string optionPhrase)
{
    options[optionNum - 1] = optionPhrase;
}

/**************************************************************************************************
 * Menu::printMenu: Displays menu options to user on screen
 *************************************************************************************************/
void Menu::printMenu()
{
    for (int i = 0; i < menuSize; i++)
    {
	cout << i + 1 << ". " << options[i] << endl;
    }
}

/**************************************************************************************************
 * Menu::validateEntry: Calls utility functions validateStringInt and validateIntRangeInc to 
 * validate whether or not user's entry is an integer within the range of menu options. Returns a
 * boolean value and alters the referenced integer.
 *************************************************************************************************/
bool Menu::validateEntry(string entryIn, int& intIn)
{
    // Check whether the entry is an integer AND that the user hasn't tried to enter a '+' or '-'
    // (because entering a '+' or '-' doesn't fit the context of a menu entry, and may indicate a
    // mistaken entry on the user's part)
    if ( (entryIn[0] != '+') && (entryIn[0] != '-') && (validateIntString(entryIn, intIn)) )
    {
	// Check whether the integer is within the range of menu options
	if ( (validateIntRangeInc(intIn, 1, menuSize)) )
	{
	    return true;
	}
	else
	{
	    return false;
	}
    }
    else
    {
	return false;
    }
}

/**************************************************************************************************
 * Menu::presentOptions: Calls printMenu and validateEntry to present options to user and validate
 * user's input with a single function. presentOptions takes no arguments, relying on the data
 * already gathered via the creation of Menu objects and option elements. It returns an integer
 * value that can be used to progress a program based on a user's menu selection.
 *************************************************************************************************/
int Menu::presentOptions()
{
    // Establish local storage variables
    int tempInt;
    string tempString;

    // Present user with menu options and collect input
    printMenu();
    getline(cin, tempString);

    // As long as the user's entry is invalid, keep re-prompting them for input.
    while ( !(validateEntry(tempString, tempInt)) )
    {
	cout << "That isn't one of the choices. Select from the following options." << endl;
	printMenu();
	getline(cin, tempString);
    }

    // Once the user has entered a valid selection, return that integer via the storage integer
    return tempInt; 
}

/**************************************************************************************************
 * getMenuEntry: Returns options entry - for testing purposes, not display in main.
 *************************************************************************************************/
string Menu::getMenuEntry(int entryIn)
{
    if (entryIn > 0 && entryIn <= menuSize)
    {
	return options[entryIn - 1];
    }
    else
    {
	return "That's not one of the menu options numbers.";
    }
}

/**************************************************************************************************
 * Menu::~Menu(): Destructor that de-allocates options array
 *************************************************************************************************/
Menu::~Menu()
{
    delete[] options;

    options = NULL;
}
