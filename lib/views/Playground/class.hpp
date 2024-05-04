#ifndef Playground_h
#define Playground_h
#include "../../types.hpp"
#include "../../../static/chars/include_chars.hpp"

class Playground :public View {
private:
    Matrix2i map;
    Matrix2i scope_map;
    sf::Vector2i mapSize{ 32, 18 };

    sf::Vector2u cam{ 0, 0 };
    sf::Vector2f camSize{ 32, 18 };

    int w;
    std::vector<Character*> chars;

    int clock;
    int delta_anim;

    bool cameraMode;

public:
    Playground(std::string _id);
    ~Playground();

    void getMap();

    void display();
    void display_map();
    void display_scope();
    void display_player();
    void display_control_mode();

    ViewRequest capture(Key _k);
};

#endif