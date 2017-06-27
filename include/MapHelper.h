#ifndef MAPHELPER_H
#define MAPHELPER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string.h>
#include <map>

#include "Recipment.h"
#include "mapp.h"
#include "player.h"
#include "DrawHelper.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;

using namespace std;

class MapHelper
{
    public:
        MapHelper();
        MapHelper(DrawHelper *dh);
        virtual ~MapHelper();
        mapp *map_loader(string, player*);
        short map_saver(string, mapp*, player*);
        void item_load(mapp*);
        void field_load(mapp*);
        Recipment *recip_load();
    protected:
    private:
        DrawHelper *dh;
};

#endif // MAPHELPER_H
