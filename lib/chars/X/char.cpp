#include "char.hpp"


Char_X::Char_X(int _x, int _y, bool playable) : Character(_x, _y, 'X', playable), dirs{ sf::Vector2i(1,1), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1), sf::Vector2i(1, -1) } {
    idx_dirs = 0;
    range = 10;
    max_bounces = 3;
    bounces = 0;
};
Char_X::Char_X(bool playable) : Character('X', playable), dirs{ sf::Vector2i(1,1), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1), sf::Vector2i(1, -1) } {
    idx_dirs = 0;
    range = 10;
    max_bounces = 3;
    bounces = 0;
};

void Char_X::showScope() {
    if (!playable) return;

    if (!targets.empty()) descope();
    sf::Vector2i dir = dirs[idx_dirs];

    for (sf::Vector2i delta(x, y); map->isOnMap(delta); delta += dir) {
        MAP_VALUES map_value = map->get_map(delta);
        SCOPE_VALUES scope_value = map->get_scope(delta);

        if (delta.x == x && delta.y == y) continue;
        if (map_value == MAP_WALL_0 || targets.size() >= range || bounces > max_bounces) break;

        // check pos

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

        // check bounce
        sf::Vector2i next(delta + dir);
        if (!map->isOnMap(next)) continue;

        MAP_VALUES adjacentX_value = map->get_map(next.x, delta.y);
        MAP_VALUES adjacentY_value = map->get_map(delta.x, next.y);

        bool xReflex = adjacentX_value == MAP_WALL_0;
        bool yReflex = adjacentY_value == MAP_WALL_0;

        if (!xReflex && !yReflex) continue;

        dir = sf::Vector2i(
            dir.x - dir.x * 2 * xReflex,
            dir.y - dir.y * 2 * yReflex
        );
        bounces++;
    };

};

void Char_X::scope(int _x, int _y) {
    if (!playable || _y) return;
    if (_x < 0 && idx_dirs == 0) idx_dirs = dirs.size() - 1;
    else idx_dirs = _x < 0 ? idx_dirs - 1 : (idx_dirs + 1) % dirs.size();
    showScope();
};
void Char_X::descope() {
    if (!playable) return;
    bounces = 0;
    int n_targets = targets.size();
    for (int i = 0; i < n_targets; i++) {
        map->set_scope(targets.back(), SCOPE_EMPTY);
        targets.pop_back();
    };
};

void Char_X::changeMovementMode() {
    movementMode = !movementMode;
    showScope();
};
