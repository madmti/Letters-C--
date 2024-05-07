#ifndef Map_values_h
#define Map_values_h
#include "../types.hpp"

enum SCOPE_VALUES {
    SCOPE_EMPTY = 0,
    SCOPE_ONGO = 1,
    SCOPE_ALLY = 2,
    SCOPE_HIT = 3,
};

enum MAP_VALUES {
    MAP_SPAWN_RED = -3,
    MAP_SPAWN_BLUE = -2,
    MAP_VOID = -1,
    MAP_FLOOR_0 = 0,
    MAP_WALL_0 = 1,
    MAP_ALLY_0 = 2,
    MAP_DUMMY_0 = 3,
    MAP_ENEMY_0 = 4,
};

enum BUILD_MAP_TILES {
    BUILD_MAP_VOID = 'v',
    BUILD_MAP_FLOOR = 'f',
    BUILD_MAP_WALL = 'w',
    BUILD_MAP_SPAWN_BLUE = 'b',
    BUILD_MAP_SPAWN_RED = 'r',
    BUILD_MAP_ALLY = 'B',
    BUILD_MAP_ENEMY = 'R',
    BUILD_MAP_DUMMY = 'D'
};

typedef std::vector<std::vector<MAP_VALUES>> D2_map_int;
typedef std::vector<std::vector<SCOPE_VALUES>> D2_scope_int;
typedef std::vector<std::vector<BUILD_MAP_TILES>> D2_map_char;
typedef std::map<MAP_VALUES, sf::Texture*> Map_textures;

class Map {
private:
    D2_map_int map_values;
    D2_scope_int scope_values;
    std::string name;
    sf::Vector2i dim;
    Map_textures tex;
    std::vector<sf::Texture*> tex_mem;
    std::vector<sf::Vector2i> spawnBlue;
    std::vector<sf::Vector2i> spawnRed;
    sf::Sprite nullSprite;
    bool valid;

    MAP_VALUES buildToMap(BUILD_MAP_TILES build);
    void getLineMap(std::string& line, bool* dimX, int dy);
    void loadTextureFromLine(std::string& line);

    void clearAll();
public:
    Map();
    Map(std::string _name);
    ~Map();

    bool load();
    bool load(std::string _name);

    std::vector<sf::Vector2i> getSpawnBlue();
    std::vector<sf::Vector2i> getSpawnRed();

    std::string getName();
    sf::Vector2i getDim();
    int getDimX();
    int getDimY();
    bool isOnMap(int x, int y);
    bool isOnMap(sf::Vector2i pos);

    sf::Vector2i getTileSize();

    sf::Sprite getTexture(MAP_VALUES val);

    void set_map(int x, int y, MAP_VALUES val);
    void set_map(sf::Vector2i pos, MAP_VALUES val);
    MAP_VALUES get_map(int x, int y);
    MAP_VALUES get_map(sf::Vector2i pos);

    void set_scope(int x, int y, SCOPE_VALUES val);
    void set_scope(sf::Vector2i pos, SCOPE_VALUES val);
    SCOPE_VALUES get_scope(int x, int y);
    SCOPE_VALUES get_scope(sf::Vector2i pos);

};

#endif