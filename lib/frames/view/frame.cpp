#include "frame.hpp"


ViewFrame::ViewFrame() :Frame() {

};
ViewFrame::~ViewFrame() {};


void ViewFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void ViewFrame::draw(sf::Text _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void ViewFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    frame.draw(_shape);
};

void ViewFrame::clear() {
    frame.clear(sf::Color::Black);
};