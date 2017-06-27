#include "button.h"

button::button()
{
    //ctor
}
button::button(float x,float y,float w,float h,float o,sf::Color text_color,sf::Color fill_color,std::string name,sf::Font *font){
    thick=o;
    fillColor=fill_color;
    text = new sf::Text(name,*font,h*0.4);
    text->setColor(text_color);
    sf::Vector2f v = text->findCharacterPos(name.length());
    text->setPosition(x+(w-v.x)/2,y+h*0.3);

    border = new sf::RectangleShape(sf::Vector2f(w,h));
    border->setFillColor(fill_color);
    border->setPosition(x,y);
    border->setOutlineThickness(o);
    shadow = new sf::RectangleShape(sf::Vector2f(w+2*o,h));
    shadow->setPosition(x-o,y+o);
    int r,g,b;
    r = (fill_color.r-50)%255;
    g = (fill_color.g-50)%255;
    b = (fill_color.b-50)%255;
    border->setOutlineColor(sf::Color(r,g,b));
    shadow->setFillColor(sf::Color(r+50,g+50,b+50));
    t_shadow=0;
    isHover=1;
}

button::~button()
{
    //dtor
}

void button::setString(std::string name){
    text->setString(name);
    sf::Vector2f v = text->findCharacterPos(name.length());
    int x = border->getPosition().x;
    int y = border->getPosition().y;
    int w = border->getSize().x;
    int h = border->getSize().y;
    text->setPosition(x+(w-v.x)/2,y+h*0.3);
}

void button::setShadow(float th){
    t_shadow=th;
    shadow->setPosition(shadow->getPosition().x-t_shadow+1,shadow->getPosition().y);
    shadow->setSize(sf::Vector2f(shadow->getSize().x+(t_shadow-1)*2,shadow->getSize().y+th));
}

void button::setHover(bool is){
    isHover=is;
}
void button::resize(float x, float y, float w, float h){
    float o = border->getOutlineThickness();
    text->setCharacterSize(h*0.4);
    std::cout << x << " " << w << " " << std::endl;
    text->setPosition(0,0);
    sf::Vector2f v = text->findCharacterPos(text->getString().getSize());
    text->setPosition(x+(w-v.x)/2,y+h*0.3);

    border->setSize(sf::Vector2f(w,h));
    border->setPosition(x,y);
    shadow->setSize(sf::Vector2f(w+2*o,h+o));
    shadow->setPosition(x-o,y+o);
    setShadow(t_shadow);
}

sf::FloatRect button::bounds(){
    if(border->getOutlineThickness()>0)
        return border->getGlobalBounds();
    else
        return text->getGlobalBounds();
}

void button::draw(sf::RenderWindow *rw){
    rw->draw(*shadow);
    rw->draw(*border);
    rw->draw(*text);
}

void button::hover(){
    if(isHover){
        int r,g,b;
        r = (fillColor.r+50)%255;
        g = (fillColor.g+50)%255;
        b = (fillColor.b+50)%255;
        border->setFillColor(sf::Color(r,g,b));
        shadow->setPosition(shadow->getPosition().x-1,shadow->getPosition().y);
        shadow->setSize(sf::Vector2f(shadow->getSize().x+2,shadow->getSize().y+1));
    }
}

void button::not_hover(){
    if(isHover){
        border->setFillColor(fillColor);
        shadow->setPosition(shadow->getPosition().x+1,shadow->getPosition().y);
        shadow->setSize(sf::Vector2f(shadow->getSize().x-2,shadow->getSize().y-1));
    }
}
