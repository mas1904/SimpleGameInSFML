#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#define MENU_ITEM 8

#define NUMBER_OF_CONTROLS 3
#define NUMBER_OD_OPTIONS 3

#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <dirent.h>
#include "mapp.h"
#include "player.h"
#include "common.h"
#include "button.h"
#include "listbox.h"
#include "tooltip.h"

#define map_draw_x 24
#define map_draw_y 16
#define map_start_x 10
#define map_start_y 7

class DrawHelper
{
    public:
        DrawHelper();
        sf::Vector2i dragpoint;
        void setMap(mapp*,player*);
        virtual ~DrawHelper();
        void setGame(float,float);
        void updatePlayer(float,float,int);
        void drawMap(player*);

        void drawMinimap(float,float);
        void drawItem(short, short, short);
        void drawField(short, short, short);
        void drawPlayer();
        void drawDraged(sf::Vector2i);
        void drawGui();

        void drawLoadMenu();
        void drawSaveMenu();

        void updateDownItems(player*);
        void updateHpMp(player*,bool);
        void refreshEq(player*);

        sf::Texture *loadSpr(bool item, int id);

        void saveConfig();

        void loadSaves();
        sf::RenderWindow *getWindow();
        int enterMenu(int);
        int enterInventory(player*);
        string enterLoad(int);
        void enterSettings();
        void enterControls();
        void resizeAll();
        void loadHotkeys();
        void display();
        void updateItemsOnField(short, short);
        void hoverEq(sf::Vector2i,player*);
        short drag(sf::Vector2i,player*);
        void undrag(sf::Vector2i,player*,short);
        void selectGuiItem(int);
        int getActions();
        void unselect(int);
        bool selectEqItem(int i);
        static void getKeyEvent(int&,bool&,bool&);
        void updateMP(short,short);
        void updateHP(short,short);
        void setSprite(player*);
    protected:
    private:
        bool dragging;
        bool isFullScreen;
        bool tip;
        bool eq_selected[25];
        int sizex;
        int sizey;
        int posx;
        int posy;
        int px;
        int py;
        int pz;
        bool eq;
        bool Eq_hover_bool;
        char Hotkeys_key[6];
        double sx;
        double sy;
        string file;
        sf::View kamera;
        sf::View minimap;
        sf::RenderTexture minim;

        sf::Texture Eq_txt;
        sf::Texture hover;
        sf::Texture left_gui_txt;
        sf::Texture gui_selected_txt;
        sf::Texture bars;
        sf::Texture logo_txt;

        sf::Sprite logo;
        sf::Sprite left_gui_items[5];
        sf::Sprite Eq_spr;
        sf::Sprite left_gui;
        sf::Sprite gui_selected_spr;
        sf::Sprite eq_selected_spr;

        int gui_selected_id;
        sf::Sprite player_spr;
        sf::Sprite map_spr[map_draw_x][map_draw_y][20];
        sf::Sprite draged;
        sf::Sprite Eq_hover;
        sf::Sprite Eq_item[25];
        sf::RectangleShape Hp_bar_out;
        sf::RectangleShape Mp_bar_out;
        sf::RectangleShape Hp_bar;
        sf::RectangleShape Mp_bar;

        sf::Text hp_points;
        sf::Text mp_points;

        sf::Text gui_item_number;
        sf::Text option[6];
        sf::Text title;
        sf::Font font;
        sf::Font official;
        sf::RenderWindow mainWindow;

        sf::RectangleShape menu_panel;
        listbox *list_save;

        sf::Text load_title;
        sf::Text save_title;
        sf::Text save_data;
        sf::Text hotkeys_title;
        sf::Text hotkeys_label[NUMBER_OF_CONTROLS];




        button *Przycisk[3];
        button *Hotkeys[NUMBER_OF_CONTROLS];

        tooltip *Item_tip;

        void odznacz(int,int);

        mapp *lmap;
        string big(string);

        map<int,sf::Texture>p_i_spr;
        map<int,sf::Texture>p_f_spr;
};

#endif // DRAWHELPER_H
