#include "char.hpp"


Char_C::Char_C(int _x, int _y, bool playable) : Character(_x, _y, 'C', playable) {
    range = 5;
};
Char_C::Char_C(bool playable) : Character('C', playable) {
    range = 5;
};

void Char_C::showScope() {
    if (!playable) return;
    /*  Character C
            lanza granadas todas direcciones

          0 1 2 3 4 5 6
        0 . . . . . . .
        1 . . . . . . .
        2 . . . . c c c
        3 C . . . c c c
        4 . . . . c c c
        5 . . . . . . .
    */
    if (!targets.empty()) descope();
    for (int dy = y + act_scope.y - 1; dy <= y + act_scope.y + 1; dy++)
        for (int dx = x + act_scope.x - 1; dx <= x + act_scope.x + 1; dx++) {
            if (!(map->isOnMap(dx, dy))) continue;

            MAP_VALUES map_value = map->get_map(dx, dy);
            SCOPE_VALUES scope_value = map->get_scope(dx, dy);

            if (scope_value || map_value == MAP_WALL_0) continue;

            if (map_value == MAP_FLOOR_0 || map_value == MAP_VOID || map_value == MAP_SPAWN_BLUE || map_value == MAP_SPAWN_RED) {
                map->set_scope(dx, dy, SCOPE_ONGO);
                targets.push_back(sf::Vector2i(dx, dy));
            }
            else if (map_value == MAP_ALLY_0) {
                map->set_scope(dx, dy, SCOPE_ALLY);
                targets.push_back(sf::Vector2i(dx, dy));
            }
            else if (map_value == MAP_DUMMY_0 || map_value == MAP_ENEMY_0) {
                map->set_scope(dx, dy, SCOPE_HIT);
                targets.push_back(sf::Vector2i(dx, dy));
            };
        };

};


void Char_C::scope(int _x, int _y) {
    if (!playable || !map->isOnMap(act_scope.x + _x + x, act_scope.y + _y + y)) return;
    if (abs(act_scope.x + _x) >= range || abs(act_scope.y + _y) >= range) return;
    act_scope += sf::Vector2i(_x, _y);
    showScope();
};

void Char_C::descope() {
    if (!playable) return;
    int n_targets = targets.size();
    for (int i = 0; i < n_targets; i++) {
        map->set_scope(targets.back(), SCOPE_EMPTY);
        targets.pop_back();
    };
};

void Char_C::changeMovementMode() {
    movementMode = !movementMode;
    showScope();
};