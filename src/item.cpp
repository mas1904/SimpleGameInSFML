#include "item.h"

item::item()
{
    item::count=0;
    build=false;


    //ctor
}

item::item(sf::Sprite s){

}

item::~item()
{
    //dtor
}

void item::set_count(short c){
    item::count = c;
}

void item::setId(short c){
    item::id = c;
}

void item::setHp(short c){
    item::hp = c;
}

void item::setAD(short c){
    item::attack = c;
}

void item::setDF(short c){
    item::defense = c;
}

void item::setMaxHp(short c){
    item::max_hp = c;
    item::hp = c;
}

short item::getCount(){
    return item::count;
}

short item::getId(){
    return item::id;
}

short item::getHp(){
    return item::hp;
}

short item::getAD(){
    return item::attack;
}

short item::getDF(){
    return item::defense;
}

short item::getMaxHp(){
    return item::max_hp;
}

void item::setName(string n){
    item::name = n;
}

string item::getName(){
    return item::name;
}
bool item::isPickable(){
    return item::pickable;
}
bool item::isThrowable(){
    return item::throwable;
}
bool item::isCountable(){
    return item::countable;
}
bool item::isBlockable(){
    return item::blockable;
}

bool item::isBuild(){
    return build;
}


short item::getDestroyItem(){
    return destroyed;
}

short item::getBuildId(int orient){
    return build_id[orient];
}

bool item::getBuildType(int orient){
    return build_type[orient];
}

void item::setBuild(bool field[2], int id[2]){
    for(int i=0;i<2;i++){
        build_id[i] = id[i];
        build_type[i] = field[i];
    }
    build=true;
}

short item::getType(){
    return type;
}

void item::setType(bool c, bool p, bool t, bool b, short ad, short df, short destroyed, short type){
    item::countable=c;
    item::pickable=p;
    item::throwable=t;
    item::blockable=b;
    item::attack=ad;
    item::defense=df;
    item::destroyed=destroyed;
    item::type=type;
}

void item::addMine(std::vector<int> *l,std::vector<it_C> *cc){
    chance=*l;
    item::mines=*cc;
}

it_C item::mine(short hpm){
    int liczba = std::rand()%100;
    it_C tmp = {0,0};
    for(int i=0;i<chance.size();i++){
        if(liczba <= chance[i]){
            tmp = mines[i];
            break;
        }
    }
    hp-=hpm*5;
    return tmp;
}
