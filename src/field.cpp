#include "field.h"

field::field()
{
    //ctor
}

field::~field()
{
    //dtor
}

short field::getId(){
    return field::id;
}

string field::getName(){
    return field::name;
}

short field::getType(){
    return field::type;
}

void field::setId(short id){
    field::id=id;
}

void field::setType(short type){
    field::type=type;
}

void field::setName(string name){
    field::name=name;
}

void field::setMineId(short id){
    field::mineId=id;
}

short field::mine(){
    if(field::mineId>0)
        return field::mineId;
    else return 0;
}
