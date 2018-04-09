/**************************************************************************************************
 * Project: Menu Class
 * Author: David LaMartina
 * Date: January 17, 2018
 * Description: This is a general Menu class that can be used to create, present and validate 
 * entries for numbered menus. Each Menu object has a single dyanmically allocated array of strings
 * (the menu options), as well as an integer member that stores the menu's number of options.
 *************************************************************************************************/

#ifndef MENU_H
#define MENU_H

#include <string>

using std::string;

class Menu
{
    private:
	string* options;	// pointer to dynamically allocated array of strings (menu options)
	int menuSize;		// number of options in the menu
    
    public:
	Menu();				    // default constructor for menu option with zero items
	Menu(int);			    // constructor that takes menu size int and allocates memory
	void setOption(int, string);	    // reads values into options array
	void printMenu();		    // prints menu of options to screen
	bool validateEntry(string, int&);   // validates strings as menu entries
	int presentOptions();		    // Calls printMenu and validateEntry to present options
					    // and validate input with a single function
	string getMenuEntry(int);	    // returns specific option entry (for testing)
	~Menu();			    // destructor that frees allocated memory
};

#endif
