#include "char.hpp"


Char_P::Char_P(int _x, int _y, bool playable) : Character(_x, _y, 'P', playable), act_scope{ 1, 0 } {
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
    for (sf::Vector2i delta(x, y);
        0 <= delta.x && delta.x < map->at(0).size() && 0 <= delta.y && delta.y < map->size();
        delta += act_scope) {

        int map_value = map->at(delta.y).at(delta.x);
        int scope_value = scope_map->at(delta.y).at(delta.x);

        if (scope_value || delta.x == x && delta.y == y) continue;
        if (map_value == MAP_WALL_0 || abs(delta.x - x) >= range || abs(delta.y - y) >= range) break;

        if (map_value == MAP_FLOOR_0) {
            scope_map->at(delta.y).at(delta.x) = 1;
            targets.push_back(sf::Vector2i(delta));
        }
        else if (map_value == MAP_ALLY_0) {
            scope_map->at(delta.y).at(delta.x) = SCOPE_ALLY;
            targets.push_back(sf::Vector2i(delta));
            break;
        }
        else if (map_value == MAP_DUMMY_0 || map_value == MAP_ENEMY_0) {
            scope_map->at(delta.y).at(delta.x) = SCOPE_HIT;
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
        sf::Vector2i target = targets.back();
        scope_map->at(target.y).at(target.x) = SCOPE_EMPTY;
        targets.pop_back();
    };
};

void Char_P::changeMovementMode() {
    movementMode = !movementMode;
    showScope();
};