#include "mapp.h"


mapp::mapp()
{
    //ctor

}

mapp::~mapp()
{
    //dtor
}

short mapp::getH(short x, short y)
{
    return height[x][y];
}

item * mapp::getTopItem(short x, short y)
{
    for(int i=0;i<mapp::height[x][y];i++)
        cout << items[x][y][i] << endl;
    return items[x][y][height[x][y]-1];
}
void mapp::setH(short x, short y, short h)
{
    mapp::height[x][y] = h;
}

void mapp::addH(short x, short y)
{
    mapp::height[x][y]++;
}

void mapp::minusH(short x, short y)
{
    mapp::height[x][y]--;
}

void mapp::addPrField(field* new_field){
    mapp::p_field.push_back(*new_field);

}

void mapp::addPrItem(item* new_item){
    mapp::p_item.push_back(*new_item);

}

void mapp::setField(short xx, short yy, short zz, char id)
{
    mapp::p_map[xx][yy][zz] = id;

}

int mapp::getFieldId(short xx, short yy, short zz)
{
    return mapp::p_map[xx][yy][zz];
}

field * mapp::getField(short xx, short yy, short zz)
{

    return &mapp::p_field[mapp::p_map[xx][yy][zz]];
}

bool mapp::getC_items(short xx, short yy, short zz)
{
    if(mapp::items[xx][yy][zz]!=NULL)
        return 1;
    return 0;
}
item *mapp::getItem(short xx, short yy, short zz)
{
    if(mapp::items[xx][yy][zz]!=NULL)
        return mapp::items[xx][yy][zz];
    return NULL;
}
void mapp::takeItem(short xx, short yy, short zz)
{
    zz=getH(xx,yy)-1;
    if(mapp::items[xx][yy][zz]!=NULL){
        mapp::items[xx][yy][zz]=NULL;
        if(getFieldId(xx,yy,zz)==0)
            minusH(xx,yy);
    }

}
item *mapp::getPrItem(char id)
{
    return &mapp::p_item[id];
}

void mapp::place_item(short xx, short yy, short zz, item tmp){

    item *t = new item;
    *t = tmp;
    t->sprite = new sf::Sprite;
    *t->sprite = *tmp.sprite;
    mapp::items[xx][yy][zz]=t;
}

void mapp::place_item(short xx, short yy, item tmp){
    if(getC_items(xx,yy,getH(xx,yy)-1)){
        addH(xx,yy);
        setField(xx,yy,getH(xx,yy)-1,0);
    }
    item *t = new item;
    *t = tmp;
    t->sprite = new sf::Sprite;
    *t->sprite = *tmp.sprite;
    mapp::items[xx][yy][getH(xx,yy)-1]=t;
}

void mapp::place_item(short xx, short yy, char id, short c){
    if(getC_items(xx,yy,getH(xx,yy)-1)){
        addH(xx,yy);
        setField(xx,yy,getH(xx,yy)-1,0);
    }

    item * tmp = new item;
    *tmp = *mapp::getPrItem(id);
    tmp->sprite = new sf::Sprite;
    *tmp->sprite = *mapp::getPrItem(id)->sprite;

    tmp->set_count(c);
    mapp::items[xx][yy][getH(xx,yy)-1]=tmp;
}


void mapp::place_item(short xx, short yy, short zz, char id, short c)
{

    item * tmp = new item;
    *tmp = *mapp::getPrItem(id);
    tmp->sprite = new sf::Sprite;
    *tmp->sprite = *mapp::getPrItem(id)->sprite;

    tmp->set_count(c);
    mapp::items[xx][yy][zz]=tmp;
}
