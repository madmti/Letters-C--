#include "frame.hpp"


ViewFrame::ViewFrame() :Frame() {

};
ViewFrame::~ViewFrame() {};


void ViewFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    sf::RectangleShape shape = formatShape(_shape);
    frame.draw(shape);
};
void ViewFrame::draw(sf::Text _shape) {
    if (!valid) return;
    sf::Text shape = formatShape(_shape);
    frame.draw(shape);
};
void ViewFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    sf::Sprite shape = formatShape(_shape);
    frame.draw(shape);
};