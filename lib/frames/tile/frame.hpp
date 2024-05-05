#ifndef Frame_tile_h
#define Frame_tile_h
#include "../abstract.hpp"

class TileFrame :public Frame {
private:
    float k;
public:
    TileFrame();
    ~TileFrame();

    void setSize(sf::Vector2i new_size);
    void zoomIn();
    void zoomOut();
    void move(int dx, int dy);

    void draw(sf::RectangleShape _shape);
    void draw(sf::Text _shape);
    void draw(sf::Sprite _shape);
};

#endif