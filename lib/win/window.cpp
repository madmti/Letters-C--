#include "window.hpp"
#include "../views/MainMenu/class.hpp"
#include "../views/ConfigMenu/class.hpp"
#include "../views/Playground/class.hpp"

/* * * * * * * * * * * * * * * * * CLASS * * * * * * * * * * * * * * * */

Window::Window(bool _debug) {
    debug = _debug;
    getConfig();
    getViews();
};

Window::~Window() {};

void Window::start() {
    sf::VideoMode win_mode(config->window.width, config->window.height);
    win.create(win_mode, "Letters");
    setup();
    mainLoop();
};

void Window::mainLoop() {
    sf::Uint32 frameRate(16.666);

    while (win.isOpen()) {
        win.clear();
        captureEvents();
        display();
        sf::sleep(sf::milliseconds(frameRate));
    };
};

void Window::setup() {};

/* * * * * * * * * * * * * * * * * UTILS * * * * * * * * * * * * * * * */

void Window::exception(std::string msg) {
    std::cout << "#=======" << std::endl;
    std::cout << "# Exception error" << std::endl;
    std::cout << "#=======" << std::endl;
    std::cout << "# Error: " << msg << std::endl;
    std::cout << "#=======" << std::endl;
    win.close();
};

/* * * * * * * * * * * * * * * * * CONFIG * * * * * * * * * * * * * * * */

bool Window::validKeysConfig(Json::Value& _conf) {
    // nivel 0
    if (_conf["window"].isNull() || _conf["theme"].isNull()) return false;
    // nivel 1
    if (_conf["window"]["width"].isNull() || !_conf["window"]["width"].isNumeric() ||
        _conf["window"]["height"].isNull() || !_conf["window"]["height"].isNumeric() ||
        _conf["window"]["FPS"].isNull() || !_conf["window"]["FPS"].isNumeric() ||
        _conf["window"]["dx"].isNull() || !_conf["window"]["dx"].isNumeric() ||
        _conf["window"]["dy"].isNull() || !_conf["window"]["dy"].isNumeric()) return false;

    if (_conf["theme"]["font"].isNull() || !_conf["theme"]["font"].isString() ||
        _conf["theme"]["color"].isNull()) return false;


    // nivel 2
    if (_conf["theme"]["color"]["base"].isNull() ||
        _conf["theme"]["color"]["back"].isNull()) return false;

    // nivel 3
    if (_conf["theme"]["color"]["base"]["r"].isNull() || !_conf["theme"]["color"]["base"]["r"].isNumeric() ||
        _conf["theme"]["color"]["base"]["g"].isNull() || !_conf["theme"]["color"]["base"]["g"].isNumeric() ||
        _conf["theme"]["color"]["base"]["b"].isNull() || !_conf["theme"]["color"]["base"]["b"].isNumeric() ||
        _conf["theme"]["color"]["base"]["a"].isNull() || !_conf["theme"]["color"]["base"]["a"].isNumeric()) return false;

    return true;
};

void Window::getConfig() {
    std::ifstream config_json_file("config.json", std::ifstream::binary);
    if (!config_json_file.is_open()) exception("Cant find config.json");

    Json::Value _conf;
    config_json_file >> _conf;
    config_json_file.close();

    if (!validKeysConfig(_conf)) exception("Config.json has missing or invalid keys/values");
    config = new Config_type();

    int width = _conf["window"]["width"].asInt();
    int height = _conf["window"]["height"].asInt();
    int FPS = _conf["window"]["FPS"].asInt();
    int dx = _conf["window"]["dx"].asInt();
    int dy = _conf["window"]["dy"].asInt();
    config->window.set(width, height, dx, dy, FPS);

    std::string font = _conf["theme"]["font"].asString();
    config->theme.set(font);
    config->theme.FONT.loadFromFile("./static/fonts/" + font + ".ttf");

    sf::Color base;
    base.r = _conf["theme"]["color"]["base"]["r"].asUInt();
    base.g = _conf["theme"]["color"]["base"]["g"].asUInt();
    base.b = _conf["theme"]["color"]["base"]["b"].asUInt();
    base.a = _conf["theme"]["color"]["base"]["a"].asUInt();
    config->theme.colors.base = base;

    sf::Color back;
    back.r = _conf["theme"]["color"]["back"]["r"].asUInt();
    back.g = _conf["theme"]["color"]["back"]["g"].asUInt();
    back.b = _conf["theme"]["color"]["back"]["b"].asUInt();
    back.a = _conf["theme"]["color"]["back"]["a"].asUInt();
    config->theme.colors.back = back;


    view_manager.setConfig(config, &win);
};

void Window::getViews() {
    view_manager.insertView(new MainMenuView("#mainmenu"));
    view_manager.insertView(new ConfigMenu("#configmenu"));
    view_manager.insertView(new Playground("#playground"));
};

/* * * * * * * * * * * * * * * * * DISPLAY * * * * * * * * * * * * * * * */

void Window::display() {
    view_manager.doViewDisplay();
    win.display();
};

/* * * * * * * * * * * * * * * * * EVENTS * * * * * * * * * * * * * * * */

void Window::captureEvents() {
    sf::Event ev;
    while (win.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) win.close();
        view_manager.doViewCapture(ev);
    };
};