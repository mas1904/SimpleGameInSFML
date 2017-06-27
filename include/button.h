#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class button
{
    public:
        button();
        button(float x,float y,float w,float h,float outline,sf::Color text_color,sf::Color fill_color,std::string name,sf::Font* font);
        virtual ~button();
        sf::FloatRect bounds();
        void draw(sf::RenderWindow*);
        void hover();
        void not_hover();
        void setHover(bool yes);
        void setShadow(float thick);
        void setString(std::string);
        void resize(float,float,float,float);
    protected:

    private:
        bool isHover;
        sf::Text *text;
        sf::RectangleShape *border;
        sf::RectangleShape *shadow;
        sf::Color fillColor;
        sf::Color outlineColor;
        float thick;
        float t_shadow;
};

#endif // BUTTON_H
