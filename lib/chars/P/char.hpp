#ifndef Char_P_h
#define Char_P_h
#include "../abstract.hpp"

class Char_P :public Character {
private:
    std::vector<sf::Vector2i> targets;
    sf::Vector2i act_scope;
    int range;
public:
    Char_P(int _x, int _y, bool playable);
    ~Char_P();

    void scope(int _x, int _y);
    void showScope();
    void descope();
    void changeMovementMode();

};

#endif