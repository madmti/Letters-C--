#include "class.hpp"

Training::Training( std::string _id ) : View( _id ) {
    req_keys = std::vector<Key>{

    };
    loadMap();
};
Training::~Training() {};

void Training::loadMap() {
    std::string map_name = "dust_0";
    map.build_map( map_name );
    MapMetaData map_meta = map.getMetaData();
    CharMetaData char_meta;
    char_meta.damage = 0;
    char_meta.id = 0;
    char_meta.life = 10;
    char_meta.max_life = 10;
    char_meta.mode = CharModes::MODE_MOVEMENT;
    char_meta.pos = sf::Vector2i( 5, 5 );
    char_meta.team = 0;
    char_meta.type = 'P';

    p.setConfig( char_meta );
    p_f.setConfig( map_meta.tile_size );
};

void Training::clear() {
    p_f.clear();

    map.clear();
    frame.clear();
};

void Training::display() {
    display_Map();
    display_Stats();
    frame.display();
};

void Training::display_Stats() {
    // TeamManager dibuja el char seleccionado sobre GameManager
    // GameManager dibuja las stats
};

void Training::display_Map() {
    // TeamManager dibuja encima de map los Sprites de los chars
    map.showOutLines( sf::Color::Black, sf::Color::White );

    CharMetaData* char_meta = p.getMetaData();
    MapMetaData map_meta = map.getMetaData();

    p_f.draw( char_meta, sf::Color::Blue, map_meta.tile_size, &config->theme.FONT );

    map.draw( p_f.getSprite() );

    frame.draw( map.getFrame() );
};

ViewRequest Training::capture( Key k ) {

    return ViewRequest( false );
};