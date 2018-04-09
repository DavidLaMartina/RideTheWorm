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

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
using std::string;

#include <vector>
using std::vector;

string validateWordString(int);             // Re-prompts for string entry until the
                                            // string is only letters and equal to or less
                                            // than specified length

string validateWordsString(int);            // Re-prompts for string entry until the string is only
                                            // letters and SPACES and equal to or less than
                                            // specified length - allows for multiple words

string validateStringLength(int);           // Re-prompts for string entry until the string is within
                                            // the specified length parameters.

bool validateIntString(string, int&);       // validation function that converts 
                                            // valid strings to integers

bool validateIntRangeInc(int, int, int);    // validates whether or not an integer is within
                                            // a given range of integers, inclusive

bool validateIntRangeExc(int, int, int);    // validates whether or not an integer is within
                                            // a given range of integers, exclusive

bool validateNumEntryInc(string, int&, int, int);   // Validates whether or not a string entry
                                                    // represents an integer within a given range
                                                    // and modifies a placeholder integer value
                                                    // by reference.

int returnValidInt(int, int);               // Re-prompts user for a valid integer entry between
                                            // upper and lower bounds until they have provided
                                            // a valid entry; returns that valid integer

double returnValidDouble(double, double, int);   // Re-prompts user for valid double entry between
                                                // upper and lower bounds and within a character
                                                // limit until they have provided a valid entry;
                                                // returns that valid double

int generateRandInt(int, int);              // generates a random integer within a given range
                                            // Faster than generateRandomInt. Requires seeding
                                            // and inclusiong of <ctime> in main

int generateRandomInt(int, int);            // generates a random integer with a given range

int generateProbInt(vector<int>);           // takes an array of relative probabilities that
                                            // correspond to index values and returns an integer
                                            // corresponding to one of those index values

void pauseSec(int);                         // pauses the computer, mainly to avoid duplicate
                                            // "random" integer generation

string convertIntToString(int);             // converts integers into strings

string convertDoubleToString(double);       // converts doubles to strings

int convertStringToInt(string);             // converts strings to integers

double convertStringToDouble(string);       // converts strings to doubles

#endif
