#include "char.hpp"


Char_D::Char_D(int _x, int _y, bool playable) : Character(_x, _y, 'D', D_DMG, D_MAX_LIFE, playable) {

};
Char_D::Char_D(bool playable) : Character('D', D_DMG, D_MAX_LIFE, playable) {

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
Damage Char_D::doDamage() {
    Damage temp(dmg, damageIsPercent);
    return Damage(temp);
};