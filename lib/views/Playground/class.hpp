#ifndef Playground_h
#define Playground_h
#include "../abstract.hpp"
#include "../../chars/include_chars.hpp"
#include "../../frames/tile/frame.hpp"

class Playground :public View {
private:
    Map map;

    int w;
    std::vector<Character*> all_chars;
    std::vector<Character*> notPlayable_chars;
    std::vector<Character*> playable_chars;

    CharFrame char_frame;
    TileFrame map_frame;
    sf::Vector2i tile_size;

    bool cameraMode;

    int next_char_idx(int act);
    int prev_char_idx(int act);
    int next_map_idx(int act);
    int prev_map_idx(int act);

    std::vector<std::string> maps_names;
    int map_name_idx;
    bool onSelectMapMenu;

    void loadMap();
    void searchMaps();
    int findIdxCharsByPos(sf::Vector2i pos);
public:
    Playground(std::string _id);
    ~Playground();

    void getMap(std::string map_name);
    void setupChars();

    void display();

    void display_select_menu();

    void display_map();
    void display_scope(int dx, int dy);
    void display_player(std::vector<Character*> char_list, bool playable);
    void display_control_mode();
    void display_char_select();

    void clear();

    ViewRequest capture(Key _k);
    void capture_onPlay(Key _k);
};

#endif