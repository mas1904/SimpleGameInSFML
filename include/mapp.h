#ifndef MAPP_H
#define MAPP_H
#include "field.h"
#include <vector>
#include <map>
class mapp
{
    public:
        mapp();
        virtual ~mapp();
        field *getField(short, short, short);
        int getFieldId(short, short, short);
        void setField(short, short, short, char);
        void addPrField(field*);
        void addPrItem(item*);
        void setPos(short, short, short);
        short getH(short, short);
        void setH(short, short, short);
        void addH(short, short);
        void minusH(short, short);
        void place_item(short, short, short, char, short);
        void place_item(short, short, short, item);
        void place_item(short, short, char, short);
        void place_item(short, short, item);
        bool getC_items(short, short, short);
        item *getItem(short, short, short);
        void takeItem(short,short,short);
        item *getPrItem(char);
        item *getTopItem(short,short);
        map<short,map<short, map<short, item*>>> items;
    protected:
    private:
        char p_map[1000][1000][20];
        vector<field> p_field;
        vector<item> p_item;
        short height[1000][1000];

};

#endif // MAPP_H
