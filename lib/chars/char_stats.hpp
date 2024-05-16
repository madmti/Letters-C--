#ifndef Char_Stats_h
#define Char_Stats_h
#include "../types.hpp"

const int CHAR_LIFE_P = 100;

const float CHAR_DAMAGE_P = 50;

enum CharModes {
    MODE_DEAD = -1,
    MODE_STAND = 0,
    MODE_MOVEMENT = 1,
    MODE_ATACK = 2,
};

struct CharMetaData {
    sf::Vector2i pos;
    int id;
    char type;
    int team;
    CharModes mode;
    int life;
    int max_life;
    float damage;
};

#endif