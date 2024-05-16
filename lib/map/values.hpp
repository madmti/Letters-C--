#ifndef Values_h
#define Values_h
#include "../types.hpp"
enum ScopeValues {
    SCOPE_EMPTY = 0,
    SCOPE_TRAYECT = 1,
    SCOPE_ENEMY_HIT = 2,
    SCOPE_TEAM_HIT = 3,
};
/*
Voids: [ -11 --> -1 ]

Floors: [ 0 --> 12 ]

Walls: [ 13 --> 23 ]

Players: [ 24 --> 25 ]
*/
enum MapValues {
    MAP_CUSTOM_VOID_9 = -11,
    MAP_CUSTOM_VOID_8 = -10,
    MAP_CUSTOM_VOID_7 = -9,
    MAP_CUSTOM_VOID_6 = -8,
    MAP_CUSTOM_VOID_5 = -7,
    MAP_CUSTOM_VOID_4 = -6,
    MAP_CUSTOM_VOID_3 = -5,
    MAP_CUSTOM_VOID_2 = -4,
    MAP_CUSTOM_VOID_1 = -3,
    MAP_CUSTOM_VOID_0 = -2,
    MAP_VOID = -1,
    MAP_FLOOR = 0,
    MAP_SPAWN_BLUE = 1,
    MAP_SPAWN_RED = 2,
    MAP_CUSTOM_FLOOR_0 = 3,
    MAP_CUSTOM_FLOOR_1 = 4,
    MAP_CUSTOM_FLOOR_2 = 5,
    MAP_CUSTOM_FLOOR_3 = 6,
    MAP_CUSTOM_FLOOR_4 = 7,
    MAP_CUSTOM_FLOOR_5 = 8,
    MAP_CUSTOM_FLOOR_6 = 9,
    MAP_CUSTOM_FLOOR_7 = 10,
    MAP_CUSTOM_FLOOR_8 = 11,
    MAP_CUSTOM_FLOOR_9 = 12,
    MAP_WALL = 13,
    MAP_CUSTOM_WALL_0 = 14,
    MAP_CUSTOM_WALL_1 = 15,
    MAP_CUSTOM_WALL_2 = 16,
    MAP_CUSTOM_WALL_3 = 17,
    MAP_CUSTOM_WALL_4 = 18,
    MAP_CUSTOM_WALL_5 = 19,
    MAP_CUSTOM_WALL_6 = 20,
    MAP_CUSTOM_WALL_7 = 21,
    MAP_CUSTOM_WALL_8 = 22,
    MAP_CUSTOM_WALL_9 = 23,
    MAP_TEAM = 24,
    MAP_ENEMY = 25,
    MAP_NULL = 99,
};

enum BuildValues {
    BUILD_MAP_VOID = 'v',
    BUILD_MAP_CUSTOM_VOID_START = '{',
    BUILD_MAP_CUSTOM_VOID_END = '}',
    BUILD_MAP_FLOOR = 'f',
    BUILD_MAP_CUSTOM_FLOOR_START = '(',
    BUILD_MAP_CUSTOM_FLOOR_END = ')',
    BUILD_MAP_WALL = 'w',
    BUILD_MAP_CUSTOM_WALL_START = '[',
    BUILD_MAP_CUSTOM_WALL_END = ']',
    BUILD_MAP_SPAWN_BLUE = 'b',
    BUILD_MAP_SPAWN_RED = 'r',
    BUILD_MAP_CUSTOM_IDX_0 = '0',
    BUILD_MAP_CUSTOM_IDX_1 = '1',
    BUILD_MAP_CUSTOM_IDX_2 = '2',
    BUILD_MAP_CUSTOM_IDX_3 = '3',
    BUILD_MAP_CUSTOM_IDX_4 = '4',
    BUILD_MAP_CUSTOM_IDX_5 = '5',
    BUILD_MAP_CUSTOM_IDX_6 = '6',
    BUILD_MAP_CUSTOM_IDX_7 = '7',
    BUILD_MAP_CUSTOM_IDX_8 = '8',
    BUILD_MAP_CUSTOM_IDX_9 = '9',
    BUILD_MAP_NULL = 'n',
};

struct SpawnData {
    std::vector<sf::Vector2i> blue;
    std::vector<sf::Vector2i> red;
    int size;
};

struct MapMetaData {
    std::string map_name;
    SpawnData spawns;
    sf::Vector2i tile_size;
    sf::Vector2i map_size;
    bool completeData = false;
};

struct ScopeData {
    sf::Vector2i pos;
    ScopeValues val;
};

struct MapValuesData {
    std::vector<std::vector<MapValues>> map_values;
    std::vector<ScopeData> scope_values;
};
#endif