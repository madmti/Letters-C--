#ifndef Map_h
#define Map_h
#include "./values.hpp"
#include "../frames/map/frame.hpp"

class Map {
private:
    MapMetaData meta;
    MapValuesData values;
    MapFrame frame;

    void setNull();
    bool importAllData( std::string map_name );
    std::vector<MapValues> getLineValues( std::string& line, int mapY, SpawnData* spawns );
    sf::Texture* getTexture( std::string& line );
    sf::Vector2i getTileSize( std::map<MapValues, sf::Texture*> textures, std::vector<MapValues> values );
    void deleteMap( std::map<MapValues, sf::Texture*> textures, std::vector<MapValues> values );
    MapValues getMapValueFromString( std::string& val_string );


    bool load( std::string map_name );
    bool build( std::string map_name );
public:
    Map( std::string map_name );
    Map();
    ~Map();

    bool load_or_build_map( std::string map_name );
    bool load_map( std::string map_name );
    bool build_map( std::string map_name );

    void zoom( float k );
    void zoom( int k );
    void move( int x, int y );
    void move( sf::Vector2i pos );

    void clear();
    void draw( sf::RectangleShape _shape );
    void draw( sf::Text _shape );
    void draw( sf::Sprite _shape );

    void showOutLines( sf::Color free, sf::Color block );
    void showOutLines( sf::Color col );

    bool isCompleteData();
    sf::Sprite getFrame();
    MapValues getMapValue( int x, int y );
    MapValues getMapValue( sf::Vector2i pos );
    std::vector<ScopeData> getScopeValues();
    MapMetaData getMetaData();
    
    void setMapValue( MapValues val, int x, int y );
    void setMapValue( MapValues val, sf::Vector2i pos );
    void setScopeValue( ScopeValues val, int x, int y );
    void setScopeValue( ScopeValues val, sf::Vector2i pos );

    bool isOnMap( int x, int y );
    bool isOnMap( sf::Vector2i pos );
};

#endif