#ifndef GAMEHELPER_H
#define GAMEHELPER_H

#include <SFML/Graphics.hpp>

#include "player.h"
#include "mapp.h"
#include "DrawHelper.h"
#include "MapHelper.h"

class GameHelper
{
    public:
        GameHelper();
        virtual ~GameHelper();
        void takeItem();
        void playerMove();
        int startGame();
        void build(int);
        void saveMap(string);
        int loadMap(string);
        void enterInventory();
        bool exitProgram();
        void exitMenu();
        void enterMenu();
        void mine(int);
        bool blocking(int, int);
        int enterGameMenu();
    protected:
    private:
        mapp *lmap;
        player *Player;
        DrawHelper *dh;
        MapHelper *mp;
        Recipment *recipments;

};

#endif // GAMEHELPER_H
