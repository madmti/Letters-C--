#include "abstract.hpp"

Frame::Frame(sf::Vector2i _pos, sf::Vector2i _size) : scale{ 1, 1 } {
    frame.create(_size.x, _size.y);
    pos = _pos;
    size = _size;
    valid = true;
};

Frame::Frame(sf::Vector2i _size) : scale{ 1, 1 }, pos{ 0, 0 } {
    frame.create(_size.x, _size.y);
    size = _size;
    valid = true;
};

Frame::Frame() : size{ 0, 0 }, scale{ 1, 1 }, pos{ 0, 0 } {
    valid = false;
};

void Frame::display() { frame.display(); };

void Frame::setConfig(sf::Vector2i _pos, sf::Vector2i _size) {
    pos = _pos;
    frame.create(_size.x, _size.y);
    size = _size;
    valid = true;
};
void Frame::setConfig(sf::Vector2i _size) {
    frame.create(_size.x, _size.y);
    size = _size;
    valid = true;
};

void Frame::setScale(float k) {
    scale = sf::Vector2f(k, k);
};

void Frame::scaleFrame(float k) {
    scale = sf::Vector2f(
        scale.x * k,
        scale.y * k
    );
};

void Frame::reSize(sf::Vector2i new_size) {
    scale = sf::Vector2f(
        (new_size.x / size.x) * scale.x,
        (new_size.y / size.y) * scale.y
    );
};

void Frame::rePos(sf::Vector2i new_pos) {
    pos = new_pos;
};

sf::Sprite Frame::getSprite() {
    display();
    sf::Sprite tempSprite(frame.getTexture(), sf::IntRect(sf::Vector2i(0, 0), size));
    tempSprite.scale(scale);
    tempSprite.setPosition(sf::Vector2f(pos));
    return sf::Sprite(tempSprite);
};