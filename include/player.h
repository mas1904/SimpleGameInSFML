#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include <vector>
#include <cmath>

class player
{
    public:
        player();
        virtual ~player();
        void move(float, float, float);
        short move_item(short skad, short dokad);
        void set_pos(short, short, short);
        void add_item(item*, short);
        void add_item(item*);
        float getX();
        float getY();
        float getZ();
        float getRealX();
        float getRealY();
        short getKUD();
        short getKRL();
        void setKUD(short);
        void setKRL(short);
        short getHP();
        short getMP();
        short getMaxHP();
        short getMaxMP();
        float getSpeed();
        void setSpeed(float);
        void setHP(short);
        void setMP(short);
        void setMaxHP(short);
        void setMaxMP(short);
        short getC_items();
        item *getItem(short);
        short throw_item(short);
        bool update(float);
        void setZ(short);
        void setSprite(int,int);
        void setSprite(int);
        sf::Texture texture;
        sf::Sprite *sprite;
        void setC_items(short c);
    protected:
    private:
        int akcja;
        float klatka;
        float x;
        float y;
        float realX;
        float realY;
        float speed;
        float z;
        short kud;
        short krl;
        short strength;
        short power;
        short defense;
        short free_space;
        short hp;
        short mp;
        short MaxHp;
        short MaxMp;
        item eq[25];
};

#endif // PLAYER_H
