#ifndef Window_h
#define Window_h

#include "../types.hpp"

class Window {
private:
    sf::RenderWindow win;
    Config_type* config;

    ViewManager view_manager;

    bool debug;

    /* * * * * * * * * * * * * * * * * CONFIG * * * * * * * * * * * * * * * */

    bool validKeysConfig(Json::Value& _conf);
    void getConfig();
    void getViews();

    /* * * * * * * * * * * * * * * * * EVENTS * * * * * * * * * * * * * * * */

    void captureEvents();

    /* * * * * * * * * * * * * * * * * DISPLAY * * * * * * * * * * * * * * * */

    void display();

    /* * * * * * * * * * * * * * * * * UTILS * * * * * * * * * * * * * * * */

    void exception(std::string _msg);

    /* * * * * * * * * * * * * * * * * CLASS * * * * * * * * * * * * * * * */

    void setup();
    void mainLoop();
public:
    Window(bool _debug);
    ~Window();

    void start();
};

#endif