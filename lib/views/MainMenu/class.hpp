#ifndef MainMenu_h
#define MainMenu_h
#include "../abstract.hpp"

struct Option {
    std::string viewid, text;
    Option(std::string _view, std::string _text) {
        viewid = _view;
        text = _text;
    };
};

class MainMenuView :public View {
private:
    int opt;
    std::vector<Option> optList;
public:
    MainMenuView(std::string _id);
    ~MainMenuView();
    void display();
    ViewRequest capture(Key _k);
};

#endif