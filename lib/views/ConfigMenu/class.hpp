#ifndef ConfigMenu_h
#define ConfigMenu_h
#include "../abstract.hpp"

class ConfigMenu :public View {
private:
    bool select;
public:
    ConfigMenu(std::string _id);
    ~ConfigMenu();
    void display();
    ViewRequest capture(Key _k);
};


#endif