#include "./abstract.hpp"

Character::Character(char _p, float _dmg, int _max_life, bool _playable) : max_life{ abs(_max_life) } {
    p = _p;
    playable = _playable;
    movementMode = true;
    life = max_life;
    dmg = _dmg;
    damageIsPercent = 0 < _dmg && _dmg < 1;
};
Character::Character(int _x, int _y, char _p, float _dmg, int _max_life, bool _playable) :max_life{ abs(_max_life) } {
    x = _x;
    y = _y;
    p = _p;
    movementMode = true;
    playable = _playable;
    life = max_life;
    dmg = _dmg;
    damageIsPercent = 0 < _dmg && _dmg < 1;
};

void Character::move(int _x, int _y) {
    if (!playable || !map->isOnMap(x + _x, y + _y)) return;
    MAP_VALUES val = map->get_map(x + _x, y + _y);
    if (val != MAP_FLOOR_0 && val != MAP_SPAWN_BLUE && val != MAP_SPAWN_RED) return;
    map->set_map(x, y, MAP_FLOOR_0);
    x += _x;
    y += _y;
    map->set_map(x, y, MAP_ALLY_0);
};

void Character::place() {
    MAP_VALUES val = playable ? MAP_ALLY_0 : MAP_DUMMY_0;
    map->set_map(x, y, val);
};

void Character::recvDamage(float damage) {
    if (damage >= life) life = 0;
    else life -= (int)damage;
};
void Character::recvDamage_perCent(float damage) {
    int real_damage = max_life * damage;
    recvDamage(real_damage);
};