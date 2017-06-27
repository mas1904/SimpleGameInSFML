#include "Recipment.h"
Recipment::Recipment()
{
    //ctor
}

Recipment::~Recipment()
{
    //dtor
}

void Recipment::showAll(){

}

void Recipment::addRecip(std::list<int> *l,std::list<it_C> *cc){
    l->sort();
    recip[*l] = *cc;
}

std::list<it_C> Recipment::getItem(std::list<int> *l){
    l->sort();
    return recip[*l];
}
