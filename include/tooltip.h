#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <SFML/Graphics.hpp>
#include <string>

class tooltip
{
    public:
        tooltip();
        tooltip(sf::Font *,int characterSize);
        virtual ~tooltip();
        void setText(std::string text);
        void setHp(int);
        void setADP(int,int);
        void setPosition(sf::Vector2i);
        void draw(sf::RenderWindow*);
    protected:

    private:
        sf::RectangleShape board;
        sf::Text text;
        sf::Text AD;
        sf::Text DF;
        sf::RectangleShape rc;
        sf::Font *font;
        int characterSize;
};

#endif // TOOLTIP_H
