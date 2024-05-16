#ifndef Frame_map_h
#define Frame_map_h
#include "../abstract.hpp"
#include "../../map/values.hpp"

class MapFrame :public Frame {
private:
    sf::Texture map_texture;
    int outlineThickness;
    void makeNull();
public:
    MapFrame( std::string map_name );
    MapFrame();
    ~MapFrame();
    int getOutlineThickness();

    bool buildMapTexture( std::map<MapValues, sf::Texture*> textures, std::vector<std::vector<MapValues>> map_values, sf::Vector2i map_size, sf::Vector2i tile_size, std::string map_name );
    bool importMapTexture( std::string map_name );

    void draw( sf::RectangleShape _shape );
    void draw( sf::Text _shape );
    void draw( sf::Sprite _shape );
    void clear();
};

#endif