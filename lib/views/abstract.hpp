#ifndef View_h
#define View_h
#include "../types.hpp"
#include "../frames/view/frame.hpp"

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
    ViewFrame frame;
public:
    View(std::string _id);
    View(std::string _id, Config_type* _config, Texture_config* _textures);
    View();
    ~View();
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual ViewRequest capture(Key _k) = 0;

    std::string getID() { return ID; };
    vectKey getRequiredKeys() { return req_keys; };
    void setRequiredKeys(vectKey _keys) { req_keys = _keys; };
    void setConfig(Config_type* _config) { config = _config; frame.setConfig(sf::Vector2i(_config->window.dx, _config->window.dy), sf::Vector2i(_config->window.width, _config->window.height)); };
    sf::Sprite getViewSprite() { return frame.getSprite(); };
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
    void doViewClear();
    void doViewCapture(sf::Event _ev);
};

#endif