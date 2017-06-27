#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <list>
#include "item.h"
#include <iostream>

#define max_list_size 4
using namespace std;

class field
{
    public:
        field();
        virtual ~field();
        void setId(short);
        void setType(short);
        void setName(string);
        short getType();
        short getId();
        string getName();
        short mine();
        void setMineId(short);
    protected:
    private:
        short id;
        short type;
        short mineId;
        string name;

};

#endif // FIELD_H
