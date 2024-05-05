#ifndef Frame_h
#define Frame_h
#include "../types.hpp"

class Frame {
protected:
    sf::Vector2i pos;
    sf::Vector2i size;
    sf::Vector2f scale;
    sf::RenderTexture frame;
    bool valid;

    sf::RectangleShape formatShape(sf::RectangleShape _shape);
    sf::Text formatShape(sf::Text _shape);
    sf::Sprite formatShape(sf::Sprite _shape);

    void reSize(sf::Vector2i new_size);
    void rePos(sf::Vector2i new_pos);

public:
    Frame(sf::Vector2i pos, sf::Vector2i size);
    Frame(sf::Vector2i size);
    Frame();

    void clear();
    void display();
    void setConfig(sf::Vector2i pos, sf::Vector2i size);
    void setConfig(sf::Vector2i size);
    virtual void draw(sf::RectangleShape _shape) = 0;
    virtual void draw(sf::Text _shape) = 0;
    virtual void draw(sf::Sprite _shape) = 0;

    sf::Sprite getSprite();
};

#endif