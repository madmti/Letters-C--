#include "frame.hpp"

CharFrame::CharFrame() :Frame() {
    clock = 0;
    deltaAnim = 1;
};
CharFrame::~CharFrame() {};


void CharFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    frame.draw(transformShapeAnim(_shape));
    doClock();
};
void CharFrame::draw(sf::Text _shape) {
    if (!valid) return;
    frame.draw(transformShapeAnim(_shape));
    doClock();
};
void CharFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    frame.draw(transformShapeAnim(_shape));
    doClock();
};

sf::RectangleShape CharFrame::transformShapeAnim(sf::RectangleShape _shape) {
    sf::RectangleShape shape(_shape);
    shape.move(0, deltaAnim * 2);
    return sf::RectangleShape(shape);
};
sf::Text CharFrame::transformShapeAnim(sf::Text _shape) {
    sf::Text shape(_shape);
    shape.move(0, deltaAnim * 2);
    return sf::Text(shape);
};
sf::Sprite CharFrame::transformShapeAnim(sf::Sprite _shape) {
    sf::Sprite shape(_shape);
    shape.move(0, deltaAnim * 2);
    return sf::Sprite(shape);
};

void CharFrame::doClock() {
    clock = (clock + 1) % 120;
    if (clock % 120 == 0) deltaAnim *= -1;
};

void CharFrame::clear() {
    frame.clear(sf::Color::Transparent);
};

void CharFrame::setSize(sf::Vector2i new_size) { reSize(new_size); };
void CharFrame::setPos(sf::Vector2i new_pos) { rePos(new_pos); };