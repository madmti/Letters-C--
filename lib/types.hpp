#include "include.hpp"
#ifndef Types_h
#define Types_h
/*
*** Config json
*/

struct Color_info {
    sf::Color base;
    sf::Color back;
};

struct Theme_info {
    std::string font_name;
    sf::Font FONT;
    Color_info colors;
    void set(std::string _fontName) { font_name = _fontName; };
};

struct Window_info {
    int width;
    int height;
    int dx;
    int dy;
    int FPS;
    void set(int _w, int _h, int _dx, int _dy, int _fps) { width = _w; height = _h; dx = _dx; dy = _dy; FPS = _fps; };
};

struct Config_type {
    Window_info window;
    Theme_info theme;
};

/*
*** Scales
*/

enum FONT_SCALES {};

enum FRAME_SCALES {};

typedef sf::Keyboard::Key Key;
typedef std::vector<Key> vectKey;
typedef std::vector<std::vector<int>> Matrix2i;

/*
*** Class
*/

class ViewRequest {
private:
    bool local;
    bool isReqNull;
    bool read;
    std::string from, to;
    Json::Value body;
public:
    ViewRequest(bool valid);
    ViewRequest(Json::Value _body, std::string _from, std::string _to, bool _local);
    ViewRequest();
    ~ViewRequest();

    void setHead(std::string _from, std::string _to, bool _local);
    void setBody(Json::Value _body);

    bool isNull();
    bool isLocal();
    bool wasRead();
    Json::Value getBody();
    std::string getHead(bool _from);

    void makeLocal();
    void makeNull();
    void readed();
};

class View {
protected:
    std::string ID;
    vectKey req_keys;
    Config_type* config;
    sf::RenderWindow* window;
public:
    View(std::string _id) { ID = _id; };
    View() {};
    ~View() {};
    virtual void display() = 0;
    virtual ViewRequest capture(Key _k) = 0;

    std::string getID() { return ID; };
    vectKey getRequiredKeys() { return req_keys; };
    void setRequiredKeys(vectKey _keys) { req_keys = _keys; };
    void setConfig(Config_type* _config, sf::RenderWindow* _window) { config = _config; window = _window; };
};

typedef std::map<std::string, View*> ViewMap;
typedef std::pair<std::string, View*> ViewPair;

class ViewManager {
private:
    std::vector<std::string> hist;
    std::vector<std::string> view_ids;

    ViewMap views;
    ViewRequest request;

    Config_type* win_config;
    sf::RenderWindow* window;

    bool checkPageID(std::string);
    void changePage();
    void changePage(std::string _pageID);
    void changePage(int _idx);

    void manageRequest();
public:
    ViewManager();
    ~ViewManager();

    Key getKeyPress(sf::Event _ev, vectKey _keys);
    void setConfig(Config_type* _win_config, sf::RenderWindow* _window);

    void insertView(View* _view);
    void doViewDisplay();
    void doViewCapture(sf::Event _ev);
};
#endif