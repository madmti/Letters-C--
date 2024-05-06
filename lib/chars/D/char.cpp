#include "char.hpp"


Char_D::Char_D(int _x, int _y, bool playable) : Character(_x, _y, 'D', playable) {

};
Char_D::Char_D(bool playable) : Character('D', playable) {

};

void Char_D::showScope() {
    if (!playable) return;

};

void Char_D::scope(int _x, int _y) {
    if (!playable) return;

};
void Char_D::descope() {
    if (!playable) return;

};
void Char_D::changeMovementMode() {
    movementMode = !movementMode;
};
