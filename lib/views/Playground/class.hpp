#ifndef Playground_h
#define Playground_h
#include "../abstract.hpp"
#include "../../chars/include_chars.hpp"
#include "../../frames/tile/frame.hpp"

class Playground :public View {
private:
    Matrix2i map;
    Matrix2i scope_map;
    sf::Vector2i mapSize{ 32, 18 };

    sf::Vector2f cam{ 0, 0 };
    sf::Vector2f camSize{ 32, 18 };

    int w;
    std::vector<Character*> all_chars;
    std::vector<Character*> notPlayable_chars;
    std::vector<Character*> playable_chars;

    TileFrame map_frame;
    sf::Vector2i tile_size;

    int clock;
    int delta_anim;

    bool cameraMode;
    
    int next_char_idx(int act);
    int prev_char_idx(int act);


public:
    Playground(std::string _id, Config_type* _config, Texture_config* _texture);
    ~Playground();

    void getMap();
    void getPlayable();
    void getConfig();

    void display();
    void display_map();
    void display_scope();
    void display_player(std::vector<Character*> char_list, bool playable);
    void display_control_mode();
    void display_char_select();

    void clear();

    ViewRequest capture(Key _k);
};

#endif