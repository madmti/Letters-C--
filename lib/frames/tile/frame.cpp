#include "frame.hpp"

TileFrame::TileFrame() :Frame() {};
TileFrame::~TileFrame() {};


void TileFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    sf::RectangleShape shape = formatShape(_shape);
    frame.draw(shape);
};
void TileFrame::draw(sf::Text _shape) {
    if (!valid) return;
    sf::Text shape = formatShape(_shape);
    frame.draw(shape);
};
void TileFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    sf::Sprite shape = formatShape(_shape);
    frame.draw(shape);
};
