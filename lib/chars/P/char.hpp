#ifndef Character_P_h
#define Character_P_h
#include "../abstract.hpp"

class Char_P :public Character {
private:

public:
    Char_P( sf::Vector2i pos, int id, char type, int team, int life, int max_life, float damage );
    Char_P();
    ~Char_P();
};

#endif