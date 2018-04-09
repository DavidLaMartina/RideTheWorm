/**************************************************************************************************
 * Program: Final Project: Ride the Worm Player class header file
 * Author: David LaMartina
 * Date: March 20, 2018
 * Description: This header file defines the Player class of the Ride the Worm game. A Player
 * object is used to store information about the Player, namely the thirst counter and inventory.
 *************************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "item.hpp"

class Player
{
    private:
        int     thirstCounter;

        int     startThirst;

        bool    prescience;

        Item**  spiceContainer;
        int     spiceContainerSize;

        Item**  hookContainer;
        int     hookContainerSize;

        Item**  thumperContainer;
        int     thumperContainerSize;

    public:
        // Constructor / initializer / destructor
        Player(int, int, int, int);

        void setInventories();
       
        ~Player();

        // Getters
        int getThirstCounter();

        bool getPrescience();

        int getNumSpice();
        int getNumHooks();
        int getNumThumpers();

        // Setters
        void setPrescience(bool);

        void incrementThirstCounter();
        void decrementThirstCounter();
        void restoreThirstCounter();

        // isEmpty & isFull, inventory counter
        bool isInventoryFull(Item**, int);
        bool isInventoryEmpty(Item**, int);

        int countInventory(Item**, int);

        // Item-adding functions
        void addSpice();
        void fillHooks();
        void fillThumpers();

        // Item-subtracting functions
        void useSpice();
        void useHook();
        void useThumper();
};

#endif
