#include "include.hpp"
#ifndef Types_h
#define Types_h
/*
*** Config json
*/

struct Color_info {
    sf::Color base;
    sf::Color back;
};

struct Theme_info {
    std::string font_name;
    sf::Font FONT;
    Color_info colors;
    void set(std::string _fontName) { font_name = _fontName; };
};

struct Window_info {
    int width;
    int height;
    int dx;
    int dy;
    int FPS;
    void set(int _w, int _h, int _dx, int _dy, int _fps) { width = _w; height = _h; dx = _dx; dy = _dy; FPS = _fps; };
};

struct Tiles_textures {
    sf::IntRect tile_mask;
    sf::Vector2i tile_size;
    sf::Texture map_wall_0;
    sf::Texture map_floor_0;
};

struct Texture_config {
    Tiles_textures tiles;
};

struct Config_type {
    Window_info window;
    Theme_info theme;
};

/*
*** Scales
*/

enum FONT_SCALES {};

enum FRAME_SCALES {};

typedef sf::Keyboard::Key Key;
typedef std::vector<Key> vectKey;
typedef std::vector<std::vector<int>> Matrix2i;

#endif