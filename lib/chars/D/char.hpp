#ifndef Char_D_h
#define Char_D_h
#include "../abstract.hpp"

class Char_D :public Character {
private:

public:
    Char_D(int _x, int _y, bool playable);
    Char_D(bool playable);
    ~Char_D();

    void scope(int _x, int _y);
    void showScope();
    void descope();
    void changeMovementMode();

};

#endif