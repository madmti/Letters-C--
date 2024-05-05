#ifndef Frame_view_h
#define Frame_view_h
#include "../abstract.hpp"

class ViewFrame :public Frame {
private:


public:
    ViewFrame();
    ~ViewFrame();

    void clear();
    void draw(sf::RectangleShape _shape);
    void draw(sf::Text _shape);
    void draw(sf::Sprite _shape);

};

#endif