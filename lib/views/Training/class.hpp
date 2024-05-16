#ifndef Training_h
#define Training_h
#include "../abstract.hpp"
#include "../../map/map.hpp"
#include "../../chars/P/char.hpp"
#include "../../frames/char/frame.hpp"

class Training :public View {
private:
    Map map;
    Char_P p;
    CharFrame p_f;

    void display_Stats();
    void display_Map();

    void capture_Cam();
    void capture_Control();

    void loadMap();
public:
    Training( std::string _id );
    ~Training();

    void clear();
    void display();
    ViewRequest capture( Key _k );
};

#endif