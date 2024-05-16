#include "frame.hpp"

CharFrame::CharFrame() :Frame() {
    anim.clock = 0;
    anim.max_clock = 60;
};
CharFrame::CharFrame( int max_clock ) :Frame() {
    anim.clock = 0;
    anim.max_clock = max_clock;
};
CharFrame::~CharFrame() {};

void CharFrame::doClock() {
    anim.clock = (anim.clock + 1) % anim.max_clock;
};

void CharFrame::draw( sf::RectangleShape _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void CharFrame::draw( sf::Text _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void CharFrame::draw( sf::Sprite _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void CharFrame::clear() {
    frame.clear( sf::Color::Transparent );
};
void CharFrame::draw( CharMetaData* meta, sf::Color team_color, sf::Vector2i tile_size, sf::Font* font ) {
    pos = sf::Vector2i(
        meta->pos.x * tile_size.x,
        meta->pos.y * tile_size.y
    );
    int min_size = tile_size.x < tile_size.y ? tile_size.x : tile_size.y;

    sf::Text text( meta->type, *font );
    text.setPosition( 15, -3 );
    text.setFillColor( team_color );
    text.setCharacterSize( min_size );
    frame.draw( text );

    int life_percentaje = meta->max_life / meta->life;
    int division = life_percentaje * tile_size.x;

    sf::RectangleShape life_bar( sf::Vector2f( division, 4 ) );
    life_bar.setPosition( 15, 0 );
    life_bar.setFillColor( sf::Color::Green );
    frame.draw( life_bar );

    sf::RectangleShape damage_bar( sf::Vector2f( tile_size.x - division, 4 ) );
    damage_bar.setPosition( 15 + division, 0 );
    damage_bar.setFillColor( sf::Color::Red );
    frame.draw( damage_bar );

};