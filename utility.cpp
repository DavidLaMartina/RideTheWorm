/**************************************************************************************************
 * Project: Reusable Utility Functions
 * Author: David LaMartina
 * Date: January 17, 2018
 * Description: These utility functions are applicable to a variety of programs. They are primarily
 * used for validating numerical entries and converting them from strings to integers, and for
 * verifying whether those integers are within a specified range. generateRandomInt also generates
 * a pseudo-random integer using the CPU clock, and calling pauseSec between calls to 
 * generateRandomInt prevents duplicate "randomized" values.
 *************************************************************************************************/

#include "utility.hpp"

#include <string>
using std::string;

#include <sstream>
using std::stringstream;
using std::ostringstream;

#include <ctime>
using std::time;

#include <cstdlib>
using std::rand;
using std::srand;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>
using std::fixed;
using std::setprecision;

/**************************************************************************************************
 * validateWordString: Re-prompts for string entry until the string is only letters (no spaces,
 * numbers or other characters). Returns that string to calling function. Meant to be used
 * following a program-specific prompt for string entry. Takes integer value for upper bounds of 
 * string length.
 *************************************************************************************************/
string validateWordString(int stringLimit)
{
    string userInput;
    bool errFlag = false;

    do
    {
        // Get string entry
        getline(cin, userInput);

        // Check whether string is appropriate length
        if ( userInput.length() <= stringLimit && userInput.length() > 0 )
        {
            errFlag = true;

            // Check whether all characters are letters
            for (unsigned i = 0; i < userInput.length(); i++)
            {
                if ( !(isalpha(userInput[i])) )
                {
                    errFlag = false;
                }
            }
        }
        else
        {
            errFlag = false;
        }

        if ( errFlag == false )
        {
            cout << "Invalid entry. Enter a word of " << stringLimit << " or fewer characters. ";
        }
    }
    while ( errFlag == false );

    return userInput;
}

/**************************************************************************************************
 * validateWordString: Re-prompts for string entry until the string is only letters or SPACES (No
 * numbres or other characters). Returns that string to calling function. Meant to be used
 * following a program-specific prompt for string entry. Takes integer value for upper bounds of 
 * string length.
 *************************************************************************************************/
string validateWordsString(int stringLimit)
{
    string userInput;
    bool errFlag = false;

    do
    {
        // Get string entry
        getline(cin, userInput);

        // Check whether string is appropriate length
        if ( userInput.length() <= stringLimit && userInput.length() > 0 )
        {
            errFlag = true;

            // Check whether all characters are letters or spaces
            for ( unsigned i = 0; i < userInput.length(); i++ )
            {
                if ( !isalpha(userInput[i]) && userInput[i] != ' ' )
                {
                    errFlag = false;
                }
            }
        }
        else
        {
            errFlag = false;
        }

        if ( errFlag == false )
        {
            cout << "Invalid entry. Enter a string of " << stringLimit << " or fewer characters. ";
        }
    }
    while ( errFlag == false );

    return userInput;
}

/**************************************************************************************************
 * validateWordString: Re-prompts for string entry until the string is within the specified length
 * parameters.
 *************************************************************************************************/
string validateStringLength(int stringLimit)
{
    string userInput;
    bool errFlag = false;

    do
    {
        // Get user string input
        getline(cin, userInput);

        // Output error message if string is empty or too long
        if ( userInput.length() > stringLimit || userInput.length() == 0 )
        {
            cout << "Invalid entry. Enter a string of " << stringLimit << " or fewer characters. ";
        }
        // Else set error flag to true so string can be returned
        else
        {
            errFlag = true;
        }
    }
    while ( errFlag == false );

    return userInput;
}

/**************************************************************************************************
 * validateIntString: This function accepts a string by value and an integer by reference. It 
 * returns a boolean value based upon whether or not the string represents an integer, and if the 
 * string does represent an integer, it also alters the referenced integer to become that integer.
 * 
 * Idea for testing characters to validate integer entries found at
 * http://www.cplusplus.com/forum/beginner/48769
 *************************************************************************************************/
bool validateIntString(string stringIn, int& intIn)
{
    // Check whether first character is a +, - or digit.
    if ((stringIn[0] == '+') || (stringIn[0] == '-') || (isdigit(stringIn[0])))
    {
        // If any subsequent character is not a digit, the strings does not
        // represent an integer.
        for (unsigned count = 1; count < stringIn.length(); count++)
        {
            if (!(isdigit(stringIn[count])))
            {
                return false;
            }
        }
        // If the first character is valid, and all of the subsequent characters are digits, then
        // the string represents an integer. Modify referenced integer and return true.
        stringstream convertString(stringIn);

        convertString >> intIn;

        return true;
    }
    // If the first character is not valid, then the string does not represent
    // an integer.
    else
    {
        return false;
    }
}

/**************************************************************************************************
 * validateIntRangeInc: Accepts an integer value to be evaluated, as well as 2 more integer values
 * to be treated as upper and lower bounds (inclusive)
 *************************************************************************************************/
bool validateIntRangeInc(int intIn, int lowerBounds, int upperBounds)
{
    if ( (intIn >= lowerBounds) && (intIn <= upperBounds) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**************************************************************************************************
 * validateIntRangeExc: Accepts an integer value to be evaluated, as well as 2 more integer values
 * to be treated as upper and lower bounds (exclusive)
 *************************************************************************************************/
bool validateIntRangeExc(int intIn, int lowerBounds, int upperBounds)
{
    if ( (intIn > lowerBounds) && (intIn < upperBounds) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**************************************************************************************************
 * validateNumEntryInc: Accepts a string, placeholder integer reference, and two ints for upper
 * and lower bounds. If the string represents an integer entry within range of specified bounds,
 * returns true and modifies placeholder integer accordingly. Returns false otherwise.
 *************************************************************************************************/
bool validateNumEntryInc(string entryIn, int& intIn, int lowBounds, int upBounds)
{
    // Check whether the entry is an integer without a negative or positive sign
    if ( (validateIntString(entryIn, intIn)) && (entryIn[0] != '+') && (entryIn[0] != '-') )
    {
        // Check whether the integer is within the range of menu options
        if ( (validateIntRangeInc(intIn, lowBounds, upBounds)) )
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
 * returnValidInt: Re-prompts user for a valid integer entry between upper and lower bounds until
 * they have provided a valid entry; returns that valid integer. Uses a boolean flag and stream
 * object to validate a string parameter as an integer.
 *
 * This function is meant to be called following an initial prompt specific to the program.
 * The function will re-prompt generically following invalid entries.
 *
 * Adapted from code presented by TA Long Le in Piazza pinned thread Topic Discussion: Utility
 * Functions on January 16, 2018
 *************************************************************************************************/
int returnValidInt(int lowBounds, int upBounds)
{
    bool errFlag = false;   // boolean variable for evaluating result; default to false
    string userInput;       // string for storing user input
    int validInt;           // return integer

    do
    {
        // Collect input
        getline(cin, userInput);

        // Create stringstream object and initialize with input string
        stringstream inputStream(userInput);

        // Check whether the string can be converted to an integer and whether there are any 
        // characters left over
        if ( inputStream >> validInt && !(inputStream >> userInput) )
        {
            // Checks whether the input was within specified bounds (parameters)
            if ( (validInt > upBounds) || (validInt < lowBounds) )
            {
                cout << "Invalid input. Enter an integer between " << lowBounds;
                cout << " and " << upBounds << ". ";
            }
            // If the input WAS within bounds, set the error flag to true
            else
            {
                errFlag = true;
            }
        }
        // Entry wasn't an integer at all
        else 
        {
            cout << "Invalid input. Enter an integer between " << lowBounds;
            cout << " and " << upBounds << ". ";
        }
    }
    while (errFlag == false);

    return validInt; 
}

/**************************************************************************************************
 * returnValidDouble: Re-prompts user for a valid double entry between upper and lower bounds and
 * of a certain number of characters until they have provided a valid entry; returns that valid
 * double. Uses a boolean flag and stream object to validate a string parameter as an integer.
 *
 * This function is meant to be called following an initial prompt specific to the program. The 
 * function will re-prompt generically following invalid entries.
 *
 * Adapted from code presented by TA Long Le in Piazza pinned thread Topic Discussion: Utility
 * Functions on January 16, 2018 
 *************************************************************************************************/
double returnValidDouble(double lowBounds, double upBounds, int digLimit)
{
    bool errFlag = false;   // boolean variable for evaluating result; default to false
    string userInput;       // string for storing user input
    double validDouble;     // return double

    do
    {
        // Collect input
        getline(cin, userInput);

        // stringstream object and initialize with input string
        stringstream inputStream(userInput);

        // Check whether the string can be converted to a double, whether there are any characters
        // left over, and whether there are too many characters
        if ( inputStream >> validDouble && !(inputStream >> userInput)
            && userInput.length() <= (digLimit + 1) )
        {
            // Check whether the input is in within specified bounds
            if ( (validDouble > upBounds) || (validDouble < lowBounds) )
            {
                cout << "Invalid input. Enter a number between " << lowBounds << " and ";
                cout << upBounds << " of " << digLimit << " or fewer digits. ";
            }
            // If the input WAS within bounds, set the error flag to true
            else
            {
                errFlag = true;
            }
        }
        // Entry wasn't a double at all
        else
        {
            cout << "Invalid input. Enter a number between " << lowBounds << " and ";
            cout << upBounds << " of " << digLimit << " or fewer digits. ";
        }
    }
    while (errFlag == false);

    return validDouble;
}

/**************************************************************************************************
 * generateRandInt: Accepts integer values for upper and lower bounds and generates a random 
 * integer within those bounds. Any program that uses generateRandInt needs to place the following
 * in the main function:
 *
 * #include<ctime>
 * srand(time(NULL));
 *
 * Format for pseudo-random number generator found at:
 * www.math.uaa.alaska.edu/~afkjm/csce211/handouts/RandomFunctions.pdf
 *************************************************************************************************/
int generateRandInt(int lowBounds, int upBounds)
{
    return (rand() %  ( (upBounds + 1) - lowBounds ) ) + lowBounds;
}

/**************************************************************************************************
 * generateRandomInt: Accepts integer values for upper and lower bounds and generates a random
 * integer within those bounds.
 *
 * Format for pseudo-random number generator found in Starting Out with C++ Early Object, 9th
 * Edition by Tony Gaddis, pages 134-136
 *************************************************************************************************/
int generateRandomInt(int lowerBounds, int upperBounds)
{
    // pause 1 second to ensure proper seeding
    pauseSec(1);

    unsigned seed = time(0);
    srand(seed);

    return (( rand() % (upperBounds - lowerBounds + 1)) + lowerBounds);
}

/**************************************************************************************************
 * pauseSec: Accepts an integer value for a number of seconds and pauses the computer for that
 * many seconds. Primarily inteded to avoid duplicate "random" integer outputs from
 * generateRandomInt, which is seeded by the current time in the computer's clock.
 *
 * Idea for pause function from https://ubuntuforums.org/archive/index.php/t-42361.html
 *************************************************************************************************/
void pauseSec(int numSec)
{
    // Establish the time at which the function will end: the current time plus the number of 
    // seconds passed in as an argument
    int waitTime = time(0) + numSec;

    // Keep an empty loop running until the current time equals the fixed end time
    while (waitTime > time(0));
}

/**************************************************************************************************
 * generateProbInt: Accepts a vector of integers representing probabilities (element / sum of 
 * elements) of various events, and returns an integer (index value + 1) corresponding to one of
 * those events.
 *************************************************************************************************/
int generateProbInt(vector<int> vec)
{
    int sum = 0;        // holds sum of all elements
    int randInt;        // holds value generated via random integer generator
    int sumLower = 0;   // lower limit for value testing
    int sumUpper = 0;   // upper limit for value testing

    // calculate sum of all elements
    for ( unsigned i = 0; i < vec.size(); i++ )
    {
        sum += vec[i];
    }

    // generate random integer between 1 and the sum of all elements
    randInt = generateRandomInt( 1, sum );

    // Test whether each vector element is between the sum of all elements up to that index value
    // (upper limit) and the sum of all elements up to the index value before (lower limit)
    for ( unsigned i = 0; i < vec.size(); i++ )
    {
        if ( i > 0 )
        {
            sumLower += vec[i-1];
        }
        sumUpper += vec[i];

        if ( ( sumLower < randInt ) && ( randInt <= sumUpper ) )
        { 
            return i + 1;
        }
    }
}

/**************************************************************************************************
 * convertIntToString: Accepts an integer and returns a converted string
 *
 * Idea for converting ints to strings from http://www.cplusplus.com/articles/D9j2Nwbp
 *************************************************************************************************/
string convertIntToString(int intIn)
{
    ostringstream converter;	// output stream for conversion

    converter << intIn;		// stream the integer characters into converter

    return converter.str();	// extract and return the string
}

/**************************************************************************************************
 * convertDoubleToString: Accepts a double value and returns a converted string
 *************************************************************************************************/
string convertDoubleToString(double doubleIn)
{
    ostringstream converter;

    converter << fixed;

    converter << setprecision(1);

    converter << doubleIn;

    return converter.str();
}

/**************************************************************************************************
 * convertStringToInt: Converts string to int - meant to be used internally, not with a user's
 * input. Returns 0 if input can't be converted.
 *************************************************************************************************/
int convertStringToInt(string stringIn)
{
    stringstream intStream(stringIn);   // stream object for conversion
    int returnInt;                      // valid integer for return
    string testString;                  // used to test whether there are any characters left

    // Check whether the string can be converted to an int and whether there are characters left
    if ( intStream >> returnInt && !(intStream >> testString) )
    {
        return returnInt;
    }
    // Return 0 if conversion fails
    else
    {
        return 0;
    }
}

/**************************************************************************************************
 * convertStringToDouble: Converts string to double  - meant to be used internally, not with a 
 * user's input. Returns 0 if input can't be converted.
 *************************************************************************************************/
double convertStringToDouble(string stringIn)
{
    stringstream doubleStream(stringIn);    // stream object for conversion
    double returnDouble;                    // valid double for return
    string testString;                      // tests whether there are any characters left

    // Check whether string can be converted to double and whether there are any characters left
    if ( doubleStream >> returnDouble && !(doubleStream >> testString) )
    {
        return returnDouble;
    }
    // Return 0 if conversion fails
    else
    {
        return 0.00;
    }
}
