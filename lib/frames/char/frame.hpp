#ifndef Frame_char_h
#define Frame_char_h
#include "../abstract.hpp"

class CharFrame :public Frame {
private:
    int clock;
    int deltaAnim;
public:
    CharFrame();
    ~CharFrame();

    void setSize(sf::Vector2i new_size);
    void setPos(sf::Vector2i new_pos);

    void clear();
    void draw(sf::RectangleShape _shape);
    void draw(sf::Text _shape);
    void draw(sf::Sprite _shape);
    void doClock();

    sf::RectangleShape transformShapeAnim(sf::RectangleShape _shape);
    sf::Text transformShapeAnim(sf::Text _shape);
    sf::Sprite transformShapeAnim(sf::Sprite _shape);
};

#endif