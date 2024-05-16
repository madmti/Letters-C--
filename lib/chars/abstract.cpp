#include "abstract.hpp"

Character::Character( sf::Vector2i pos, int id, char type, int team, int life, int max_life, float damage ) {
    meta.pos = pos;
    meta.id = id;
    meta.life = life;
    meta.max_life = max_life;
    meta.mode = CharModes::MODE_MOVEMENT;
    meta.team = team;
    meta.type = type;
    meta.damage = damage;
};
Character::Character() {};
Character::~Character() {};

void Character::setConfig( CharMetaData _meta) {
    meta = _meta;
};

void Character::setPos( sf::Vector2i pos ) {
    meta.pos = pos;
};

CharMetaData* Character::getMetaData() {
    return &meta;
};