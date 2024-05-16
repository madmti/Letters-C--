#ifndef Frame_char_h
#define Frame_char_h
#include "../abstract.hpp"
#include "../../chars/char_stats.hpp"

struct CharAnimData {
    int clock;
    int max_clock;
};

class CharFrame :public Frame {
private:
    CharAnimData anim;

public:
    CharFrame();
    CharFrame( int max_clock );
    ~CharFrame();

    void draw( sf::RectangleShape _shape );
    void draw( sf::Text _shape );
    void draw( sf::Sprite _shape );
    void draw( CharMetaData* meta, sf::Color team_color, sf::Vector2i tile_size, sf::Font* font );
    void clear();
    void doClock();

};

#endif