#include "char.hpp"


Char_P::Char_P(int _x, int _y, bool playable) : Character(_x, _y, 'P', playable), act_scope{ 1, 0 } {
    range = 8;
};
Char_P::Char_P(bool playable) : Character('P', playable), act_scope{ 1, 0 } {
    range = 8;
};

void Char_P::showScope() {
    /*  Character P:
            Sniper a 4 direcciones

      0 1 2 3 4 5 |
    0 . . . . . . | . . | . .
    1 . . . . . . | . . | . .
    2 P - - - - p | - - P - -
    3 . . . . . . | . . | . .
    4 . . . . . . | . . | . .
    5 . . . . . . |
    */
    if (!playable) return;

    if (!targets.empty()) descope();
    for (sf::Vector2i delta(x, y); map->isOnMap(delta); delta += act_scope) {

        MAP_VALUES map_value = map->get_map(delta);
        SCOPE_VALUES scope_value = map->get_scope(delta);

        if (scope_value || delta.x == x && delta.y == y) continue;
        if (map_value == MAP_WALL_0 || abs(delta.x - x) >= range || abs(delta.y - y) >= range) break;

        if (map_value == MAP_FLOOR_0 || map_value == MAP_VOID || map_value == MAP_SPAWN_BLUE || map_value == MAP_SPAWN_RED) {
            map->set_scope(delta, SCOPE_ONGO);
            targets.push_back(sf::Vector2i(delta));
        }
        else if (map_value == MAP_ALLY_0) {
            map->set_scope(delta, SCOPE_ALLY);
            targets.push_back(sf::Vector2i(delta));
            break;
        }
        else if (map_value == MAP_DUMMY_0 || map_value == MAP_ENEMY_0) {
            map->set_scope(delta, SCOPE_HIT);
            targets.push_back(sf::Vector2i(delta));
            break;
        };
    };
};

void Char_P::scope(int _x, int _y) {
    if (!playable) return;
    act_scope = sf::Vector2i(_x, _y);
    showScope();
};

void Char_P::descope() {
    if (!playable) return;
    int n_targets = targets.size();
    for (int i = 0; i < n_targets; i++) {
        map->set_scope(targets.back(), SCOPE_EMPTY);
        targets.pop_back();
    };
};

void Char_P::changeMovementMode() {
    movementMode = !movementMode;
    showScope();
};

