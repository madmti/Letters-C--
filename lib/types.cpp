#include "./types.hpp"

/*
*** ViewManager
*/

ViewManager::ViewManager() {

};

ViewManager::~ViewManager() {
    if (!view_ids.empty()) for (int i = 0; i < view_ids.size(); i++) delete views[view_ids.at(i)];
};

void ViewManager::setConfig(Config_type* _win_config, sf::RenderWindow* _window) { win_config = _win_config; window = _window; };

Key ViewManager::getKeyPress(sf::Event _ev, vectKey _keys) {
    if (_ev.type == sf::Event::KeyPressed) for (int n = _keys.size() - 1; n >= 0; n--) if (_ev.key.code == _keys[n]) return _ev.key.code;
    return sf::Keyboard::Key::Unknown;
};

bool ViewManager::checkPageID(std::string _id) {
    for (int i = 0; i < view_ids.size(); i++) if (view_ids.at(i) == _id) return true;
    return false;
};

void ViewManager::changePage() {
    if (hist.size() <= 1) return;
    hist.pop_back();
};
void ViewManager::changePage(std::string _pageID) {
    if (!checkPageID(_pageID)) return;
    hist.push_back(_pageID);
};
void ViewManager::changePage(int _idx) {
    int size = hist.size();
    if (size <= _idx) return;

    for (int i = 0; i < size - _idx; i++) hist.pop_back();
};

void ViewManager::insertView(View* _view) {
    std::string _id = _view->getID();
    _view->setConfig(win_config, window);
    views.insert_or_assign(_id, _view);
    view_ids.push_back(_id);
    if (hist.empty()) hist.push_back(_id);
};

void ViewManager::doViewDisplay() {
    if (hist.empty()) return;

    sf::RectangleShape background(sf::Vector2f(win_config->window.width, win_config->window.height));
    background.setFillColor(win_config->theme.colors.back);
    background.setPosition(win_config->window.dx, win_config->window.dy);
    window->draw(background);

    View* now = views.at(hist.back());
    now->display();
};

void ViewManager::doViewCapture(sf::Event _ev) {
    if (hist.empty()) return;

    View* now = views.at(hist.back());
    Key k = getKeyPress(_ev, now->getRequiredKeys());

    // Requests
    ViewRequest req = now->capture(k);
    if (req.isNull()) return;
    if (req.isLocal()) {
        changePage(req.getHead(false));
    };
    req.readed();

};

/*
*** ViewRequest
*/

ViewRequest::ViewRequest(bool valid) { isReqNull = !valid; };
ViewRequest::ViewRequest(Json::Value _body, std::string _from, std::string _to, bool _local) { body = _body; from = _from; to = _to; local = _local; };
ViewRequest::ViewRequest() {};
ViewRequest::~ViewRequest() {};

void ViewRequest::setHead(std::string _from, std::string _to, bool _local) { from = _from; to = _to; local = _local; };
void ViewRequest::setBody(Json::Value _body) { body = _body; };

bool ViewRequest::isNull() { return isReqNull; };
bool ViewRequest::isLocal() { return local; };
bool ViewRequest::wasRead() { return read; };
Json::Value ViewRequest::getBody() { return body; };
std::string ViewRequest::getHead(bool _from) { return _from ? from : to; };

void ViewRequest::makeLocal() { local = true; };
void ViewRequest::makeNull() { isReqNull = true; };
void ViewRequest::readed() { read = true; };
