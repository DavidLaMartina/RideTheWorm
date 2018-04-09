/**************************************************************************************************
 * Program: Final Project: Ride the Worm Player class source file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This source file defines the functions of the Player class, which is used to 
 * contain the information about the player of the Ride the Worm game. A Player object has 
 * inventories of items and a bool value called prescience that is necessary to properly print the
 * game board and implement the game. Ultimately, however, most of the player manipulations of the
 * game are done via the player pointer in the Board class.
 *************************************************************************************************/

#include "player.hpp"

#include "item.hpp"

#include <iostream>
using std::cout;
using std::endl;

/**************************************************************************************************
 * Player::Player: Constructor:
 *************************************************************************************************/
Player::Player(int thirstCounter, int spice, int hooks, int thumpers):
    thirstCounter(thirstCounter), startThirst(thirstCounter), prescience(false), 
    spiceContainerSize(spice), hookContainerSize(hooks), thumperContainerSize(thumpers)
{
    setInventories();
}

/**************************************************************************************************
 * Player::setInventories: Allocates items to player's inventories
 *************************************************************************************************/
void Player::setInventories()
{
    // Set spices - all null at first, player must collect spice in the desert
    spiceContainer = new Item*[spiceContainerSize];

    for ( int i = 0; i < spiceContainerSize; i++ )
    {
        spiceContainer[i] = nullptr;
    }

    // Set hooks - player starts with full inventory of hooks
    hookContainer = new Item*[hookContainerSize];

    for ( int i = 0; i < hookContainerSize; i++ )
    {
        hookContainer[i] = new Hook;
    }

    // Set thumpers - player starts with full inventory of thumpers
    thumperContainer = new Item*[thumperContainerSize];

    for ( int i = 0; i < thumperContainerSize; i++ )
    {
        thumperContainer[i] = new Thumper;
    }
}

/**************************************************************************************************
 * Player::~Player: Destructor deletes all memory within inventory containers
 *************************************************************************************************/
Player::~Player()
{
    // Delete spiceContainer memory
    for ( int i = 0; i < spiceContainerSize; i++ )
    {
        delete spiceContainer[i];
    }
    delete[] spiceContainer;

    // Delete hookContainer memory
    for ( int i = 0; i < hookContainerSize; i++ )
    {
        delete hookContainer[i];
    }
    delete[] hookContainer;

    // Dlete thumperContainer memory
    for ( int i = 0; i < thumperContainerSize; i++ )
    {
        delete thumperContainer[i];
    }
    delete[] thumperContainer;
}

/**************************************************************************************************
 * Getters
 *************************************************************************************************/
int Player::getThirstCounter()
{
    return thirstCounter;
}

bool Player::getPrescience()
{
    return prescience;
}

int Player::getNumSpice()
{
    return countInventory(spiceContainer, spiceContainerSize);
}

int Player::getNumHooks()
{
    return countInventory(hookContainer, hookContainerSize);
}

int Player::getNumThumpers()
{
    return countInventory(thumperContainer, thumperContainerSize);
}

/**************************************************************************************************
 * Setters
 *************************************************************************************************/
void Player::setPrescience(bool prescience)
{
    this->prescience = prescience;
}

void Player::incrementThirstCounter()
{
    thirstCounter++;
}

void Player::decrementThirstCounter()
{
    thirstCounter--;
}

void Player::restoreThirstCounter()
{
    thirstCounter = startThirst;
}

/**************************************************************************************************
 * Player::isInventoryFull: Returns true if passed-in inventory is at capacity
 *************************************************************************************************/
bool Player::isInventoryFull(Item** inventory, int inventorySize)
{
    for ( int i = 0; i < inventorySize; i++ )
    {
        if ( inventory[i] == nullptr )
        {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************
 * Player::isInventoryEmpty: Returns true if all pointers in passed-in inventory are null
 *************************************************************************************************/
bool Player::isInventoryEmpty(Item** inventory, int inventorySize)
{
    for ( int i = 0; i < inventorySize; i++ )
    {
        if ( inventory[i] != nullptr )
        {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************
 * Player::countInventory: Returns number of items in a given inventory
 *************************************************************************************************/
int Player::countInventory(Item** inventory, int inventorySize)
{
    int inventoryCount = 0;

    for ( int i = 0; i < inventorySize; i++ )
    {
        if ( inventory[i] != nullptr )
        {
            inventoryCount++;
        }
    }
    return inventoryCount;
}

/**************************************************************************************************
 * Add functions for inventories - Each adds item to appropriate inventory if not full
 *************************************************************************************************/
void Player::addSpice()     // Adds ONE spice item to spice container
{
    if ( !isInventoryFull(spiceContainer, spiceContainerSize) )
    {
        for ( int i = 0; i < spiceContainerSize; i++ )
        {
            if ( spiceContainer[i] == nullptr )
            {
                spiceContainer[i] = new Spice;
                return;
            }
        }
    }
}

void Player::fillHooks()    // Completely fills hooks container
{
    if ( !isInventoryFull(hookContainer, hookContainerSize) )
    {
        for ( int i = 0; i < hookContainerSize; i++ )
        {
            if ( hookContainer[i] == nullptr )
            {
                hookContainer[i] = new Hook;
            }
        }
    }
}

void Player::fillThumpers() // Completely fills thumpers container
{
    if ( !isInventoryFull(thumperContainer, thumperContainerSize) )
    {
        for ( int i = 0; i < thumperContainerSize; i++ )
        {
            if ( thumperContainer[i] == nullptr )
            {
                thumperContainer[i] = new Thumper;
            }
        }
    }
}

/**************************************************************************************************
 * Use functions for inventories - Each subtracts item from appropriate inventory if not empty
 *************************************************************************************************/
void Player::useSpice()
{
    if ( !isInventoryEmpty(spiceContainer, spiceContainerSize) )
    {
        for ( int i = 0; i < spiceContainerSize; i++ )
        {
            if ( spiceContainer[i] != nullptr )
            {
                delete spiceContainer[i];
                spiceContainer[i] = nullptr;
                return;
            }
        }
    }
}

void Player::useHook()
{
    if ( !isInventoryEmpty(hookContainer, hookContainerSize) )
    {
        for ( int i = 0; i < hookContainerSize; i++ )
        {
            if ( hookContainer[i] != nullptr )
            {
                delete hookContainer[i];
                hookContainer[i] = nullptr;
                return;
            }
        }
    }
}

void Player::useThumper()
{

    if ( !isInventoryEmpty(thumperContainer, thumperContainerSize) )
    {
        for ( int i = 0; i < thumperContainerSize; i++ )
        {
            if ( thumperContainer[i] != nullptr )
            {
                delete thumperContainer[i];
                thumperContainer[i] = nullptr;
                return;
            }
        }
    }
}
