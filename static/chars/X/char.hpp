#ifndef Char_X_h
#define Char_X_h
#include "../abstract.hpp"

class Char_X :public Character {
private:

    std::vector<sf::Vector2i> targets;
    std::vector<sf::Vector2i> dirs;
    int idx_dirs;
    int range;
    int max_bounces;
    int bounces;

public:
    Char_X(int _x, int _y, bool playable);
    ~Char_X();

    void scope(int _x, int _y);
    void showScope();
    void descope();
    void changeMovementMode();


};

#endif