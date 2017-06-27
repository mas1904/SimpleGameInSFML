#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "common.h"
#include "statistic.h"

using namespace std;

class item
{
    public:
        item();
        item(sf::Sprite);
        virtual ~item();
        void set_count(short);
        void setId(short);
        void setHp(short);
        void setAD(short);
        void setDF(short);
        void setMaxHp(short);
        void setName(string);
        string getName();
        void setType(bool,bool,bool,bool,short,short,short destroyed = 0, short type = 0 );
        short getDestroyItem();
        short getId();
        short getHp();
        short getAD();
        short getDF();
        short getBuildId(int);
        bool getBuildType(int);
        void setBuild(bool[],int[]);
        short getMaxHp();
        short getCount();
        void set_pos(short, short, short);
        bool isPickable();
        bool isThrowable();
        bool isCountable();
        bool isBlockable();
        bool isBuild();
        short getType();

        void addMine(std::vector<int>*,std::vector<it_C>*);
        it_C mine(short);

        void setMineId(short);

        sf::Texture texture;
        sf::Sprite *sprite;
    protected:
    private:
        short id;
        bool build;
        short type;
        short build_id[2];
        bool build_type[2];
        string name;
        bool pickable;
        bool throwable;
        bool countable;
        bool blockable;
        short count;
        short attack;
        short defense;
        short range;
        short hp;
        short max_hp;
        short destroyed;
        vector<int> chance;
        vector<it_C> mines;
};

#endif // ITEM_H
