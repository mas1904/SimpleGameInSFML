#include "MapHelper.h"


MapHelper::MapHelper(DrawHelper *dh)
{
    this->dh=dh;
    //ctor
}

MapHelper::~MapHelper()
{
    //dtor
}
#pragma pack(push, 1)
struct saveterm_header
{
    short x;
    short y;
    short z;
    char c_items_eq;
};

struct saveterm_item
{
    char id;
    char count;
};

struct saveterm_field
{
    char id;
};
#pragma pack(pop)

inline char * stringToChar( string & s ) {
    long long N = s.length();
    char * out = new char[ N + 1 ];
    ::copy( s.c_str(),( s.c_str() + N - 1 ), out );
    return out;
}

char * fileToChar( const char * filename ) {
    ifstream file( filename, ios::binary );
    if( file.bad() ) {
        exit( - 1 );
    }

    filebuf * pbuf = file.rdbuf();
    long f_size = pbuf->pubseekoff( 0, ios::end, ios::in );
    file.seekg( 0 );

    char * ch_file = new char[ f_size + 1 ];

    file.read( ch_file, f_size );
    file.close();
    return ch_file;
}

void MapHelper::item_load(mapp *lmap){
    const char * fields_file = "items.xml";

    unique_ptr <char> fields(fileToChar(fields_file));
    xml_document <> doc;

    try {
        doc.parse<0>(fields.get());
    } catch(parse_error p) {
        p.what();
    }
    xml_node <> * n_fields = doc.first_node();
    bool countable=0;
    bool pickable=0;
    bool throwable=0;
    bool blockable=0;
    short attack=0;
    short defense=0;
    short destroyed=0;
    short type=0;
    item *tmp = new item;
    vector<int> *chance = new vector<int>;
    vector<it_C> *out = new vector<it_C>;
    it_C tmpc;
    for( xml_node <> * n_field = n_fields->first_node(); n_field; n_field = n_field->next_sibling()){
        for( xml_attribute <> * n_atr = n_field->first_attribute(); n_atr; n_atr = n_atr->next_attribute()){
            if(!strcmp(n_atr->name(), "id")){
                tmp->setId(atoi(n_atr->value()));
                tmp->sprite = new sf::Sprite;
                tmp->sprite->setTexture(*dh->loadSpr(1,atoi(n_atr->value())));
                tmp->sprite->setOrigin(0,tmp->sprite->getTexture()->getSize().y-64);
            }
            if(!strcmp(n_atr->name(), "name")) tmp->setName(n_atr->value());//tmp->setName(n_atr->value());
            if(!strcmp(n_atr->name(), "hp")) tmp->setMaxHp(atoi(n_atr->value()));//tmp->setName(n_atr->value());
        }
        for(xml_node <>* nn = n_field->first_node();nn;nn=nn->next_sibling()){
            if(!strcmp(nn->name(),"properties")){
                for( xml_node <> * prop = nn->first_node();prop;prop = prop->next_sibling()){
                    if(!strcmp(prop->first_attribute()->value(), "countable")) countable=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "pickable")) pickable=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "throwable")) throwable=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "blockable")) blockable=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "attack_points")) attack=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "defense_points")) defense=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "destroyed")) destroyed=(atoi(prop->value()));
                    if(!strcmp(prop->first_attribute()->value(), "type")) type=(atoi(prop->value()));
                }
            } else if(!strcmp(nn->name(),"mine")){
                for( xml_node <> * prop = nn->first_node();prop;prop = prop->next_sibling()){
                    tmpc.id = atoi(prop->value());
                    for( xml_attribute <> * atr = prop->first_attribute();atr;atr = atr->next_attribute()){
                        if(!strcmp(atr->name(), "count")) tmpc.c=(atoi(atr->value()));
                        if(!strcmp(atr->name(), "percent")) chance->push_back((atoi(atr->value())));
                    }
                    out->push_back(tmpc);
                }
                tmp->addMine(chance,out);
                chance->clear();
                out->clear();
            } else if(!strcmp(nn->name(),"builds")){
                bool itmb[2]={0,0};
                int id_b[2];
                int i=0;
                for( xml_node <> * prop = nn->first_node();prop;prop = prop->next_sibling()){
                    id_b[i] = atoi(prop->value());
                    xml_attribute<>*atr = prop->first_attribute();
                    if(!strcmp(atr->name(), "type"))
                        if(!strcmp(atr->value(), "i"))
                            itmb[i]=1;
                    i++;
                }
                tmp->setBuild(itmb,id_b);
            }
        }
        tmp->setType(countable, pickable, throwable,blockable,attack,defense,destroyed,type);
        lmap->addPrItem(tmp);
        destroyed = 0;
        type = 0;
        countable=0;
        pickable=0;
        throwable=0;
        blockable=0;
        attack=0;
        defense=0;
    }
    doc.clear();
}

Recipment *MapHelper::recip_load(){
    const char * fields_file = "recipments.xml";

    unique_ptr <char> fields(fileToChar(fields_file));
    xml_document <> doc;

    try {
        doc.parse<0>(fields.get());
    } catch(parse_error p) {
        p.what();
    }
    xml_node <> * n_fields = doc.first_node();
    Recipment *rc = new Recipment();
    list<it_C> *pro = new list<it_C>;
    list<int> *it = new list<int>;;
    it_C tmp;
    for( xml_node <> * n_field = n_fields->first_node(); n_field; n_field = n_field->next_sibling()){
        for( xml_node <> * nn = n_field->first_node();nn;nn=nn->next_sibling()){
            if(!strcmp(nn->name(), "product")){
                xml_attribute <> * n_atr = nn->first_attribute();
                tmp.c=atoi(n_atr->value());
                tmp.id=atoi(nn->value());
                pro->push_back(tmp);
            } else {
                it->push_back(atoi(nn->value()));
            }
        }
        rc->addRecip(it,pro);
        pro->clear();
        it->clear();
    }
    doc.clear();
    return rc;
}

void MapHelper::field_load(mapp *lmap){
    const char * fields_file = "fields.xml";

    unique_ptr <char> fields(fileToChar(fields_file));
    xml_document <> doc;

    try {
        doc.parse<0>(fields.get());
    } catch(parse_error p) {
        p.what();
    }
    xml_node <> * n_fields = doc.first_node();
    field *tmp = new field;
    for( xml_node <> * n_field = n_fields->first_node(); n_field; n_field = n_field->next_sibling()){
        for( xml_attribute <> * n_atr = n_field->first_attribute(); n_atr; n_atr = n_atr->next_attribute()){
            if(!strcmp(n_atr->name(), "id")){
                    tmp->setId(atoi(n_atr->value()));
                    dh->loadSpr(0,atoi(n_atr->value()));
            }
            if(!strcmp(n_atr->name(), "name")) tmp->setName(n_atr->value());//tmp->setName(n_atr->value());
            if(!strcmp(n_atr->name(), "type")) tmp->setType(atoi(n_atr->value()));
            if(!strcmp(n_atr->name(), "mine")) tmp->setMineId(atoi(n_atr->value()));

        }
        lmap->addPrField(tmp);

    }
    doc.clear();
}

mapp *MapHelper::map_loader(string filename, player *Player){

    mapp * lmap = new mapp;
    MapHelper::field_load(lmap);
    MapHelper::item_load(lmap);

    ifstream loader(filename.c_str(), ios::binary);
    char* temp = new char(sizeof(saveterm_header));
    loader.read(temp, sizeof(saveterm_header));
    saveterm_header* header = (saveterm_header*)(temp);
    Player->set_pos(header->x, header->y, header->z);

    saveterm_item *temp_item = new saveterm_item;
    temp = new char[sizeof(saveterm_item)];
    for(short i=0; i<25; i++){
        loader.read(temp, sizeof(saveterm_item));
        temp_item = (saveterm_item*)(temp);
        Player->add_item(lmap->getPrItem(temp_item->id),temp_item->count);
    }
    Player->setC_items(header->c_items_eq);
    char* tmpf = new char;
    saveterm_field* fheader = new saveterm_field;
    field* temp_field;
    char* height = new char;
    char* itf = new char;
    char* cc = new char;
    for(short i=0; i<1000; i++){
        for(short j=0; j<1000; j++){
            loader.read(height, sizeof(char));
            lmap->setH(i, j, *((char*)(height)));
            for(short z=0; z<lmap->getH(i, j); z++){
                loader.read(tmpf, sizeof(char));

                lmap->setField(i, j, z, *tmpf);
                if((short)loader.peek()==255){
                    loader.ignore();
                    loader.read(itf, sizeof(char));
                    loader.read(cc, sizeof(char));
                    lmap->place_item(i,j,z,*itf,*(short*)cc);
                }
            }
        }
    }
    loader.close();
    return lmap;
}

short MapHelper::map_saver(string filename, mapp *lmap, player *Player){
    ofstream saver(filename.c_str(), ios::binary);

    saveterm_header* header = new saveterm_header;

    header->x = Player->getX();
    header->y = Player->getY();
    header->z = Player->getZ();
    header->c_items_eq = Player->getC_items();

    saver.write((char*)(header), sizeof(saveterm_header));

    saveterm_item *temp_item = new saveterm_item;
    item * itmp;
    for(short i=0; i<25; i++){
            itmp = Player->getItem(i);
            temp_item->id = itmp->getId();
            temp_item->count = itmp->getCount();
            saver.write((char*)(temp_item), sizeof(saveterm_item));
    }

    saveterm_field* fheader = new saveterm_field;

    field * ftmp;
    short * zz = new short;
    short * a = new short;
    for(short i=0; i<1000; i++){
        for(short j=0; j<1000; j++){
            saver.put(lmap->getH(i, j));
            for(short z=0; z<lmap->getH(i, j); z++){
                saver.put(lmap->getFieldId(i, j, z));
                if(lmap->getC_items(i, j, z)){
                    saver.put(255);
                    temp_item->id = lmap->getItem(i, j, z)->getId();
                    temp_item->count = lmap->getItem(i, j, z)->getCount();
                    saver.write((char*)(temp_item), sizeof(saveterm_item));
                }
            }
        }
    }
    saver.close();
}
