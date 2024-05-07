#include "./map.hpp"


Map::Map() :dim{ 0,0 } {
    valid = false;
    name = "";
};
Map::Map(std::string _name) : dim{ 0,0 } {
    valid = false;
    load(_name);
};

Map::~Map() {
    int n_tex_mem = tex_mem.size();
    for (int i = 0; i < n_tex_mem; i++) delete tex_mem.at(i);
};

bool Map::isOnMap(int x, int y) {
    return (0 <= x && x < dim.x && 0 <= y && y < dim.y);
};
bool Map::isOnMap(sf::Vector2i pos) {
    return (0 <= pos.x && pos.x < dim.x && 0 <= pos.y && pos.y < dim.y);
};

bool Map::load() {
    if (valid || name == "") return false;
    return load(name);
};

void Map::clearAll() {
    map_values.clear();
    scope_values.clear();
    dim = sf::Vector2i(0, 0);
    int n_tex_mem = tex_mem.size();
    for (int i = 0; i < n_tex_mem; i++) delete tex_mem.at(i);
    tex_mem.clear();
    spawnBlue.clear();
    spawnRed.clear();
    valid = false;
};

bool Map::load(std::string _name) {
    clearAll();
    std::ifstream file("./static/maps/" + _name + "/map.txt");
    if (!file.is_open()) {
        valid = false;
        return false;
    };
    std::string line = "";
    bool dimX = false;
    int mapY = 0;
    for (int n = 0; std::getline(file, line); n++) {
        char first = line.front();
        if (first == '*') continue;
        else if (first == '-') {
            getLineMap(line, &dimX, mapY);
            mapY++;
        }
        else loadTextureFromLine(line);
    };
    file.close();
    valid = true;
    scope_values.assign(dim.y, std::vector<SCOPE_VALUES>(dim.x, SCOPE_EMPTY));

    return true;
};

void Map::getLineMap(std::string& line, bool* dimX, int mapY) {
    std::vector<MAP_VALUES> map_line;
    int mapX = 0;
    for (int i = 0; i < line.size(); i++) {
        char c = line.at(i);
        if (c == ' ' || c == '-' || c == '\n') continue;
        MAP_VALUES value = buildToMap(BUILD_MAP_TILES(c));
        map_line.push_back(value);
        if (value == MAP_SPAWN_BLUE) spawnBlue.push_back(sf::Vector2i(mapX, mapY));
        else if (value == MAP_SPAWN_RED) spawnRed.push_back(sf::Vector2i(mapX, mapY));
        if (!*dimX) dim.x++;
        mapX++;
    };
    *dimX = true;
    map_values.push_back(map_line);
    dim.y++;
};

void Map::loadTextureFromLine(std::string& line) {
    std::string tex_name = "";
    for (int i = 2; i < line.size(); i++) if (line.at(i) != '\n') tex_name.push_back(line.at(i));
    MAP_VALUES map_val = buildToMap(BUILD_MAP_TILES(line.front()));
    sf::Texture* temp_tex = new sf::Texture;
    tex_mem.push_back(temp_tex);

    if (!temp_tex->loadFromFile("./static/textures/tiles/" + tex_name + ".png")) { return; };
    tex.insert_or_assign(map_val, temp_tex);
};

sf::Vector2i Map::getDim() { return dim; };
int Map::getDimX() { return dim.x; };
int Map::getDimY() { return dim.y; };

sf::Sprite Map::getTexture(MAP_VALUES _val) {
    if (tex.count(_val) == 0) return nullSprite;
    return sf::Sprite(*tex.at(_val));
};

void Map::set_map(int x, int y, MAP_VALUES val) {
    if (!isOnMap(x, y)) return;
    map_values.at(y).at(x) = val;
};
void Map::set_map(sf::Vector2i pos, MAP_VALUES val) {
    if (!isOnMap(pos)) return;
    map_values.at(pos.y).at(pos.x) = val;
};
void Map::set_scope(int x, int y, SCOPE_VALUES val) {
    if (!isOnMap(x, y)) return;
    scope_values.at(y).at(x) = val;
};
void Map::set_scope(sf::Vector2i pos, SCOPE_VALUES val) {
    if (!isOnMap(pos)) return;
    scope_values.at(pos.y).at(pos.x) = val;
};

MAP_VALUES Map::get_map(int x, int y) {
    if (!isOnMap(x, y)) return MAP_VOID;
    return map_values.at(y).at(x);
};
MAP_VALUES Map::get_map(sf::Vector2i pos) {
    if (!isOnMap(pos)) return MAP_VOID;
    return map_values.at(pos.y).at(pos.x);
};
SCOPE_VALUES Map::get_scope(int x, int y) {
    if (!isOnMap(x, y)) return SCOPE_EMPTY;
    return scope_values.at(y).at(x);
};
SCOPE_VALUES Map::get_scope(sf::Vector2i pos) {
    if (!isOnMap(pos)) return SCOPE_EMPTY;
    return scope_values.at(pos.y).at(pos.x);
};

sf::Vector2i Map::getTileSize() {
    return sf::Vector2i(50, 50);
};

std::string Map::getName() {
    return name;
};

std::vector<sf::Vector2i> Map::getSpawnBlue() {
    return spawnBlue;
};
std::vector<sf::Vector2i> Map::getSpawnRed() {
    return spawnRed;
};


MAP_VALUES Map::buildToMap(BUILD_MAP_TILES build) {
    switch (build) {
    case BUILD_MAP_FLOOR: { return MAP_FLOOR_0; };
    case BUILD_MAP_WALL: { return MAP_WALL_0; };
    case BUILD_MAP_SPAWN_BLUE: { return MAP_SPAWN_BLUE; };
    case BUILD_MAP_SPAWN_RED: { return MAP_SPAWN_RED; };
    case BUILD_MAP_ALLY: { return MAP_ALLY_0; };
    case BUILD_MAP_ENEMY: { return MAP_ENEMY_0; };
    case BUILD_MAP_DUMMY: { return MAP_DUMMY_0; };
    default: {
        return MAP_VOID;
    };
    };
};