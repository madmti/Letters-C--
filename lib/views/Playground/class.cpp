#include "class.hpp"

Playground::Playground(std::string _id) : View(_id), chars{ new Char_P(2, 5, true), new Char_C(5, 5, true), new Char_X(1, 1, true), new Char_D(3, 3, false) } {
    cameraMode = true;
    w = 0;
    clock = 0;
    delta_anim = 1;
    req_keys = std::vector<Key>{
        sf::Keyboard::W,
        sf::Keyboard::A,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::Space,
        sf::Keyboard::Escape,
        sf::Keyboard::E,
        sf::Keyboard::Q,
        sf::Keyboard::F
    };
    getMap();
    for (int i = 0; i < chars.size(); i++) {
        chars.at(i)->setMaps(&map, &scope_map);
        chars.at(i)->place();
    };
};

Playground::~Playground() {
    int n_chars = chars.size();
    for (int i = 0; i < n_chars; i++) {
        delete chars.at(i);
    };
    chars.clear();
};

void Playground::getMap() {
    map.assign(mapSize.y, std::vector<int>(mapSize.x, 0));
    scope_map.assign(mapSize.y, std::vector<int>(mapSize.x, 0));
    for (int y = 0; y < map.size(); y++) for (int x = 0; x < map.at(0).size(); x++) {
        if (x == 0 || x == 31 || y == 0 || y == 17 || x % 4 == 0 && y % 4 == 0) map.at(y).at(x) = MAP_WALL_0;
        else map.at(y).at(x) = MAP_FLOOR_0;

        scope_map.at(y).at(x) = SCOPE_EMPTY;
    }
};

void Playground::display() {
    display_map();
    display_scope();
    display_player();
    display_control_mode();
    clock = (clock + 1) % 60;
    if (clock % 30 == 0) delta_anim *= -1;
};

void Playground::display_control_mode() {
    std::string text = cameraMode ? "O | CAMERA MODE" : "X | PLAY MODE";
    sf::Color color = cameraMode ? sf::Color::Blue : sf::Color::Red;
    sf::Color shade;
    shade.r = 0;
    shade.g = 0;
    shade.b = 0;
    shade.a = 100;

    sf::RectangleShape back(sf::Vector2f(cameraMode? 500: 450, 50));
    back.setPosition(10, 10);
    back.setFillColor(shade);

    sf::Text label(text, config->theme.FONT);
    label.setCharacterSize(50);
    label.setPosition(10, 0);
    label.setFillColor(color);

    window->draw(back);
    window->draw(label);
};

void Playground::display_player() {
    int tilex = (config->window.width / camSize.x) - 1;
    int tiley = (config->window.height / camSize.y);
    int size = tilex < tiley ? tilex : tiley;

    for (int i = 0; i < chars.size(); i++) {
        sf::Text player(chars.at(i)->getP(), config->theme.FONT);
        player.setCharacterSize(size);
        player.setPosition(
            chars.at(i)->getX() * size + chars.at(i)->getX() + cam.x * size + 8,
            chars.at(i)->getY() * size + chars.at(i)->getY() + cam.y * size - 10 + delta_anim * 2
        );

        if (chars.at(i)->getP() == 'D') player.setFillColor(sf::Color::Green);
        else player.setFillColor(config->theme.colors.base);

        if (i == w) {
            sf::Color shade;
            shade.b = 255;
            shade.r = 0;
            shade.g = 0;
            shade.a = 150;
            player.setOutlineThickness(4);
            player.setOutlineColor(shade);
        };

        window->draw(player);
    };
};

void Playground::display_scope() {
    int tilex = (config->window.width / camSize.x) - 1;
    int tiley = (config->window.height / camSize.y);
    int size = tilex < tiley ? tilex : tiley;
    for (int camy = 0; camy < scope_map.size(); camy++) {
        for (int camx = 0; camx < scope_map.at(0).size(); camx++) if (scope_map.at(camy).at(camx)) {
            int TileValue = scope_map.at(camy).at(camx);

            sf::Color shade_blue;
            shade_blue.r = 0;
            shade_blue.g = 0;
            shade_blue.b = 255;
            shade_blue.a = 50;

            sf::Color shade_white;
            shade_white.r = 255;
            shade_white.g = 255;
            shade_white.b = 255;
            shade_white.a = 50;

            sf::Color shade_red;
            shade_red.r = 255;
            shade_red.g = 0;
            shade_red.b = 0;
            shade_red.a = 50;

            sf::Color tile_color = TileValue == SCOPE_ONGO
                ? shade_blue
                : TileValue == SCOPE_ALLY
                ? shade_white
                : shade_red;

            sf::RectangleShape tile(sf::Vector2f(size, size));
            tile.setFillColor(tile_color);
            tile.setPosition(camx * size + camx + cam.x * size, camy * size + camy + cam.y * size);
            window->draw(tile);
        };
    };
};

void Playground::display_map() {
    int tilex = (config->window.width / camSize.x) - 1;
    int tiley = (config->window.height / camSize.y);
    int size = tilex < tiley ? tilex : tiley;
    for (int camy = 0; camy < map.size(); camy++) {
        for (int camx = 0; camx < map.at(0).size(); camx++) {
            int TileValue = map.at(camy).at(camx);
            sf::Color tile_color = TileValue == 1
                ? sf::Color::Green
                : sf::Color::Black;

            sf::RectangleShape tile(sf::Vector2f(size, size));
            tile.setFillColor(tile_color);
            tile.setOutlineColor(sf::Color::White);
            tile.setOutlineThickness(1);
            tile.setPosition(camx * size + camx + cam.x * size, camy * size + camy + cam.y * size);
            window->draw(tile);
        };
    };
};


ViewRequest Playground::capture(Key k) {
    switch (k) {
    case sf::Keyboard::Escape: {
        return ViewRequest("", ID, "#mainmenu", true);
    };
    case sf::Keyboard::F: {
        cameraMode = !cameraMode;
        break;
    };
    case sf::Keyboard::Space: {
        if (!cameraMode) {
            chars.at(w)->changeMovementMode();

            if (chars.at(w)->onMovementMode()) chars.at(w)->descope();
        }
        break;
    }
    case sf::Keyboard::W: {
        if (cameraMode) {
            cam.y++;
        }
        else if (chars.at(w)->onMovementMode()) {
            chars.at(w)->move(0, -1);
        }
        else {
            chars.at(w)->scope(0, -1);
        };
        break;
    };
    case sf::Keyboard::S: {
        if (cameraMode) {
            cam.y--;
        }
        else if (chars.at(w)->onMovementMode()) {
            chars.at(w)->move(0, 1);
        }
        else {
            chars.at(w)->scope(0, 1);
        };
        break;
    };
    case sf::Keyboard::A: {
        if (cameraMode) {
            cam.x++;
        }
        else if (chars.at(w)->onMovementMode()) {
            chars.at(w)->move(-1, 0);
        }
        else {
            chars.at(w)->scope(-1, 0);
        };
        break;
    };
    case sf::Keyboard::D: {
        if (cameraMode) {
            cam.x--;
        }
        else if (chars.at(w)->onMovementMode()) {
            chars.at(w)->move(1, 0);
        }
        else {
            chars.at(w)->scope(1, 0);
        };
        break;
    };
    case sf::Keyboard::Q: {
        if (cameraMode) {
            camSize.x += 2;
            camSize.y += 1;
        }
        else {
            if (w == 0) w = chars.size() - 1;
            else w--;
        };
        break;
    };
    case sf::Keyboard::E: {
        if (cameraMode) {
            if (camSize.x >= 3 && camSize.y >= 2) {
                camSize.x -= 2;
                camSize.y -= 1;
            }
        }
        else {
            w = (w + 1) % chars.size();
        };
        break;
    };
    };
    return ViewRequest(false);
};