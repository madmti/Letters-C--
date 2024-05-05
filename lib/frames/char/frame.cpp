#include "frame.hpp"

CharFrame::CharFrame() :Frame() {};
CharFrame::~CharFrame() {};


void CharFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    sf::RectangleShape shape = formatShape(_shape);
    frame.draw(shape);
};
void CharFrame::draw(sf::Text _shape) {
    if (!valid) return;
    sf::Text shape = formatShape(_shape);
    frame.draw(shape);
};
void CharFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    sf::Sprite shape = formatShape(_shape);
    frame.draw(shape);
};
