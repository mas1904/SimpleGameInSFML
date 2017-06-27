#include "player.h"

player::player()
{
    //ctor
    player::free_space=25;
    player::krl=0;
    player::kud=0;
    player::hp=100;
    player::mp=100;
    player::MaxHp=100;
    player::MaxMp=100;
    player::speed=2;
    akcja=0;
    for(int i=0;i<25;i++){
        eq[i].setId(0);
    }
    klatka=0;
}

player::~player()
{
    //dtor
}

float player::getX(){
    return player::x;
}

float player::getY(){
    return player::y;
}

float player::getZ(){
    return player::z;
}

float player::getRealX(){
    return player::realX;
}

float player::getRealY(){
    return player::realY;
}

short player::getC_items(){
    return player::free_space;
}

void player::setC_items(short c){
    player::free_space=c;
}
short player::getHP(){
    return player::hp;
}

short player::getMP(){
    return player::mp;
}

short player::getMaxHP(){
    return player::MaxHp;
}

short player::getMaxMP(){
    return player::MaxMp;
}

void player::setHP(short hp){
    player::hp=hp;
}

void player::setMP(short mp){
    player::mp=mp;
}

void player::setMaxHP(short hp){
    player::MaxHp=hp;
}

void player::setMaxMP(short mp){
    player::MaxMp=mp;
}

item* player::getItem(short id){
    return &player::eq[id];
}

short player::throw_item(short id){
    short idd = eq[id].getId();
    eq[id].setId(0);
    free_space++;
    return idd;
}

void player::add_item(item * new_item, short count){
    free_space--;
    for(int i=0;i<25;i++)
        if(eq[i].getId()==0){
            eq[i]=*new_item;
            eq[i].set_count(count);
            break;
        }
}

void player::add_item(item * new_item){
    free_space--;
    for(int i=0;i<25;i++)
        if(eq[i].getId()==0){
            eq[i]=*new_item;
            break;
        }
}

short player::move_item(short zz, short doz){
        item tmp = eq[zz];
        eq[zz]=eq[doz];
        eq[doz]=tmp;
}

void player::set_pos(short xx, short yy, short zz)
{
    x = xx;
    y = yy;
    z = zz;
    realX=xx;
    realY=yy;
}
void player::setKUD(short k){
    player::kud=k;
    player::krl=0;
}
void player::setKRL(short k){
    player::krl=k;
    player::kud=0;
}

void player::setZ(short zz){
    z = zz;
}

short player::getKUD(){
    return player::kud;
}
short player::getKRL(){
    return player::krl;
}

void player::setSprite(int j, int i){
    sf::IntRect r1(32+(128*j), 8+(i*128),64,128);
    sprite->setTextureRect(r1);
}

void player::setSprite(int i){
    akcja=i;
    sf::IntRect r1(32+(128*(int)klatka), 8+(i*128),64,128);
    sprite->setTextureRect(r1);
}

void player::move(float xx, float yy, float zz)
{
    if(realX==x&&realY==y){
        x += xx;
        y += yy;
        z += zz;
        kud=yy;
        krl=xx;
    }
}

bool player::update(float delta){
    if(realX!=x||realY!=y){
        delta*=speed;
        if(realX>x)
            if((realX-(delta))<x)
                realX=x;
            else{
                if(abs(x-realX)<0.01)
                    realX=x;
                else
                    realX-=delta;
            }
        else if(realY>y)
            if((realY-(delta))<y)
                realY=y;
            else{
                if(abs(y-realY)<0.01)
                    realY=y;
                else
                    realY-=delta;
            }
        else if(realX<x)
            if((realX+(delta))>x)
                realX=x;
            else{
                if(abs(x-realX)<0.01)
                    realX=x;
                else
                    realX+=delta;
            }
        else if(realY<y){
            if((realY+(delta))>y)
                realY=y;
            else{
                if(abs(y-realY)<0.01)
                    realY=y;
                else
                    realY+=delta;
            }
        }
        if(klatka<8)
            klatka+=delta*10;
        else klatka=1;
        return 1;
    }
    return 0;
}
