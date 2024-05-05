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

void Frame::clear() { frame.clear(); };
void Frame::display() { frame.display(); };

void Frame::setConfig(sf::Vector2i _pos, sf::Vector2i _size) {
    pos = _pos;
    if (!valid) {
        frame.create(_size.x, _size.y);
        size = _size;
        valid = true;
    }
    else reSize(_size);
};
void Frame::setConfig(sf::Vector2i _size) {
    if (!valid) {
        frame.create(_size.x, _size.y);
        size = _size;
        valid = true;
    }
    else reSize(_size);
};

sf::RectangleShape Frame::formatShape(sf::RectangleShape _shape) {
    sf::RectangleShape shape(_shape);
    shape.scale(scale);

    sf::Vector2f past_pos = shape.getPosition();
    sf::Vector2f new_pos = sf::Vector2f(
        past_pos.x * scale.x,
        past_pos.y * scale.y
    );
    shape.setPosition(new_pos);

    return sf::RectangleShape(shape);
};
sf::Text Frame::formatShape(sf::Text _shape) {
    sf::Text shape(_shape);
    shape.scale(scale);

    sf::Vector2f past_pos = shape.getPosition();
    sf::Vector2f new_pos = sf::Vector2f(
        past_pos.x * scale.x,
        past_pos.y * scale.y
    );
    shape.setPosition(new_pos);

    return sf::Text(shape);
};
sf::Sprite Frame::formatShape(sf::Sprite _shape) {
    sf::Sprite shape(_shape);
    shape.scale(scale);

    sf::Vector2f past_pos = shape.getPosition();
    sf::Vector2f new_pos = sf::Vector2f(
        past_pos.x * scale.x,
        past_pos.y * scale.y
    );
    shape.setPosition(new_pos);

    return sf::Sprite(shape);
};

void Frame::reSize(sf::Vector2i new_size) {
    scale = sf::Vector2f(
        (new_size.x / size.x) * scale.x,
        (new_size.y / size.y) * scale.y
    );
    size = new_size;
};

void Frame::rePos(sf::Vector2i new_pos) {
    pos = new_pos;
};

sf::Sprite Frame::getSprite() {
    display();
    sf::Sprite tempSprite(frame.getTexture(), sf::IntRect(sf::Vector2i(0, 0), size));
    tempSprite.setPosition(sf::Vector2f(pos));
    return sf::Sprite(tempSprite);
};