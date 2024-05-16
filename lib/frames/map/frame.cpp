#include "frame.hpp"

MapFrame::MapFrame( std::string map_name ) :Frame() {
    valid = importMapTexture( map_name );
    outlineThickness = 2;
};
MapFrame::MapFrame() :Frame() {
    outlineThickness = 2;
};
MapFrame::~MapFrame() {};

void MapFrame::makeNull() {
    valid = false;
    pos = sf::Vector2i( 0, 0 );
    size = sf::Vector2i( 0, 0 );
    scale = sf::Vector2f( 0, 0 );
    frame.clear( sf::Color::Transparent );
};

bool MapFrame::buildMapTexture( std::map<MapValues, sf::Texture*> textures, std::vector<std::vector<MapValues>> map_values, sf::Vector2i map_size, sf::Vector2i tile_size, std::string map_name ) {
    sf::Vector2i texture_size = sf::Vector2i(
        map_size.x * (tile_size.x + outlineThickness),
        map_size.y * (tile_size.y + outlineThickness)
    );

    sf::RenderTexture tempMapTexture;
    tempMapTexture.create( texture_size.x, texture_size.y );
    tempMapTexture.clear( sf::Color::Transparent );
    for (int y = 0; y < map_size.y; y++) for (int x = 0; x < map_size.x; x++) {
        if (textures.count( map_values.at( y ).at( x ) ) == 0) continue;
        sf::Texture* tile_texture = textures.at( map_values.at( y ).at( x ) );
        if (tile_texture == nullptr) continue;
        sf::Sprite tile_sprite( *tile_texture );
        tile_sprite.setPosition(
            x * (tile_size.x + outlineThickness),
            y * (tile_size.y + outlineThickness)
        );
        tempMapTexture.draw( tile_sprite );
    };
    tempMapTexture.display();

    sf::Image mapTexImage( tempMapTexture.getTexture().copyToImage() );
    bool succes = mapTexImage.saveToFile( MAPS_DIR + map_name + "/texture.png" );
    return succes;
};
bool MapFrame::importMapTexture( std::string map_name ) {
    bool load_succes = map_texture.loadFromFile( MAPS_DIR + map_name + "/texture.png" );
    if (!load_succes) return false;
    sf::Vector2u uSize = map_texture.getSize();
    setConfig( sf::Vector2i( uSize.x, uSize.y ) );
    return true;
};

int MapFrame::getOutlineThickness() {
    return outlineThickness;
};

void MapFrame::draw( sf::RectangleShape _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void MapFrame::draw( sf::Text _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void MapFrame::draw( sf::Sprite _shape ) {
    if (!valid) return;
    frame.draw( _shape );
};
void MapFrame::clear() {
    frame.clear();
    if (!valid) return;
    frame.draw( sf::Sprite( map_texture ) );
};