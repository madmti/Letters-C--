#include "frame.hpp"

TileFrame::TileFrame() :Frame() {
    k = 1.2;
};
TileFrame::~TileFrame() {};


void TileFrame::setSize(sf::Vector2i new_size) { reSize(new_size); };

void TileFrame::draw(sf::RectangleShape _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void TileFrame::draw(sf::Text _shape) {
    if (!valid) return;
    frame.draw(_shape);
};
void TileFrame::draw(sf::Sprite _shape) {
    if (!valid) return;
    frame.draw(_shape);
};

void TileFrame::clear() {
    frame.clear(sf::Color::Black);
};

void TileFrame::zoomIn() {
    rePos(sf::Vector2i(
        pos.x - (size.x * scale.x * k - size.x * scale.x) / 2,
        pos.y - (size.y * scale.y * k - size.y * scale.y) / 2
    ));
    scale = sf::Vector2f(
        scale.x * k,
        scale.y * k
    );

};
void TileFrame::zoomOut() {
    rePos(sf::Vector2i(
        pos.x + (size.x * scale.x - size.x * scale.x / k) / 2,
        pos.y + (size.y * scale.y - size.y * scale.y / k) / 2
    ));
    scale = sf::Vector2f(
        scale.x / k,
        scale.y / k
    );
};

void TileFrame::move(int dx, int dy) {
    rePos(sf::Vector2i(
        pos.x + dx,
        pos.y + dy
    ));
};