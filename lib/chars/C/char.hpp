#ifndef Char_C_h
#define Char_C_h
#include "../abstract.hpp"

class Char_C :public Character {
private:
    std::vector<sf::Vector2i> targets;
    sf::Vector2i act_scope{ 0, 0 };
    int range;

public:
    Char_C(int _x, int _y, bool playable);
    Char_C(bool playable);
    ~Char_C();

    void scope(int _x, int _y);
    void showScope();
    void descope();
    void changeMovementMode();
};

#endif