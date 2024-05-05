#include "frame.hpp"

CharFrame::CharFrame() :Frame() {};
CharFrame::~CharFrame() {};


void CharFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void CharFrame::draw(sf::Text _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void CharFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
