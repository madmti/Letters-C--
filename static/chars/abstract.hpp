#ifndef Character_Abstract_h
#define Character_Abstract_h
#include "../../lib/types.hpp"
#include "../tiles/map.hpp"

class Character {
protected:
    int x, y;

    char p;
    bool movementMode;
    bool playable;

    Matrix2i* map;
    Matrix2i* scope_map;
public:
    Character(int _x, int _y, char _p, bool _playable) { x = _x; y = _y; p = _p; movementMode = true; playable = _playable; };

    void move(int x, int y);
    void place();

    virtual void scope(int x, int y) = 0;
    virtual void showScope() = 0;
    virtual void descope() = 0;
    virtual void changeMovementMode() = 0;

    char getP() { return p; };
    int getX() { return x; };
    int getY() { return y; };
    bool isPlayable() { return playable; };
    bool onMovementMode() { return movementMode; };

    void setMaps(Matrix2i* _map, Matrix2i* _scope_map) { map = _map; scope_map = _scope_map; };

};

#endif