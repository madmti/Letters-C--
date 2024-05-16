#include "map.hpp"

Map::Map() {};
Map::Map( std::string map_name ) {
    load_or_build_map( map_name );
};
Map::~Map() {};

bool Map::load_or_build_map( std::string map_name ) {
    return load( map_name ) || build( map_name ) && load( map_name );
};

bool Map::load_map( std::string map_name ) {
    return load( map_name );
};

bool Map::build_map( std::string map_name ) {
    return build( map_name ) && load( map_name );
};

void Map::setNull() {
    meta.completeData = false;
    meta.map_name = "";
    meta.map_size = sf::Vector2i( 0, 0 );
    meta.tile_size = sf::Vector2i( 0, 0 );
    meta.spawns.blue.clear();
    meta.spawns.red.clear();
    meta.spawns.size = 0;
    values.map_values.clear();
    values.scope_values.clear();
};

bool Map::importAllData( std::string map_name ) {
    std::ifstream file( MAPS_DIR + map_name + "/data.bin", std::ios::binary );
    if (!file.is_open()) return false;

    int blue_spawn_size;
    file.read( (char*)&blue_spawn_size, sizeof( int ) );

    sf::Vector2i blue_spawns[blue_spawn_size];
    file.read( (char*)blue_spawns, sizeof( sf::Vector2i ) * blue_spawn_size );

    int red_spawn_size;
    file.read( (char*)&red_spawn_size, sizeof( int ) );

    sf::Vector2i red_spawns[red_spawn_size];
    file.read( (char*)red_spawns, sizeof( sf::Vector2i ) * red_spawn_size );

    sf::Vector2i tile_size;
    file.read( (char*)&tile_size, sizeof( sf::Vector2i ) );

    sf::Vector2i map_size;
    file.read( (char*)&map_size, sizeof( sf::Vector2i ) );

    MapValues map_values[map_size.y][map_size.x];
    file.read( (char*)map_values, sizeof( MapValues[map_size.y][map_size.x] ) );

    file.close();
    if (file.bad()) return false;

    meta.map_name = map_name;
    for (int i = 0; i < blue_spawn_size; i++) meta.spawns.blue.push_back( blue_spawns[i] );
    for (int i = 0; i < red_spawn_size; i++) meta.spawns.red.push_back( red_spawns[i] );
    meta.spawns.size = blue_spawn_size + red_spawn_size;
    meta.map_size = map_size;
    meta.tile_size = tile_size;
    for (int y = 0; y < map_size.y; y++) {
        std::vector<MapValues> row;
        for (int x = 0; x < map_size.x; x++) {
            row.push_back( MapValues( map_values[y][x] ) );
        };
        values.map_values.push_back( row );
    };
    return true;
};

std::vector<MapValues> Map::getLineValues( std::string& line, int mapY, SpawnData* spawns ) {
    std::vector<MapValues> row;
    int mapX = 0;
    for (int i = 0; i < line.size(); i++) {
        std::string act;
        char c = line.at( i );
        act.push_back( c );
        if (c == ' ' || c == '-' || c == '\n') continue;

        if (c == BUILD_MAP_SPAWN_BLUE) spawns->blue.push_back( sf::Vector2i( mapX, mapY ) );
        else if (c == BUILD_MAP_SPAWN_BLUE) spawns->blue.push_back( sf::Vector2i( mapX, mapY ) );
        else if (c == BUILD_MAP_CUSTOM_VOID_START || c == BUILD_MAP_CUSTOM_FLOOR_START || c == BUILD_MAP_CUSTOM_WALL_START) {
            act = line.substr( i, 3 );
            i += 2;
        };
        MapValues val = getMapValueFromString( act );
        row.push_back( val );
        mapX++;
    };
    return std::vector<MapValues>( row );
};

sf::Texture* Map::getTexture( std::string& line ) {
    std::string tex_name = "";
    bool onName = false;
    for (int i = 1; i < line.size(); i++) {
        if (line.at( i ) == ':' && !onName) {
            onName = true;
            continue;
        };
        if (line.at( i ) == '\n') continue;
        if (onName) tex_name.push_back( line.at( i ) );
    };
    if (tex_name == "null") return nullptr;

    sf::Texture* temp_tex = new sf::Texture;
    bool load_success = temp_tex->loadFromFile( TEXTURES_DIR + "tiles/" + tex_name + ".png" );
    if (load_success) return temp_tex;
    else return nullptr;
};

sf::Vector2i Map::getTileSize( std::map<MapValues, sf::Texture*> textures, std::vector<MapValues> values ) {
    for (int i = 0; i < values.size(); i++) {
        if (textures.count( values.at( i ) ) != 0 && textures.at( values.at( i ) ) != nullptr) {
            sf::Vector2u uSize = textures.at( values.at( i ) )->getSize();
            return sf::Vector2i( uSize.x, uSize.y );
        };
    };
    return sf::Vector2i( 0, 0 );
};

void Map::deleteMap( std::map<MapValues, sf::Texture*> tex, std::vector<MapValues> val ) {
    for (int i = 0; i < val.size(); i++) {
        if (tex.count( val.at( i ) ) != 0 && tex.at( val.at( i ) ) != nullptr) {
            MapValues key = val.at( i );
            delete tex.at( key );
            tex.insert_or_assign( key, nullptr );
        };
    };
    tex.clear();
};

MapValues Map::getMapValueFromString( std::string& val_string ) {
    if (val_string.size() == 1) {
        char val_char = val_string.at( 0 );
        switch (val_char) {
        case BUILD_MAP_VOID: { return MapValues::MAP_VOID; };
        case BUILD_MAP_FLOOR: { return MapValues::MAP_FLOOR; };
        case BUILD_MAP_WALL: { return MapValues::MAP_WALL; };
        case BUILD_MAP_SPAWN_BLUE: { return MapValues::MAP_SPAWN_BLUE; };
        case BUILD_MAP_SPAWN_RED: { return MapValues::MAP_SPAWN_RED; };
        default: { return MapValues::MAP_NULL; };
        };
    }
    else if (val_string.size() == 3) {
        char start = val_string.front();
        char val_idx = val_string.at( 1 );
        switch (val_idx) {
        case BUILD_MAP_CUSTOM_IDX_0: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_0;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_0;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_0;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_1: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_1;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_1;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_1;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_2: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_2;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_2;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_2;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_3: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_3;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_3;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_3;
            else return MapValues::MAP_NULL;
        };

        case BUILD_MAP_CUSTOM_IDX_4: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_4;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_4;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_4;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_5: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_5;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_5;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_5;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_6: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_6;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_6;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_6;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_7: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_7;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_7;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_7;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_8: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_8;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_8;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_8;
            else return MapValues::MAP_NULL;
        };
        case BUILD_MAP_CUSTOM_IDX_9: {
            if (start == BUILD_MAP_CUSTOM_VOID_START) return MapValues::MAP_CUSTOM_VOID_9;
            else if (start == BUILD_MAP_CUSTOM_FLOOR_START) return MapValues::MAP_CUSTOM_FLOOR_9;
            else if (start == BUILD_MAP_CUSTOM_WALL_START) return MapValues::MAP_CUSTOM_WALL_9;
            else return MapValues::MAP_NULL;
        };
        };
    };
    return MapValues::MAP_NULL;
};

bool Map::load( std::string map_name ) {
    setNull();
    meta.completeData = importAllData( map_name ) && frame.importMapTexture( map_name );
    return meta.completeData;
};

bool Map::build( std::string map_name ) {
    std::ifstream fileIn( MAPS_DIR + map_name + "/template.txt" );
    if (!fileIn.is_open()) return false;
    MapMetaData tempMeta;
    MapValuesData tempValues;
    std::string line = "";
    bool dimXset = false;
    int mapYpos = 0;
    std::map<MapValues, sf::Texture*> textures;
    std::vector<MapValues> texValues;

    for (int n = 0; getline( fileIn, line ); n++) {
        char first = line.front();
        if (first == '-') {
            std::vector<MapValues> row = getLineValues( line, mapYpos, &tempMeta.spawns );
            tempValues.map_values.push_back( row );
            mapYpos++;
        }
        else if (first == '$') {
            sf::Texture* tex = getTexture( line );
            std::string val_string = "";
            for (int i = 1; i < line.size(); i++) { if (line.at( i ) == ':') break; val_string.push_back( line.at( i ) ); };
            MapValues val = getMapValueFromString( val_string );
            textures.insert_or_assign( val, tex );
            texValues.push_back( val );
        };
    };
    fileIn.close();

    int blue_spawn_size = tempMeta.spawns.blue.size();
    int red_spawn_size = tempMeta.spawns.red.size();

    tempMeta.map_name = map_name;
    tempMeta.spawns.size = blue_spawn_size + red_spawn_size;
    tempMeta.tile_size = getTileSize( textures, texValues );
    tempMeta.map_size = sf::Vector2i( tempValues.map_values.at( 0 ).size(), tempValues.map_values.size() );

    bool build_texture_success = frame.buildMapTexture( textures, tempValues.map_values, tempMeta.map_size, tempMeta.tile_size, map_name );

    deleteMap( textures, texValues );

    if (!build_texture_success || tempMeta.tile_size.x == 0 && tempMeta.tile_size.y == 0) return false;

    std::ofstream fileOut( MAPS_DIR + map_name + "/data.bin", std::ios::binary );
    if (!fileOut.is_open()) return false;

    fileOut.write( (char*)&blue_spawn_size, sizeof( int ) );
    fileOut.write( (char*)&tempMeta.spawns.blue[0], sizeof( sf::Vector2i ) * blue_spawn_size );
    fileOut.write( (char*)&red_spawn_size, sizeof( int ) );
    fileOut.write( (char*)&tempMeta.spawns.red[0], sizeof( sf::Vector2i ) * red_spawn_size );
    fileOut.write( (char*)&tempMeta.tile_size, sizeof( sf::Vector2i ) );
    fileOut.write( (char*)&tempMeta.map_size, sizeof( sf::Vector2i ) );
    MapValues map_values[tempMeta.map_size.y][tempMeta.map_size.x];
    for (int y = 0; y < tempMeta.map_size.y; y++) for (int x = 0; x < tempMeta.map_size.x; x++) map_values[y][x] = tempValues.map_values.at( y ).at( x );
    fileOut.write( (char*)map_values, sizeof( MapValues[tempMeta.map_size.y][tempMeta.map_size.x] ) );

    fileOut.close();
    if (fileOut.bad()) return false;
    return true;
};

void Map::zoom( float k ) {};
void Map::zoom( int k ) {};
void Map::move( int x, int y ) {};
void Map::move( sf::Vector2i pos ) {};

void Map::draw( sf::RectangleShape _shape ) {
    if (!meta.completeData) return;
    frame.draw( _shape );
};
void Map::draw( sf::Text _shape ) {
    if (!meta.completeData) return;
    frame.draw( _shape );
};
void Map::draw( sf::Sprite _shape ) {
    if (!meta.completeData) return;
    frame.draw( _shape );
};
void Map::clear() {
    frame.clear();
};

bool Map::isCompleteData() {
    return meta.completeData;
};
sf::Sprite Map::getFrame() {
    return frame.getSprite();
};
MapValues Map::getMapValue( int x, int y ) {
    if (!isOnMap( x, y )) return MapValues::MAP_NULL;
    return values.map_values.at( y ).at( x );
};
MapValues Map::getMapValue( sf::Vector2i pos ) {
    return getMapValue( pos.x, pos.y );
};
std::vector<ScopeData> Map::getScopeValues() {
    return values.scope_values;
};

void Map::setMapValue( MapValues val, int x, int y ) {};
void Map::setMapValue( MapValues val, sf::Vector2i pos ) {};
void Map::setScopeValue( ScopeValues val, int x, int y ) {};
void Map::setScopeValue( ScopeValues val, sf::Vector2i pos ) {};

bool Map::isOnMap( int x, int y ) {
    return 0 <= x && x < meta.map_size.x && 0 <= y && y < meta.map_size.y;
};
bool Map::isOnMap( sf::Vector2i pos ) {
    return isOnMap( pos.x, pos.y );
};

void Map::showOutLines( sf::Color col ) {
    showOutLines( col, col );
};

void Map::showOutLines( sf::Color free, sf::Color block ) {
    int outlineThickness = frame.getOutlineThickness();
    for (int y = 0; y < meta.map_size.y; y++) for (int x = 0; x < meta.map_size.x; x++) {
        MapValues val = getMapValue( x, y );
        bool isFreeSpace = !(MAP_WALL <= val && val <= MAP_CUSTOM_WALL_9);

        sf::RectangleShape outline( sf::Vector2f( meta.tile_size ) );
        outline.setFillColor( sf::Color::Transparent );
        outline.setOutlineThickness( 1 );
        outline.setOutlineColor(
            isFreeSpace ? free : block
        );
        outline.setPosition(
            x * (meta.tile_size.x + outlineThickness),
            y * (meta.tile_size.y + outlineThickness)
        );
        frame.draw( outline );
    };
};
MapMetaData Map::getMetaData() {
    return meta;
};
