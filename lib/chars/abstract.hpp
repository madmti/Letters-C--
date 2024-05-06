#ifndef Character_Abstract_h
#define Character_Abstract_h
#include "../types.hpp"
#include "../tiles/map.hpp"
#include "../frames/char/frame.hpp"

class Character {
protected:
    int x, y;

    char p;
    bool movementMode;
    bool playable;

    Map* map;
public:
    Character(char _p, bool _playable) { p = _p; playable = _playable; movementMode = true; };
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
    void setPos(int _x, int _y) { x = _x; y = _y; };
    void setPos(sf::Vector2i pos) { x = pos.x; y = pos.y; };

    void setMap(Map* _map) { map = _map; };

};

#endif