#ifndef Frame_tile_h
#define Frame_tile_h
#include "../abstract.hpp"

class TileFrame :public Frame {
private:

public:
    TileFrame();
    ~TileFrame();

    void draw(sf::RectangleShape _shape);
    void draw(sf::Text _shape);
    void draw(sf::Sprite _shape);
};

#endif