#include "class.hpp"

ConfigMenu::ConfigMenu(std::string _id) :View(_id) {
    select = false;
    req_keys = std::vector<Key>{
        sf::Keyboard::Escape,
        sf::Keyboard::Left,
        sf::Keyboard::Right,
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Space,
        sf::Keyboard::Enter,
    };
};

void ConfigMenu::display() {
    sf::Text title("Configuration", config->theme.FONT);
    title.setCharacterSize(100);
    title.setPosition(0, 0);
    title.setFillColor(config->theme.colors.base);

    sf::Text Info("Delta (" + std::to_string(config->window.dx) + ", " + std::to_string(config->window.dy) + ") \
    \nScreen (" + std::to_string(config->window.width) + ", " + std::to_string(config->window.height) + ")", config->theme.FONT);
    Info.setCharacterSize(50);
    Info.setPosition(0, 100);
    Info.setFillColor(config->theme.colors.base);

    sf::RectangleShape win(sf::Vector2f(config->window.width, config->window.height));
    win.setPosition(config->window.dx, config->window.dy);
    win.setOutlineColor(sf::Color::Red);
    win.setOutlineThickness(500);
    win.setFillColor(sf::Color::Green);

    window->draw(win);
    window->draw(title);
    window->draw(Info);
};

ViewRequest ConfigMenu::capture(Key k) {
    if (k == sf::Keyboard::Escape) {
        return ViewRequest("", ID, "#mainmenu", true);
    }
    else if (k == sf::Keyboard::Space) {
        select = !select;
    }
    else if (k == sf::Keyboard::Enter) {
        window->setSize(sf::Vector2u(config->window.width, config->window.height));
        window->setView(sf::View(sf::FloatRect(sf::Vector2f(config->window.dx, config->window.dy), sf::Vector2f(config->window.width, config->window.height))));
    }
    else if (k == sf::Keyboard::Up) {
        select
            ? config->window.height--
            : config->window.dy--;
    }
    else if (k == sf::Keyboard::Down) {
        select
            ? config->window.height++
            : config->window.dy++;
    }
    else if (k == sf::Keyboard::Left) {
        select
            ? config->window.width--
            : config->window.dx--;
    }
    else if (k == sf::Keyboard::Right) {
        select
            ? config->window.width++
            : config->window.dx++;
    };

    return ViewRequest(false);
};