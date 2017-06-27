#ifndef RECIPMENT_H
#define RECIPMENT_H

#include <list>
#include <map>
#include "common.h"
#include <iostream>
class Recipment
{
    public:
        Recipment();
        virtual ~Recipment();
        void showAll();
        void addRecip(std::list<int>*,std::list<it_C>*);
        std::list<it_C> getItem(std::list<int>*);

    protected:

    private:
        std::map<std::list<int>,std::list<it_C>> recip;
};

#endif // RECIPMENT_H
