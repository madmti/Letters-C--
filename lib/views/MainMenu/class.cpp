#include "class.hpp"

MainMenuView::MainMenuView(std::string _id) : View(_id) {
    opt = 0;
    optList = std::vector<Option>{
        Option("#onlinemenu", "online"),
        Option("#playground", "playground"),
        Option("#myteam", "my team"),
        Option("#configmenu", "configuration")
    };
    req_keys = std::vector<Key>{
        sf::Keyboard::W,
        sf::Keyboard::S,
        sf::Keyboard::Space,
    };
};

void MainMenuView::clear() {
    frame.clear();
};

void MainMenuView::display() {
    sf::Text title("Letters Online", config->theme.FONT);
    title.setCharacterSize(100);
    title.setPosition(100, 200);
    title.setFillColor(config->theme.colors.base);

    sf::Text selector(">", config->theme.FONT);
    selector.setCharacterSize(50);
    selector.setPosition(100, 500 + opt * 50);
    selector.setFillColor(config->theme.colors.base);

    for (int i = 0; i < optList.size(); i++) {
        Option act = optList.at(i);
        sf::Text txt_opt(act.text, config->theme.FONT);
        txt_opt.setCharacterSize(50);
        txt_opt.setPosition(200, 500 + i * 50);
        txt_opt.setFillColor(config->theme.colors.base);
        frame.draw(txt_opt);
    };

    frame.draw(selector);
    frame.draw(title);
};

ViewRequest MainMenuView::capture(Key k) {
    if (k == sf::Keyboard::Space) {
        Option act = optList.at(opt);
        return ViewRequest("", ID, act.viewid, true);
    }
    else if (k == sf::Keyboard::S) {
        opt = (opt + 1) % 4;
    }
    else if (k == sf::Keyboard::W) {
        if (opt <= 0) opt = 3;
        else opt--;
    };
    return ViewRequest(false);
};