#ifndef Playground_h
#define Playground_h
#include "../../types.hpp"
#include "../../../static/chars/include_chars.hpp"

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

    int clock;
    int delta_anim;

    bool cameraMode;
    
    int next_char_idx(int act);
    int prev_char_idx(int act);


public:
    Playground(std::string _id);
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

    ViewRequest capture(Key _k);
};

#endif