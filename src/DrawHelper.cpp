#include "DrawHelper.h"
#define SAVE_BUTTON 0
#define LOAD_BUTTON 1
#define DELETE_BUTTON 2
#define H_USE 0
#define H_TAKE 1
#define H_THROW 2
#define H_MAP 3
#define H_EQ 4
#define H_CHANGER 5

DrawHelper::DrawHelper()
{
    fstream config;
    config.open("config.ini", ios::in);
    string tmp;
    string w = "width:";
    int all_set = 0;
    if(config.good()){
        while(!config.eof()){
            config >> tmp;
            if(tmp.compare(w)==0){
                config >> DrawHelper::sizex;
                all_set++;
            }
            else if(tmp.compare("height:")==0){
                config >> DrawHelper::sizey;
                all_set++;
            }
            else if(tmp.compare("fullscreen:")==0){
                config >> DrawHelper::isFullScreen;
                all_set++;
            }
            else break;
        }
        config.close();
    }
    else {
        config.close();
        sizex=640;
        sizey=480;
        isFullScreen=false;
        saveConfig();
        all_set=NUMBER_OD_OPTIONS;
    }
    if(all_set!=NUMBER_OD_OPTIONS){
        sizex=640;
        sizey=480;
        isFullScreen=false;
    }
    if(isFullScreen)
        mainWindow.create( sf::VideoMode( sizex, sizey, 32 ), "Foooorpg", sf::Style::Fullscreen );
    else
        mainWindow.create( sf::VideoMode( sizex, sizey, 32 ), "Foooorpg" );

    mainWindow.clear(sf::Color::White);
    mainWindow.setFramerateLimit(60);
    if(!font.loadFromFile("data/LithosPro-Regular.otf")){
        MessageBox(NULL,"Font LithosPro-Regular.otf not found!","ERROR",NULL);
        return;
    }
    if(!official.loadFromFile("data/MING__PL.ttf")){
        MessageBox(NULL,"Font MING__PL.ttf not found!","ERROR",NULL);
        return;
    }
    for(int i=0;i<MENU_ITEM;i++){
        option[i].setFont(font);
        option[i].setCharacterSize(mainWindow.getSize().y*0.06);
        option[i].setOutlineColor(sf::Color(220,146,16));
        option[i].setColor(sf::Color(255,255,255));
        option[i].setOutlineThickness(2);
    }
    float przekatna = sqrt((mainWindow.getSize().x*mainWindow.getSize().x)+(mainWindow.getSize().y*mainWindow.getSize().y));
    menu_panel.setSize(sf::Vector2f(przekatna*0.3,przekatna*0.2));
    menu_panel.setPosition((mainWindow.getSize().x-menu_panel.getSize().x)/2,(mainWindow.getSize().y-menu_panel.getSize().y)/2);
    menu_panel.setFillColor(sf::Color(100,100,100,100));
    menu_panel.setOutlineColor(sf::Color(0,0,0));
    menu_panel.setOutlineThickness(2);

    float menu_x = menu_panel.getPosition().x;
    float menu_y = menu_panel.getPosition().y;
    float menu_w = menu_panel.getSize().x;
    float menu_h = menu_panel.getSize().y;

   // list_save.setSize(sf::Vector2f(menu_w*0.8,menu_h*0.5));


    save_data.setFont(font);
    save_title.setFont(font);
    load_title.setFont(font);
    hotkeys_title.setFont(font);

    save_title.setStyle(sf::Text::Underlined);
    load_title.setStyle(sf::Text::Underlined);
    hotkeys_title.setStyle(sf::Text::Underlined);

    save_data.setColor(sf::Color::Black);
    save_title.setColor(sf::Color::Black);
    load_title.setColor(sf::Color::Black);

    save_data.setString("Data zapisu: ");
    save_title.setString("Zapisz");
    load_title.setString("Wczytaj");

    int fontSize=przekatna*0.02;

    hotkeys_title.setPosition((int)(menu_x+menu_w*0.015)+0.2,(int)(menu_y-menu_h*0.02));
    hotkeys_title.setCharacterSize(fontSize*1.5);
    hotkeys_title.setString("Sterowanie");
    hotkeys_title.setColor(sf::Color::Black);

    string hots[]={"Interakcja","Podnoszenie","Ekwipunek","Mapa","Ekwipunek","Aktywuj"};
    string keys[]={"E","T","I"};
    for(int i=0;i<3;i++){
        hotkeys_label[i].setPosition((int)(menu_x+menu_w*0.08),(int)(menu_y+menu_h*0.17+fontSize*i*1.1));
        hotkeys_label[i].setCharacterSize(fontSize*0.8);
        hotkeys_label[i].setString(hots[i]);
        hotkeys_label[i].setFont(font);
        hotkeys_label[i].setColor(sf::Color::Black);
        Hotkeys[i] = new button((int)(menu_x+menu_w*0.92-fontSize*3),(int)(menu_y+menu_h*0.16+fontSize*i*1.1),fontSize*3,fontSize*0.9,1,sf::Color::White,sf::Color(60,60,60),keys[i],&font);
        Hotkeys[i]->setHover(false);
    }

    list_save = new listbox(1,menu_x+(menu_w*0.02),menu_y+menu_h*0.3,menu_w*0.96,menu_h*0.5,(int)(fontSize*0.8),&font);
    //list_save.setFillColor(sf::Color(100,100,100,0));
    //list_save.setOutlineColor(sf::Color(150,150,150));

    save_data.setCharacterSize(fontSize*0.5);
    save_title.setCharacterSize(fontSize*1.5);
    load_title.setCharacterSize(fontSize*1.5);

    save_data.setPosition((int)(menu_x+menu_w*0.02),(int)(menu_y+menu_h*0.28-fontSize*0.5));
    save_title.setPosition((int)(menu_x+menu_w*0.015)+0.2,(int)(menu_y-menu_h*0.02));
    load_title.setPosition((int)(menu_x+menu_w*0.015)+0.2,(int)(menu_y-menu_h*0.02));


    Przycisk[SAVE_BUTTON] = new button(menu_x+(menu_w-fontSize*3)/2,menu_y+menu_h*0.98-fontSize*1.4,fontSize*3,fontSize*1.4,1,sf::Color::White,sf::Color(60,60,60,255),"Zapisz",&font);
    Przycisk[LOAD_BUTTON] = new button(menu_x+(menu_w-fontSize*3)/2,menu_y+menu_h*0.98-fontSize*1.4,fontSize*3,fontSize*1.4,1,sf::Color::White,sf::Color(60,60,60,255),"Wczytaj",&font);
    Przycisk[DELETE_BUTTON] = new button(menu_x+menu_w*0.98-fontSize*3,menu_y+menu_h*0.02,fontSize*3,fontSize*1.4,1,sf::Color::White,sf::Color(150,60,60,255),"Skasuj",&font);
    Przycisk[DELETE_BUTTON]->setShadow(1);
    Przycisk[SAVE_BUTTON]->setShadow(1);
    Przycisk[LOAD_BUTTON]->setShadow(1);

    for(int i=0;i<map_draw_y;i++)
        for(int j=0;j<map_draw_x;j++)
            for(int z=0;z<20;z++){
                //item_spr[j][i][z].setOrigin(sf::Vector2f(0.5f,1.0f));

                map_spr[j][i][z].setPosition(j*64-32,(i-2)*64-z*4);
               // item_spr[j][i][z].setPosition(j*64-32,(i-2)*64-z*4);

            }



    kamera = sf::View(sf::Vector2f(640,360),sf::Vector2f(1280,720));

    Eq_txt.loadFromFile("spr/eq.png");
    Eq_spr.setTexture(Eq_txt);
    sx = sizex/1280;
    sy = sizey/720;
    Eq_spr.setPosition(((1280-344)/2)*sx,((720-350)/2)*sy);
    eq=false;
    for(int j=0;j<4;j++)
        for(int i=0;i<5;i++)
            Eq_item[i+j*5+5].setPosition(((1280-344)/2+8+i*66)*sx,((720-350)/2+8+j*66)*sy);
    for(int i=0;i<5;i++)
        Eq_item[i].setPosition(((1280-344)/2+8+i*66)*sx,((720-350)/2+8+4*66+12)*sy);

    logo_txt.loadFromFile("spr/logo.png");
    logo.setTexture(logo_txt);
    logo.setPosition((1280-640)/2*sx,720*sy*0.06);
    hover.loadFromFile("spr/zaznaczony.png");
    Eq_hover.setTexture(hover);
    Eq_hover_bool=false;
    Item_tip = new tooltip(&font,fontSize*0.7);
    minimap.setViewport(sf::FloatRect(0.8f, 0, 0.2f, 0.3f));
    tip=0;
    left_gui_txt.loadFromFile("spr/left_gui.png");
    left_gui.setTexture(left_gui_txt);
    //left_gui.setScale(sf::Vector2f(mainWindow.getSize().x/1280*1.0f,mainWindow.getSize().x/1280*1.0f));
    left_gui.setPosition((mainWindow.getSize().x-726)/2,mainWindow.getSize().y-76);
    for(int i=0;i<5;i++)
        left_gui_items[i].setPosition((mainWindow.getSize().x-726)/2+i*70+2,mainWindow.getSize().y-76+2);
    gui_item_number.setCharacterSize(fontSize*0.5);
    gui_item_number.setFont(font);
    gui_selected_id=0;
    gui_selected_id=0;
    gui_selected_txt.loadFromFile("spr/selected.png");
    gui_selected_spr.setPosition((mainWindow.getSize().x-726)/2,mainWindow.getSize().y-76);
    gui_selected_spr.setTexture(gui_selected_txt);
    eq_selected_spr.setTexture(gui_selected_txt);
    Hp_bar_out.setFillColor(sf::Color(100,50,50));
    Hp_bar.setFillColor(sf::Color(200,50,50));
    Mp_bar_out.setFillColor(sf::Color(50,50,100));
    Mp_bar.setFillColor(sf::Color(50,50,200));

    hp_points.setFont(font);
    mp_points.setFont(font);

    hp_points.setCharacterSize(fontSize*0.35);
    mp_points.setCharacterSize(fontSize*0.35);

    hp_points.setString("0|0");
    mp_points.setString("1|1");

    int offset = hp_points.findCharacterPos(3).x;
    cout << offset << endl;


    hp_points.setColor(sf::Color::White);
    mp_points.setColor(sf::Color::White);

    hp_points.setPosition(((1280-726-offset)/2+174)*sx,(720-92)*sy);
    mp_points.setPosition(((1280-726-offset)/2+174+377)*sx,(720-92)*sy);

    Hp_bar.setSize(sf::Vector2f(348,10));
    Hp_bar_out.setSize(sf::Vector2f(348,10));
    Mp_bar.setSize(sf::Vector2f(348,10));
    Mp_bar_out.setSize(sf::Vector2f(348,10));

    Hp_bar_out.setOutlineColor(sf::Color(50,10,10));
    Mp_bar_out.setOutlineColor(sf::Color(10,10,50));
    Hp_bar_out.setOutlineThickness(2);
    Mp_bar_out.setOutlineThickness(2);

    Hp_bar.setPosition((mainWindow.getSize().x-726)/2,mainWindow.getSize().y-90);
    Hp_bar_out.setPosition((mainWindow.getSize().x-726)/2,mainWindow.getSize().y-90);
    Mp_bar.setPosition((mainWindow.getSize().x-726)/2+377,mainWindow.getSize().y-90);
    Mp_bar_out.setPosition((mainWindow.getSize().x-726)/2+377,mainWindow.getSize().y-90);
}

void DrawHelper::setSprite(player* Player){
    Player->texture.loadFromFile("spr/player.png");
    sf::IntRect r1(32, 8+1280,64,128);
    Player->sprite = new sf::Sprite();
    Player->sprite->setTexture(Player->texture);
    Player->sprite->setTextureRect(r1);
    Player->sprite->setOrigin(0,64);
    Player->sprite->setPosition(10*64-32,5*64);
    updatePlayer(Player->getX(),Player->getY(),Player->getZ());
}

void DrawHelper::updateMP(short mp, short maxmp){
    Mp_bar.setSize(sf::Vector2f( 348*mp/maxmp-2 ,10));
    string text=to_string(mp) + " | "+to_string(maxmp);
    mp_points.setString(text);
    int offset = mp_points.findCharacterPos(text.length()).x-mp_points.getPosition().x;
    mp_points.setPosition(((1280-726-offset)/2+174+377)*sx,(720-92)*sy);
}


void DrawHelper::updateHP(short hp, short maxhp){
    Hp_bar.setSize(sf::Vector2f( 348*hp/maxhp-2 ,10));
    string text=to_string(hp) + " | "+to_string(maxhp);
    hp_points.setString(text);
    int offset = hp_points.findCharacterPos(text.length()).x-hp_points.getPosition().x;
    hp_points.setPosition(((1280-726-offset)/2+174)*sx,(720-92)*sy);
}


void DrawHelper::selectGuiItem(int i){
    gui_selected_spr.setPosition((mainWindow.getSize().x-726)/2+i*70,mainWindow.getSize().y-76);
}

void DrawHelper::unselect(int i){
    eq_selected[i]=0;
}

bool DrawHelper::selectEqItem(int i){
    return eq_selected[i]=eq_selected[i]?0:1;
}

sf::RenderWindow * DrawHelper::getWindow(){
    return &mainWindow;
}

void DrawHelper::resizeAll(){


}

void DrawHelper::loadHotkeys(){
    fstream config;
    config.open("hotkeys.ini", ios::in);
    string tmp;
    int all_set = 0;
    if(config.good()){
        while(!config.eof()){
            config >> tmp;
            if(tmp.compare("use:")==0){
                config >> Hotkeys_key[H_USE];
                all_set++;
            }
            else if(tmp.compare("take:")==0){
                config >> Hotkeys_key[H_TAKE];
                all_set++;
            }
            else if(tmp.compare("throw:")==0){
                config >> Hotkeys_key[H_THROW];
                all_set++;
            }
            else if(tmp.compare("map:")==0){
                config >> Hotkeys_key[H_MAP];
                all_set++;
            }
            else if(tmp.compare("eq:")==0){
                config >> Hotkeys_key[H_EQ];
                all_set++;
            }
            else if(tmp.compare("ch:")==0){
                config >> Hotkeys_key[H_CHANGER];
                all_set++;
            }
            else break;
        }
        config.close();
    }
    else {
        config.close();

        saveConfig();

    }
    if(all_set!=NUMBER_OD_OPTIONS){

    }
    //TO DO
}

void DrawHelper::drawLoadMenu(){
    mainWindow.draw(menu_panel);
    mainWindow.draw(load_title);
    list_save->draw(&mainWindow);
    mainWindow.draw(save_data);
    Przycisk[LOAD_BUTTON]->draw(&mainWindow);
    Przycisk[DELETE_BUTTON]->draw(&mainWindow);
}

void DrawHelper::drawSaveMenu(){
    mainWindow.draw(menu_panel);
    mainWindow.draw(save_title);
    list_save->draw(&mainWindow);
    mainWindow.draw(save_data);
    Przycisk[SAVE_BUTTON]->draw(&mainWindow);
    Przycisk[DELETE_BUTTON]->draw(&mainWindow);
}


void DrawHelper::saveConfig(){
    fstream config;
    config.open("config.ini", ios::out);
    config << "width: " << DrawHelper::sizex << endl;
    config << "height: " << DrawHelper::sizey << endl;
    config << "fullscreen: " << DrawHelper::isFullScreen << endl;
    config.close();
}

DrawHelper::~DrawHelper()
{
    //dtor
}

string DrawHelper::enterLoad(int panel){
    if(file.size()>0)
        return file;
    else
        return "";
}

void DrawHelper::enterControls(){
    mainWindow.draw(menu_panel);
    mainWindow.draw(hotkeys_title);
    Przycisk[SAVE_BUTTON]->draw(&mainWindow);
    for(int i=0;i<NUMBER_OF_CONTROLS;i++){
        mainWindow.draw(hotkeys_label[i]);
        Hotkeys[i]->draw(&mainWindow);
    }
}

void DrawHelper::enterSettings(){

}

void DrawHelper::odznacz(int z, int k){

}

sf::Texture *DrawHelper::loadSpr(bool item, int id){
    sf::Texture tmp;
    if(item){
        string n="spr/items/" + std::to_string(id);
        n+=".png";
        tmp.loadFromFile(n);
        p_i_spr[id]=tmp;
        return &p_i_spr[id];
    }
    else{
        string n="spr/fields/" + std::to_string(id);
        n+=".png";
        tmp.loadFromFile(n);
        p_f_spr[id]=tmp;
        return &p_f_spr[id];
    }
}

void DrawHelper::drawItem(short id, short y, short x){

}

void DrawHelper::drawField(short id, short y, short x){

}

void DrawHelper::refreshEq(player *Player){

}

short DrawHelper::drag(sf::Vector2i ms,player *Player){
    dragging = dragging==0?1:0;
    if(Eq_spr.getGlobalBounds().contains(ms.x,ms.y)){
        for(int i=0;i<25;i++){
            if(Eq_item[i].getGlobalBounds().contains(ms.x,ms.y)){
                if(dragging==1){
                    draged.setTexture(p_i_spr[Player->getItem(i)->getId()]);
                    draged.setPosition(Eq_item[i].getPosition());
                    updateDownItems(Player);
                    dragpoint.x=Eq_item[i].getPosition().x-ms.x;
                    dragpoint.y=Eq_item[i].getPosition().y-ms.y;
                }
                if(Player->getItem(i)->getId()!=0||dragging==0)
                    return i;

            }
        }
        if(dragging==1)
            dragging=0;
        return -2;
    }
    if(dragging==1)
            dragging=0;
    return -1;
}

void DrawHelper::hoverEq(sf::Vector2i ms,player *Player){
    if(dragging){

        draged.setPosition(ms.x+dragpoint.x,ms.y+dragpoint.y);
    }
    if(Eq_spr.getGlobalBounds().contains(ms.x,ms.y)){
            bool jest=0;
        for(int i=0;i<25;i++){
            if(Eq_item[i].getGlobalBounds().contains(ms.x,ms.y)){
                Eq_hover.setPosition(Eq_item[i].getPosition());
                jest=1;
                if(Player->getItem(i)->getId()!=0){
                    Item_tip->setPosition(ms);
                    Item_tip->setText(Player->getItem(i)->getName());
                    Item_tip->setADP(Player->getItem(i)->getAD(),Player->getItem(i)->getDF());
                    Item_tip->setHp(Player->getItem(i)->getHp()*100/Player->getItem(i)->getMaxHp());
                    tip=1;
                } else tip=0;

                Eq_hover_bool=true;
                break;
            }
        }
        if(jest==0)
            Eq_hover_bool=false;
    }
}

int DrawHelper::enterInventory(player *Player){

    mainWindow.draw(Eq_spr);
    if(Eq_hover_bool)
        mainWindow.draw(Eq_hover);
    for(int i=0;i<25;i++){
        if(eq_selected[i]){
            eq_selected_spr.setPosition(Eq_item[i].getPosition().x-2,Eq_item[i].getPosition().y-2);
            mainWindow.draw(eq_selected_spr);
        }
        Eq_item[i].setTexture(p_i_spr[Player->getItem(i)->getId()]);
        //Eq_item[i].setScale(0.9,0.9);
        mainWindow.draw(Eq_item[i]);

    }
    if(Eq_hover_bool&&dragging==0&&tip)
        Item_tip->draw(&mainWindow);
    if(dragging){
        mainWindow.draw(draged);
    }
}

void DrawHelper::getKeyEvent(int &action, bool &exit, bool &aktywny){

}

void DrawHelper::loadSaves(){
    list_save->eraseAll();
    DIR * path;
    struct dirent * f;
    if( path = opendir("saves") ){
        while( f = readdir(path)){
            if(f->d_name[0]!='.')
            list_save->populate(f->d_name);
        }
        closedir(path);
    }
}

int DrawHelper::enterMenu(int m){
    //main menu
    int p10x = sizex/80;
    int p10y = sizey/40*27;
                       //0       1       2           3          4             5         6                7
    string str[]={"Nowa gra","Wczytaj","Zapisz","Ustawienia","Sterowanie","Kontynuuj","Powrót do menu","Koniec"};
    if(m==0){
        option[0].setString(str[0]);
        option[1].setString(str[1]);
        option[2].setString(str[4]);
        option[3].setString(str[3]);
        option[4].setString(str[7]);
        for(int i=0; i<5; i++)
            option[i].setPosition((int)p10x,p10y+(i*option[i].getCharacterSize())+option[i].getCharacterSize()*0.1);
    }
    //game menu
    else if(m==1){
        option[0].setString(str[5]);
        option[1].setString(str[2]);
        option[2].setString(str[4]);
        option[3].setString(str[3]);
        option[4].setString(str[6]);
        for(int i=0; i<5; i++)
            option[i].setPosition((int)p10x,(int)(p10y+(i*option[i].getCharacterSize())+option[i].getCharacterSize()*0.1));
    }
    mainWindow.clear(sf::Color::White);
    mainWindow.draw(logo);
    for(int i=0; i<5; i++)
        mainWindow.draw(option[i]);
    mainWindow.display();
    int addmenu=0;
    int hotkeys=0;
    bool some=0,somep=0,changeSelect=0;
    int zmiana=1,zmianap=1,poprzednia=1,poprzedniap=1;
    sf::Event event;
    sf::Vector2i mousePosition;
    int c=2;
    while( mainWindow.isOpen() )
    {
        if(c==2){
            mainWindow.waitEvent( event );
            c=0;

            if(event.type == sf::Event::Resized){
                //resizeAll();
                changeSelect=1;
            }
            if(event.type == sf::Event::MouseMoved){
                mousePosition = sf::Mouse::getPosition( mainWindow );
                mousePosition.x*=1.0/((double)(mainWindow.getSize().x)/1280);
                mousePosition.y*=1.0/((double)(mainWindow.getSize().y)/720);
                for(int i=0;i<5;i++)
                    if(option[i].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                        if(i+1!=zmiana){
                            if(zmiana!=0)
                                option[zmiana-1].setStyle(sf::Text::Style::Regular);//(sf::Color(221,221,221));
                            option[i].setStyle(sf::Text::Style::Underlined);//setOutlineColor(sf::Color::Cyan);
                            zmiana=i+1;
                        }
                        some=1;
                    }
                if(some==0 && zmiana!=0){
                    option[zmiana-1].setStyle(sf::Text::Style::Regular);//setOutlineColor(sf::Color(221,221,221));
                    zmiana=0;
                }
                some=0;
                if(hotkeys){
                    if(Przycisk[SAVE_BUTTON]->bounds().contains(mousePosition.x,mousePosition.y)){
                        if(zmianap!=1){
                            Przycisk[SAVE_BUTTON]->hover();
                            zmianap=1;
                        }
                        somep=1;
                    }
                    if(somep==0 && zmianap!=0){
                        Przycisk[SAVE_BUTTON]->not_hover();
                        zmianap=0;
                    }
                    somep=0;
                }
                if(addmenu){
                    for(int i=0;i<3;i++)
                        if((addmenu==1&&i!=SAVE_BUTTON)||(addmenu==2&&i!=LOAD_BUTTON))
                            if(Przycisk[i]->bounds().contains(mousePosition.x,mousePosition.y)){
                                if(i+1!=zmianap){
                                    if(zmianap!=0)
                                        Przycisk[zmianap-1]->not_hover();
                                    Przycisk[i]->hover();
                                    zmianap=i+1;
                                }
                                somep=1;
                            }
                    if(somep==0 && zmianap!=0){
                        Przycisk[zmianap-1]->not_hover();
                        zmianap=0;
                    }
                    somep=0;
                }
            }
            if(event.type == sf::Event::MouseButtonReleased
            && event.key.code == sf::Mouse::Left){
                if(addmenu){
                    if(list_save->bounds().contains(mousePosition.x,mousePosition.y)){
                        list_save->select(mousePosition.y);
                        changeSelect=1;
                    }
                    if(Przycisk[DELETE_BUTTON]->bounds().contains(mousePosition.x,mousePosition.y)){
                        list_save->dropItem();
                        changeSelect=1;
                    }
                    if(addmenu==1){
                        if(Przycisk[LOAD_BUTTON]->bounds().contains(mousePosition.x,mousePosition.y)){
                            file=list_save->getSelected();
                            Przycisk[LOAD_BUTTON]->not_hover();
                            zmianap=0;
                            somep=0;
                            return ENTER_LOAD_MENU;
                        }
                    }
                    else if(addmenu==2){
                        if(Przycisk[SAVE_BUTTON]->bounds().contains(mousePosition.x,mousePosition.y)){
                            file=list_save->getSelected();
                            Przycisk[SAVE_BUTTON]->not_hover();
                            zmianap=0;
                            somep=0;
                            return ENTER_SAVE_MENU;
                        }
                    }
                }
                if(hotkeys){

                }
                if(option[0].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                    if(m==0)
                        return START_GAME;
                    else
                        return RETURN_GAME;
                }
                if(option[1].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                    if(m==0)
                        addmenu=1;
                    else
                        addmenu=2;
                    loadSaves();
                    hotkeys=0;
                    zmiana=-1;
                }
                if(option[2].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                    hotkeys=1;
                    addmenu=0;
                    zmiana=-1;
                }
                if(option[3].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                    return ENTER_SETTINGS;
                }
                if(option[4].getGlobalBounds().contains(mousePosition.x,mousePosition.y)){
                    if(m==0)
                        return EXIT_PROGRAM;
                    else
                        return END_GAME;
                }
            }
        }
        if(event.type == sf::Event::Closed){
                return EXIT_PROGRAM;
        }
        if(zmiana!=poprzednia||zmianap!=poprzedniap||changeSelect){
                changeSelect=0;
                poprzednia=zmiana;
                poprzedniap=zmianap;
                mainWindow.clear(sf::Color::White);

                mainWindow.draw(logo);
                if(addmenu==1)
                    drawLoadMenu();
                else if(addmenu==2)
                    drawSaveMenu();
                if(hotkeys)
                    enterControls();

                for(int i=0; i<5; i++)
                    mainWindow.draw(option[i]);
                mainWindow.display();
        }
        c++;
    }
    mainWindow.close();
    return 0;
}

void DrawHelper::updateDownItems(player *Player){
    for(int i=0;i<5;i++)
        left_gui_items[i].setTexture(p_i_spr[Player->getItem(i)->getId()]);
}

void DrawHelper::updateHpMp(player *Player,bool ishp){

}


void DrawHelper::setMap(mapp *mapl, player *Player){
    Eq_txt.loadFromFile("spr/eq.png");
    Eq_spr.setTexture(Eq_txt);
    DrawHelper::lmap=mapl;
    mainWindow.clear();
}
/*
void DrawHelper::drawBottom(){


}*/

void DrawHelper::drawPlayer(){

}

void DrawHelper::setGame(float RealX, float RealY){
    px =RealX;
    py =RealY;

    mainWindow.setView(kamera);
    for(int i=-map_start_y;i<map_start_y+1;i++){
        for(int j=-map_start_x;j<map_start_x+2;j++){
            for(int z=0;z<lmap->getH(px+j, py+i);z++){
                map_spr[j+map_start_x][i+map_start_y][z].setTexture(p_f_spr[lmap->getField(px+j,py+i,z)->getId()]);
                if(lmap->getItem(px+j,py+i,z)!=NULL){
                    //lmap->getItem(px+j,py+i,z)->sprite->setTexture(p_i_spr[lmap->getItem(px+j,py+i,z)->getId()]);
                    //item_spr[j+map_start_x][i+map_start_y][z].setTexture(p_i_spr[lmap->getItem(px+j,py+i,z)->getId()]);
                }
            }
        }
    }
}

void DrawHelper::updateItemsOnField(short x, short y){
    for(int z=0;z<lmap->getH(x, y);z++){
        map_spr[map_start_x][map_start_y][z].setTexture(p_f_spr[lmap->getField(x,y,z)->getId()]);
        if(lmap->getItem(x,y,z)!=NULL){
            lmap->getItem(x,y,z)->sprite->setTexture(p_i_spr[lmap->getItem(x,y,z)->getId()]);
            //item_spr[map_start_x][map_start_y][z].setTexture(p_i_spr[lmap->getItem(x,y,z)->getId()]);
        }
    }
}

void DrawHelper::drawGui(){
    mainWindow.draw(left_gui);
    for(int i=0;i<5;i++){
        gui_item_number.setString((char)(i+49));
        gui_item_number.setPosition(left_gui_items[i].getPosition().x+2,left_gui_items[i].getPosition().y+2);
        mainWindow.draw(left_gui_items[i]);
        mainWindow.draw(gui_item_number);
        mainWindow.draw(gui_selected_spr);
    }
    mainWindow.draw(Hp_bar_out);
    mainWindow.draw(Hp_bar);
    mainWindow.draw(Mp_bar_out);
    mainWindow.draw(Mp_bar);
    mainWindow.draw(hp_points);
    mainWindow.draw(mp_points);
}

void DrawHelper::drawMinimap(float RealX, float RealY){
        minimap.setCenter(RealX,RealY);
        mainWindow.setView(minimap);
        sf::RectangleShape rr(sf::Vector2f(812,812));
        rr.setPosition(RealX-406,RealY-406);
        rr.setOutlineColor(sf::Color(130,80,30));
        rr.setFillColor(sf::Color(190,190,190));
        rr.setOutlineThickness(10);
        mainWindow.draw(rr);
        sf::RectangleShape object(sf::Vector2f(20,20));
        sf::RectangleShape r(sf::Vector2f(20,20));
        for(int i=-20;i<20;i++)
            for(int j=-20;j<20;j++){
                r.setTexture(&p_f_spr[lmap->getFieldId(RealX+j,RealY+i,0)]);

                r.setPosition(RealX+j*20,RealY+i*20+0);
                mainWindow.draw(r);
            }

        object.setFillColor(sf::Color::Yellow);
        object.setPosition(RealX,RealY);
        mainWindow.draw(object);
        sf::View view = mainWindow.getView();
        view.setCenter(px,py);
        mainWindow.setView(kamera);
}

void DrawHelper::updatePlayer(float RealX, float RealY,int Pz){
        px = RealX;
        py = RealY;
        pz = Pz;


        sf::View view = mainWindow.getView();
        view.setCenter(RealX,RealY);
        mainWindow.setView(kamera);
        float pxx = RealX -px;
        float pyy = RealY -py;

        if(pxx==0||pyy==0){
            for(int i=-map_start_y;i<map_start_y+1;i++){
                for(int j=-map_start_x;j<map_start_x+2;j++){
                    for(int z=0;z<lmap->getH(px+j, py+i);z++){
                        map_spr[j+map_start_x][i+map_start_y][z].setTexture(p_f_spr[lmap->getField(px+j,py+i,z)->getId()]);
                        map_spr[j+map_start_x][i+map_start_y][z].setPosition((j+map_start_x-pxx)*64-32,(i+map_start_y-pyy-2)*64-z*4+Pz*4);
                        if(lmap->getItem(px+j,py+i,z)!=NULL){
                            //item_spr[j+map_start_x][i+map_start_y][z].setTexture(p_i_spr[lmap->getItem(px+j,py+i,z)->getId()]);

                            //item_spr[j+map_start_x][i+map_start_y][z].
                            lmap->getItem(px+j,py+i,z)->sprite->setPosition((j+map_start_x-pxx)*64-32,(i+map_start_y-pyy-2)*64-z*4+Pz*4);

                        }
                    }
                }
            }
        }
        //map_spr[10][6][0].setTexture(this->gui_selected_txt);
        /*for(int i=0;i<map_draw_y;i++)
            for(int j=0;j<map_draw_x;j++)
                for(int z=0;z<20;z++){
                    map_spr[j][i][z].setPosition((j-pxx)*64-32,(i-pyy-2)*64-z*4+Pz*4);
                    item_spr[j][i][z].setPosition((j-pxx)*64-32,(i-pyy-2)*64-z*4+Pz*4);
                }*/

}

void DrawHelper::drawMap(player* Player){
        mainWindow.clear(sf::Color::White);
        for(int i=-map_start_y;i<2;i++)
            for(int j=-map_start_x;j<map_start_x+2;j++){
                for(int z=0;z<lmap->getH(px+j, py+i);z++){
                    mainWindow.draw(map_spr[j+map_start_x][i+map_start_y][z]);
                    if(lmap->getItem(px+j,py+i,z)!=NULL){
                        //mainWindow.draw(item_spr[j+map_start_x][i+map_start_y][z]);
                        mainWindow.draw(*lmap->getItem(px+j,py+i,z)->sprite);
                    }
                }
            }
        mainWindow.draw(*Player->sprite);
        for(int i=-1;i<=1;i++)
            for(int z=pz;z<lmap->getH(px+i, py+1);z++){
                mainWindow.draw(map_spr[i+map_start_x][1+map_start_y][z]);
                if(lmap->getItem(px+i,py+1,z)!=NULL)
                    mainWindow.draw(*lmap->getItem(px+i,py+1,z)->sprite);;
            }
        for(int i=2;i<map_start_y+1;i++)
            for(int j=-map_start_x;j<map_start_x+2;j++){
                for(int z=0;z<lmap->getH(px+j, py+i);z++){
                    mainWindow.draw(map_spr[j+map_start_x][i+map_start_y][z]);
                    if(lmap->getItem(px+j,py+i,z)!=NULL){
                        //mainWindow.draw(item_spr[j+map_start_x][i+map_start_y][z]);
                        mainWindow.draw(*lmap->getItem(px+j,py+i,z)->sprite);
                    }
                }
            }
}

void DrawHelper::display(){
    mainWindow.display();
}

