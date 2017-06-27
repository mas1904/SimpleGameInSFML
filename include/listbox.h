#ifndef LISTBOX_H
#define LISTBOX_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class listbox
{
    public:
        listbox();
        listbox(float outline_thick, float x, float y, float w, float h, int fontSize, sf::Font *font);
        virtual ~listbox();
        sf::FloatRect bounds();
        void draw(sf::RenderWindow*);
        void select(float y);
        std::string getSelected();
        void populate(std::string);
        void dropItem(int id);
        void dropItem();
        void eraseAll();
        void resize(float,float,float,float,int);
        int getSize();
    protected:

    private:
        int x, y, w, h;
        int characterSize;
        sf::Font *font;
        std::vector<sf::Text*> items;
        sf::RectangleShape selected_g;
        sf::RectangleShape board;
        int selected;

};

#endif // LISTBOX_H
