#include "GameHelper.h"

GameHelper::GameHelper()
{
    //ctor
    dh = new DrawHelper();
    mp = new MapHelper(dh);
    recipments = mp->recip_load();
    recipments->showAll();

}

GameHelper::~GameHelper()
{
    //dtor
}
void GameHelper::enterMenu(){
    string file;
    int option=0;
    int exit=0;
    while(exit!=1){
        option = dh->enterMenu(0);
        if(option==START_GAME)
            exit = loadMap("../basic");
        else if(option==ENTER_LOAD_MENU){
            file=dh->enterLoad(0);
            if(file!="")
                exit = loadMap(file);
        }
        else if(option==EXIT_PROGRAM)
            exit=1;
    }
}

void GameHelper::enterInventory(){
    dh->enterInventory(Player);
}

int GameHelper::enterGameMenu(){
    string file;
    int option=0;
    bool exit=0;
    while(!exit){
        option = dh->enterMenu(1);
        if(option==RETURN_GAME)
            exit=1;
        else if(option==ENTER_LOAD_MENU){
            file=dh->enterLoad(0);
            if(file!="")
                loadMap(file);
        }
        else if(option==ENTER_SAVE_MENU){
            file=dh->enterLoad(1);
            if(file!="")
                saveMap(file);
        }
        else if(option==END_GAME)
            return 2;
    }
    return 0;
}

bool GameHelper::exitProgram(){
    return 1;
}

int GameHelper::loadMap(string name){
    Player = new player;
    lmap = new mapp;
    string n="saves/";
    cout << n << endl;
    n+=name;
/*
    for(int i=0;i<1000;i++)
        for(int j=0;j<1000;j++){
            lmap->setField(j,i,0,1);
            lmap->setH(j,i,1);
        }
    Player->set_pos(500,500,0);
    mp->map_saver("nowy",lmap,Player);
*/
    lmap = mp->map_loader(n, Player);
    dh->setMap(lmap,Player);
    int exit;
    exit = startGame();
    return exit;
}

void GameHelper::saveMap(string name){
    string n="saves/";
    n+=name;
    mp->map_saver(n,lmap,Player);
}

void GameHelper::build(int selected){
    int x = Player->getX();
    int y = Player->getY();
    int krl = x+Player->getKRL();
    int kud = y+Player->getKUD();
    item * i_seleced= Player->getItem(selected);
    item * top =lmap->getTopItem(krl,kud);
    int orient;
    if(Player->getKUD())
        orient = 0;
    else orient = 1;


    if(!i_seleced->getBuildType(orient)){
        if(top==NULL){
            lmap->setField(krl,kud,lmap->getH(krl,kud),Player->getItem(selected)->getBuildId(orient));
            Player->throw_item(selected);
            lmap->addH(krl,kud);
        } else if(!top->isPickable()&&lmap->getH(krl,kud)<20){
            lmap->setField(krl,kud,lmap->getH(krl,kud),Player->getItem(selected)->getBuildId(orient));
            Player->throw_item(selected);
            lmap->addH(krl,kud);
        }
    } else {
        if(top==NULL){
            lmap->addH(krl,kud);
            lmap->place_item(krl,kud,i_seleced->getBuildId(orient),1);
            Player->throw_item(selected);
        } else if(!top->isPickable()&&lmap->getH(krl,kud)<20) {
            lmap->addH(krl,kud);
            lmap->place_item(krl,kud,i_seleced->getBuildId(orient),1);
            Player->throw_item(selected);
        }
    }
    dh->updateDownItems(Player);
}

void GameHelper::mine(int selected){
    int x = Player->getX();
    int y = Player->getY();
    int krl = x+Player->getKRL();
    int kud = y+Player->getKUD();
    int z = Player->getZ();
    float cc=1;
    item *use_item = Player->getItem(selected);
    item *top = lmap->getTopItem(krl,kud);
    if(use_item->getId()!=0){
        cc=use_item->getAD()/4;
        if(top!=NULL)
            if(use_item->getType()-top->getType())
                cc*=2;
    }
    if(cc<1)
        cc=1;
    it_C tmp[(int)cc];
    if(top!=NULL){
        for(int i=0;i<cc;i++)
            tmp[i] = top->mine(1);
        if(top->getHp()<0){
            int iddd = top->getDestroyItem();
            lmap->takeItem(krl,kud,z);
            if(iddd!=0){
                lmap->place_item(krl,kud,iddd,1);
            }
        }
    }
    else{
        for(int i=0;i<cc;i++)
            tmp[0] = {lmap->getField(krl,kud,0)->mine(),1};
    }
    if(tmp[0].id!=0){
        if(use_item->getId()!=0){
            use_item->setHp(Player->getItem(selected)->getHp()-2);
            if(use_item->getHp()<=0){
                Player->throw_item(selected);
                dh->updateDownItems(Player);
            }
        }
        for(int i=0;i<cc;i++)
            if(Player->getC_items()>0){
                Player->add_item(lmap->getPrItem(tmp[i].id),tmp[i].c);
                dh->updateDownItems(Player);
            }
            else if(lmap->getH(x,y)<20){
                lmap->place_item(x,y,tmp[i].id,tmp[i].c);
                Player->setZ(lmap->getH(Player->getX(),Player->getY()));
            }
    }
}

bool GameHelper::blocking(int rl, int kd){
    int x = Player->getRealX()+rl;
    int y = Player->getRealY()+kd;
    if(lmap->getTopItem(x,y)!=NULL)
        if(lmap->getTopItem(x,y)->isBlockable())
            return false;
    if(lmap->getH(x,y)-Player->getZ()>6)
        return false;
    if(lmap->getField(x,y,lmap->getH(x,y)-1)->getType()==2)
        return false;
    return true;
}

int GameHelper::startGame(){
    int exit=0;
    int action=0;
    sf::RenderWindow *mainWindow=dh->getWindow();
    float delta;
    sf::Time lastUpdate = sf::Time::Zero;
    item *tmpi;
	sf::Clock time;

    list<int> selected;
    bool eq=false;
    int spr=0;
    short draged=-1;
    int selected_gui=0;
    bool do_up=0;
    bool lctrl=0;
    sf::Vector2i mousePosition = sf::Mouse::getPosition( *mainWindow );
    dh->updateDownItems(Player);

    /*
    lmap->place_item(508,504,0,7,1);
    lmap->place_item(509,504,0,8,1);
    lmap->place_item(508,505,0,9,1);
    lmap->place_item(509,505,0,10,1);

    lmap->place_item(509,500,0,11,1);

    lmap->place_item(513,500,0,12,1);*/
    //lmap->addH(508,504);
    //lmap->addH(509,504);
    //lmap->addH(508,505);
    //lmap->addH(509,505);
    Player->setHP(50);
    Player->setMP(80);
    dh->setSprite(Player);
    dh->setGame(Player->getRealX(),Player->getRealY());
    dh->updateHP(Player->getHP(),Player->getMaxHP());
    dh->updateMP(Player->getMP(),Player->getMaxMP());
    int noaction=0;


    while(mainWindow->isOpen()&&exit==0){
        sf::Event event;
        while(mainWindow->pollEvent(event)){
            if(event.type == sf::Event::Closed)
                exit=1;
            if(event.type == sf::Event::KeyPressed&&lctrl){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    Player->setKRL(-1);
                    do_up=true;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    Player->setKRL(1);
                    do_up=true;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    Player->setKUD(-1);
                    do_up=true;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    Player->setKUD(1);
                    do_up=true;
                }
            } else if(event.type == sf::Event::KeyPressed&&event.key.code==(sf::Keyboard::LControl)){
                lctrl=1;
            } else if(event.type == sf::Event::KeyReleased&&event.key.code==(sf::Keyboard::LControl)){
                lctrl=0;
            } else if(lctrl==0){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    if(blocking(-1,0))
                        Player->move(-1,0,0);
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    if(blocking(1,0))
                        Player->move(1,0,0);
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    if(blocking(0,-1))
                        Player->move(0,-1,0);
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    if(blocking(0,1))
                        Player->move(0,1,0);
                }
                else if(event.type==sf::Event::KeyReleased&&event.key.code==(sf::Keyboard::T)){   //TAKE
                    tmpi = lmap->getItem(Player->getX()+Player->getKRL(),Player->getY()+Player->getKUD(),lmap->getH(Player->getX()+Player->getKRL(),Player->getY()+Player->getKUD())-1 );
                    if(tmpi!=NULL && tmpi->isPickable()==true){
                        if(Player->getC_items()>0){
                            Player->add_item(tmpi);
                            lmap->takeItem(Player->getX()+Player->getKRL(),Player->getY()+Player->getKUD(),Player->getZ());
                            dh->updateDownItems(Player);
                        }
                    }
            } else if(event.type==sf::Event::KeyReleased&&event.key.code==(sf::Keyboard::E)){    //USE

                if(Player->getItem(selected_gui)->isBuild()){
                    build(selected_gui);
                } else {
                    mine(selected_gui);
                }
                dh->updatePlayer(Player->getRealX(),Player->getRealY(),Player->getZ());
            } else if(event.type==sf::Event::KeyReleased&&event.key.code==(sf::Keyboard::I)){ //EQ
                    eq==0?eq=1:eq=0;
            } else if(event.type==sf::Event::KeyReleased&&event.key.code==(sf::Keyboard::M)){  //MAP

            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){ //ENTER GAME MENU
                    selected_gui=0;
                    dh->selectGuiItem(0);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){ //ENTER GAME MENU
                    selected_gui=1;
                    dh->selectGuiItem(1);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){ //ENTER GAME MENU
                    selected_gui=2;
                    dh->selectGuiItem(2);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){ //ENTER GAME MENU
                    selected_gui=3;
                    dh->selectGuiItem(3);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){ //ENTER GAME MENU
                    selected_gui=4;
                    dh->selectGuiItem(4);
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ //ENTER GAME MENU
                    exit = enterGameMenu();
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                  //  dh->playerAttack();
                  //  if(lmap->Monster(Player->getX()+Player->getKRL(),Player->getY()+Player->getKUD(),Player->getZ()))
                  //      lmap->Monster(Player->getX()+Player->getKRL(),Player->getY()+Player->getKUD(),Player->getZ())->getHitted(Player->getAd());
            }
          }
            if(eq){
                if(event.type == sf::Event::MouseMoved){
                    mousePosition = sf::Mouse::getPosition( *mainWindow );
                    mousePosition.x*=1.0/((double)(mainWindow->getSize().x)/1280);
                    mousePosition.y*=1.0/((double)(mainWindow->getSize().y)/720);
                    dh->hoverEq(mousePosition,Player);
                }
                if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left){

                    draged = dh->drag(mousePosition,Player);
                }
                if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right){
                    if(selected.size()>0){
                        list<int> l;
                        for(auto& x: selected){
                            l.push_back(Player->getItem(x)->getId());
                        }
                        list<it_C> itc = recipments->getItem(&l);
                        if(itc.size()>0){
                            if(Player->getC_items()+20-lmap->getH(Player->getX(),Player->getY())-selected.size()+itc.size()>0){
                                for(auto& x: selected){
                                    Player->throw_item(x);
                                    dh->unselect(x);
                                }
                                for(auto& x: itc){
                                    if(Player->getC_items()>0){
                                        Player->add_item(lmap->getPrItem(x.id),x.c);
                                        dh->updateDownItems(Player);
                                    }
                                    else {
                                        lmap->place_item(Player->getX(),Player->getY(),x.id,x.c);
                                        dh->updateItemsOnField(Player->getX(),Player->getY());
                                        Player->setZ(lmap->getH(Player->getX(),Player->getY()));
                                        dh->updatePlayer(Player->getRealX(),Player->getRealY(),Player->getZ());
                                    }
                                }
                                selected.clear();
                            }
                        }
                    }
                }
                if(event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left){
                    if(draged>=0){
                        short dd = dh->drag(mousePosition,Player);
                        if(draged!=dd&&dd>=0){
                            Player->move_item(draged,dd);
                            dh->unselect(draged);
                            dh->updateDownItems(Player);
                        } else {
                            if(dh->selectEqItem(draged))
                                selected.push_back(draged);
                            else
                                selected.remove(draged);
                        }
                        if(dd==-1){
                            if(lmap->getH(Player->getX(),Player->getY())<20){
                                lmap->place_item(Player->getX(),Player->getY(),*Player->getItem(draged));
                                Player->throw_item(draged);
                                dh->unselect(draged);
                                Player->setZ(lmap->getH(Player->getX(),Player->getY()));

                                dh->updateItemsOnField(Player->getX(),Player->getY());
                                dh->updateDownItems(Player);
                                dh->updatePlayer(Player->getRealX(),Player->getRealY(),Player->getZ());
                                selected.remove(draged);

                            }
                        }
                        draged=-1;
                    }
                }
            }

        }
        delta = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
        if(Player->update(delta)||do_up){
            do_up=false;
            if(Player->getKRL()==1) spr=11;
            else if(Player->getKRL()==-1) spr=9;
            else if(Player->getKUD()==-1) spr=8;
            else if(Player->getKUD()==1) spr=10;
            Player->setZ(lmap->getH(Player->getX(),Player->getY()));
            Player->setSprite(spr);

            dh->updatePlayer(Player->getRealX(),Player->getRealY(),Player->getZ());
        } else if(++noaction==3){
            Player->setSprite(0,spr);
            noaction=0;
        }
        lastUpdate = time.getElapsedTime();

        dh->drawMap(Player);
        dh->drawGui();
        if(eq)
            dh->enterInventory(Player);
        dh->drawMinimap(Player->getRealX(),Player->getRealY());
        dh->display();

    }

    return exit;

   /* while(exit!=1){
        /*if(dh->event.key.code == sf::Keyboard::M)
            cout<< "aaaaa" << endl;
        clock.restart().asMilliseconds();*/
        /*dh->move(0,0,0,Player);
    }*/
}
