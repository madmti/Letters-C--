#include "./abstract.hpp"


void Character::move(int _x, int _y) {
    if (!playable || x + _x >= 32 || x + _x < 0 || y + _y < 0 || y + _y >= 18 || map->at(y + _y).at(x + _x) != 0) return;
    map->at(y).at(x) = MAP_FLOOR_0;
    x += _x;
    y += _y;
    map->at(y).at(x) = MAP_ALLY_0;
};

void Character::place() {
    map->at(y).at(x) = playable ? MAP_ALLY_0 : MAP_DUMMY_0;
};