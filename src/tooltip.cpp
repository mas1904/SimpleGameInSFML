#include "tooltip.h"

tooltip::tooltip()
{
    //ctor
}

tooltip::~tooltip()
{
    //dtor
}

tooltip::tooltip(sf::Font * fnt, int characterSize){
    font=fnt;
    this->characterSize=characterSize;
    text.setCharacterSize(characterSize);
    AD.setCharacterSize(characterSize*0.8);
    DF.setCharacterSize(characterSize*0.8);
    board.setFillColor(sf::Color(40,40,40,200));
    board.setOutlineThickness(2);
    board.setOutlineColor(sf::Color(120,120,120));
    text.setFont(*font);
    AD.setFont(*font);
    DF.setFont(*font);

}
void tooltip::setHp(int hp){
    rc.setSize(sf::Vector2f(board.getSize().x*hp/100,board.getSize().y*0.05));
    rc.setFillColor(sf::Color((255 * (100 - hp))/100,(255*hp)/100,0));
}

void tooltip::setADP(int ad, int df){
    std::string ads = "AD: " + std::to_string(ad);
    std::string dfs = "DF: " + std::to_string(df);
    AD.setString(ads);
    DF.setString(dfs);
}

void tooltip::setText(std::string text){
    this->text.setString(text);
    sf::Vector2f v = this->text.findCharacterPos(text.length());
    board.setSize(sf::Vector2f(v.x+4-this->text.getPosition().x,v.y+4-this->text.getPosition().y+(2.6*this->text.getCharacterSize())));
}
void tooltip::setPosition(sf::Vector2i v){
    board.setPosition(v.x-board.getSize().x,v.y-board.getSize().y);
    text.setPosition(board.getPosition().x+2,board.getPosition().y+2);
    AD.setPosition(board.getPosition().x+2,board.getPosition().y+2+characterSize);
    DF.setPosition(board.getPosition().x+2,board.getPosition().y+4+1.6*characterSize);
    rc.setPosition(board.getPosition());
}
void tooltip::draw(sf::RenderWindow*w){
    w->draw(board);
    w->draw(text);
    w->draw(AD);
    w->draw(DF);
    w->draw(rc);
}
