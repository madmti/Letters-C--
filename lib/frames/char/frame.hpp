#ifndef Frame_char_h
#define Frame_char_h
#include "../abstract.hpp"

class CharFrame :public Frame {
private:

public:
    CharFrame();
    ~CharFrame();

    void draw(sf::RectangleShape _shape);
    void draw(sf::Text _shape);
    void draw(sf::Sprite _shape);
};

#endif