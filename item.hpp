/**************************************************************************************************
 * Program: Final Project: Ride the Worm Item class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Item class, an abstract base class used to create an
 * inventory of items for the player in the Ride the Worm game.
 *************************************************************************************************/

#ifndef ITEM_H
#define ITEM_H

enum ItemType { SPICE, HOOK, THUMPER };

class Item
{
    public:
        virtual ItemType getType() = 0;
};

class Spice : public Item
{
    public:
        ItemType getType()
        {
            return SPICE;
        }
};

class Hook : public Item
{
    public:
        ItemType getType()
        {
            return HOOK;
        }
};

class Thumper : public Item
{
    public:
        ItemType getType()
        {
            return THUMPER;
        }
};
#endif
