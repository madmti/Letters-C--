#ifndef Character_Abstract_h
#define Character_Abstract_h
#include "../types.hpp"
#include "../tiles/map.hpp"
#include "../frames/char/frame.hpp"

struct Damage {
    std::vector<sf::Vector2i> targets;
    float dmg;
    bool isPercentage;
    Damage(float _dmg, bool _perCent) { dmg = _dmg; isPercentage = _perCent; };
};

const int C_DMG = 20;
const int D_DMG = 10;
const int P_DMG = 100;
const float X_DMG = 0.1;

enum CHARS_MAX_LIFE {
    C_MAX_LIFE = 200,
    D_MAX_LIFE = 300,
    P_MAX_LIFE = 100,
    X_MAX_LIFE = 50,
};

class Character {
protected:
    int x, y;

    char p;
    bool movementMode;
    bool playable;

    const int max_life;
    int life;

    float dmg;
    bool damageIsPercent;

    Map* map;
public:
    Character(char _p, float _dmg, int _max_life, bool _playable);
    Character(int _x, int _y, char _p, float _dmg, int _max_life, bool _playable);

    void move(int x, int y);
    void place();
    void recvDamage(float Damage);
    void recvDamage_perCent(float Damage);

    virtual void scope(int x, int y) = 0;
    virtual void showScope() = 0;
    virtual void descope() = 0;
    virtual void changeMovementMode() = 0;
    virtual Damage doDamage() = 0;

    float getPercentageLife() { return (float) life / (float) max_life; };
    int getMaxLife() { return max_life; };
    int getLife() { return life; };
    char getP() { return p; };
    int getX() { return x; };
    int getY() { return y; };
    sf::Vector2i getPos() { return sf::Vector2i(x, y); };
    bool isPlayable() { return playable; };
    bool onMovementMode() { return movementMode; };
    void setPos(int _x, int _y) { x = _x; y = _y; };
    void setPos(sf::Vector2i pos) { x = pos.x; y = pos.y; };

    void setMap(Map* _map) { map = _map; };
};

#endif