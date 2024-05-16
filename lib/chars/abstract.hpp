#ifndef Character_h
#define Character_h
#include "./char_stats.hpp"

class Character {
protected:
    CharMetaData meta;

public:
    Character( sf::Vector2i pos, int id, char type, int team, int life, int max_life, float damage );
    Character();
    ~Character();

    void setConfig( CharMetaData _meta );

    void setPos( sf::Vector2i pos );

    CharMetaData* getMetaData();
};

#endif