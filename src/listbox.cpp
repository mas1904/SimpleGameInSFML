#include "listbox.h"
#include <iostream>
listbox::listbox()
{

}


listbox::listbox(float outline_thick, float x, float y, float w, float h, int fontSize, sf::Font *font){
    this->font=font;
    characterSize=fontSize;
    board.setOutlineThickness(outline_thick);
    board.setOutlineColor(sf::Color(150,150,150));
    board.setFillColor(sf::Color(100,100,100,0));
    board.setPosition(x,y);
    board.setSize(sf::Vector2f(w,h));
    selected_g.setSize(sf::Vector2f(w,characterSize));
    selected_g.setFillColor(sf::Color(0,0,0,120));
    selected_g.setOutlineThickness(outline_thick);
    selected_g.setOutlineColor(sf::Color(150,150,150));
    selected=-1;

    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
}

listbox::~listbox()
{
    //dtor
}

sf::FloatRect listbox::bounds(){
    //board.get
    return board.getGlobalBounds();
}

void listbox::resize(float x, float y, float w, float h, int fontSize){
    characterSize=fontSize;
    board.setPosition(x,y);
    board.setSize(sf::Vector2f(w,h));
    selected_g.setSize(sf::Vector2f(w,characterSize));
    if(items.size()>0)
        selected_g.setPosition(board.getPosition().x,board.getPosition().y+selected*characterSize);
    for(int i=0;i<items.size();i++)
        items[i]->setCharacterSize(characterSize);
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
}

void listbox::draw(sf::RenderWindow* win){
    win->draw(board);
    if(selected!=-1)
        win->draw(selected_g);
    for(int i=0;i<items.size();i++){
        items[i]->setPosition(x+0.02*w,y+i*characterSize-characterSize*0.1);
        win->draw(*items[i]);
    }
}

void listbox::select(float yy){
    int s=(yy-board.getPosition().y)/characterSize;

    if(s<items.size()){
        if(selected!=-1)
            items.at(selected)->setColor(sf::Color::Black);
        selected=s;
        selected_g.setPosition(board.getPosition().x,board.getPosition().y+selected*characterSize);
        items.at(selected)->setColor(sf::Color::White);
    }
}

std::string listbox::getSelected(){
    return items.at(listbox::selected)->getString();
}

void listbox::populate(std::string newitem){
    items.push_back(new sf::Text(newitem,*font,characterSize));
    items.at(items.size()-1)->setColor(sf::Color::Black);
}

void listbox::eraseAll(){
    items.erase(items.begin(),items.end());
}

void listbox::dropItem(int id){
    items.erase(items.begin()+id);
    if(id==items.size())selected--;
    else if(items.size()==0)
        selected=-1;
}

void listbox::dropItem(){
    if(selected>=0&&selected<items.size()){
        items.erase(items.begin()+selected);
        if(selected==items.size()){
            selected--;
            selected_g.setPosition(board.getPosition().x,board.getPosition().y+selected*characterSize);
        }
        else if(items.size()==0)
            selected=-1;
        if(selected!=-1)
            items.at(selected)->setColor(sf::Color::White);
    }
}

int listbox::getSize(){
    return items.size();
}
