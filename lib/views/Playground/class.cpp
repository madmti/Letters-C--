#include "class.hpp"

Playground::Playground(std::string _id, Config_type* _config, Texture_config* _texture) : View(_id), all_chars{ new Char_P(2, 5, true), new Char_C(5, 5, true), new Char_X(1, 1, true), new Char_D(3, 3, false) } {
    cameraMode = true;
    w = 0;
    clock = 0;
    delta_anim = 1;
    config = _config;
    textures = _texture;
    tile_size = textures->tiles.tile_size;
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
    getPlayable();
    getConfig();
};

Playground::~Playground() {
    int n_chars = all_chars.size();
    for (int i = 0; i < n_chars; i++) {
        delete all_chars.at(i);
    };
    all_chars.clear();
    notPlayable_chars.clear();
    playable_chars.clear();
};

void Playground::getConfig() {
    for (int i = 0; i < all_chars.size(); i++) {
        all_chars.at(i)->setMaps(&map, &scope_map);
        all_chars.at(i)->place();
    };
};

void Playground::getPlayable() {
    for (int i = 0; i < all_chars.size(); i++)
        if (all_chars.at(i)->isPlayable())
            playable_chars.push_back(all_chars.at(i));
        else notPlayable_chars.push_back(all_chars.at(i));
};

void Playground::getMap() {
    map.assign(mapSize.y, std::vector<int>(mapSize.x, 0));
    scope_map.assign(mapSize.y, std::vector<int>(mapSize.x, 0));

    for (int y = 0; y < map.size(); y++) for (int x = 0; x < map.at(0).size(); x++) {
        if (x == 0 || x == 31 || y == 0 || y == 17 || x % 4 == 0 && y % 4 == 0) map.at(y).at(x) = MAP_WALL_0;
        else map.at(y).at(x) = MAP_FLOOR_0;

        scope_map.at(y).at(x) = SCOPE_EMPTY;
    };

    sf::Vector2i map_frame_size = sf::Vector2i(
        (tile_size.x + 1) * map.at(0).size(),
        (tile_size.y + 1) * map.size()
    );
    map_frame.setConfig(sf::Vector2i(50, 50), map_frame_size);
    map_frame.setSize(sf::Vector2i(1920, 1080));
    char_frame.setConfig(sf::Vector2i(0, 0), map_frame_size);
};

void Playground::clear() {
    char_frame.clear();
    map_frame.clear();
    frame.clear();
};

void Playground::display() {
    display_map();
    //display_scope();
    display_player(notPlayable_chars, false);
    display_player(playable_chars, true);
    map_frame.draw(char_frame.getSprite());
    frame.draw(map_frame.getSprite());
    display_control_mode();
    display_char_select();
};

void Playground::display_char_select() {
    int l_idx = prev_char_idx(w);
    int r_idx = next_char_idx(w);

    char l_char = playable_chars.at(l_idx)->getP();
    char act_char = playable_chars.at(w)->getP();
    char r_char = playable_chars.at(r_idx)->getP();

    sf::Text l_select(l_char, config->theme.FONT);
    l_select.setCharacterSize(40);
    l_select.setFillColor(sf::Color::Blue);
    l_select.setPosition(20, 95);

    sf::Text act_select(act_char, config->theme.FONT);
    act_select.setCharacterSize(50);
    act_select.setFillColor(sf::Color::Blue);
    act_select.setPosition(60, 90);

    sf::Text r_select(r_char, config->theme.FONT);
    r_select.setCharacterSize(40);
    r_select.setFillColor(sf::Color::Blue);
    r_select.setPosition(110, 95);

    sf::Color shade;
    shade.r = 0;
    shade.g = 0;
    shade.b = 0;
    shade.a = 200;

    sf::Color shade_2;
    shade_2.b = 255;
    shade_2.r = 255;
    shade_2.g = 255;
    shade_2.a = 200;
    act_select.setOutlineThickness(4);
    act_select.setOutlineColor(shade_2);

    sf::RectangleShape back(sf::Vector2f(140, 50));
    back.setPosition(10, 100);
    back.setFillColor(shade);

    frame.draw(back);
    frame.draw(l_select);
    frame.draw(act_select);
    frame.draw(r_select);
};

void Playground::display_control_mode() {
    std::string text = cameraMode ? "O | CAMERA MODE" : "X | PLAY MODE";
    sf::Color color = cameraMode ? sf::Color::Blue : sf::Color::Red;
    sf::Color shade;
    shade.r = 0;
    shade.g = 0;
    shade.b = 0;
    shade.a = 100;

    sf::RectangleShape back(sf::Vector2f(cameraMode ? 500 : 450, 50));
    back.setPosition(10, 10);
    back.setFillColor(shade);

    sf::Text label(text, config->theme.FONT);
    label.setCharacterSize(50);
    label.setPosition(10, 0);
    label.setFillColor(color);

    frame.draw(back);
    frame.draw(label);
};

void Playground::display_player(std::vector<Character*> char_list, bool playable) {
    for (int i = 0; i < char_list.size(); i++) {
        Character* actual = char_list.at(i);

        sf::Text player(actual->getP(), config->theme.FONT);
        player.setCharacterSize(tile_size.y < tile_size.x ? tile_size.y : tile_size.x);
        player.setPosition(
            actual->getX() * (tile_size.x + 1),
            actual->getY() * (tile_size.y + 1)
        );

        if (!playable) player.setFillColor(sf::Color::Green);
        else player.setFillColor(config->theme.colors.base);

        if (i == w && playable) {
            sf::Color shade;
            shade.b = 255;
            shade.r = 0;
            shade.g = 0;
            shade.a = 150;
            player.setOutlineThickness(2);
            player.setOutlineColor(shade);
        };
        char_frame.draw(player);
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
            frame.draw(tile);
        };
    };
};

void Playground::display_map() {
    for (int dy = 0; dy < map.size(); dy++) {
        for (int dx = 0; dx < map.at(0).size(); dx++) {
            int TileValue = map.at(dy).at(dx);
            sf::Texture tile_texture = TileValue == MAP_WALL_0
                ? textures->tiles.map_wall_0
                : textures->tiles.map_floor_0;

            sf::Sprite tile_sprite(tile_texture);
            tile_sprite.setPosition(
                dx * (tile_size.x + 1),
                dy * (tile_size.y + 1)
            );
            sf::RectangleShape outline(sf::Vector2f(tile_size.x, tile_size.y));
            outline.setFillColor(sf::Color::Transparent);
            outline.setOutlineThickness(1);
            outline.setOutlineColor(sf::Color::Black);
            outline.setPosition(
                dx * (tile_size.x + 1),
                dy * (tile_size.y + 1)
            );
            map_frame.draw(tile_sprite);
            map_frame.draw(outline);

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
            playable_chars.at(w)->changeMovementMode();

            if (playable_chars.at(w)->onMovementMode()) playable_chars.at(w)->descope();
        }
        break;
    }
    case sf::Keyboard::W: {
        if (cameraMode) {
            cam.y++;
            map_frame.move(0, 50);
        }
        else if (playable_chars.at(w)->onMovementMode()) {
            playable_chars.at(w)->move(0, -1);
        }
        else {
            playable_chars.at(w)->scope(0, -1);
        };
        break;
    };
    case sf::Keyboard::S: {
        if (cameraMode) {
            cam.y--;
            map_frame.move(0, -50);
        }
        else if (playable_chars.at(w)->onMovementMode()) {
            playable_chars.at(w)->move(0, 1);
        }
        else {
            playable_chars.at(w)->scope(0, 1);
        };
        break;
    };
    case sf::Keyboard::A: {
        if (cameraMode) {
            cam.x++;
            map_frame.move(50, 0);
        }
        else if (playable_chars.at(w)->onMovementMode()) {
            playable_chars.at(w)->move(-1, 0);
        }
        else {
            playable_chars.at(w)->scope(-1, 0);
        };
        break;
    };
    case sf::Keyboard::D: {
        if (cameraMode) {
            cam.x--;
            map_frame.move(-50, 0);
        }
        else if (playable_chars.at(w)->onMovementMode()) {
            playable_chars.at(w)->move(1, 0);
        }
        else {
            playable_chars.at(w)->scope(1, 0);
        };
        break;
    };
    case sf::Keyboard::Q: {
        if (cameraMode) {
            camSize.x += 4;
            camSize.y += 2;
            cam.x += 2;
            cam.y += 1;
            map_frame.zoomOut();
        }
        else {
            w = prev_char_idx(w);
        };
        break;
    };
    case sf::Keyboard::E: {
        if (cameraMode) {
            if (camSize.x >= 5 && camSize.y >= 3) {
                camSize.x -= 4;
                camSize.y -= 2;
                cam.x -= 2;
                cam.y -= 1;
                map_frame.zoomIn();
            }
        }
        else {
            w = next_char_idx(w);
        };
        break;
    };
    };
    return ViewRequest(false);
};

int Playground::prev_char_idx(int actual) {
    if (actual == 0) return playable_chars.size() - 1;
    else return actual - 1;
};

int Playground::next_char_idx(int actual) {
    return (actual + 1) % playable_chars.size();
};