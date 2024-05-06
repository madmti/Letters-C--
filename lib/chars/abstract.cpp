#include "./abstract.hpp"


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
