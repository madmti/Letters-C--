#include "class.hpp"

Playground::~Playground() {
    int n_chars = all_chars.size();
    for (int i = 0; i < n_chars; i++) {
        delete all_chars.at(i);
    };
    all_chars.clear();
    notPlayable_chars.clear();
    playable_chars.clear();
};

Playground::Playground(std::string _id) : View(_id), all_chars{
    new Char_P(true),
    new Char_C(true),
    new Char_X(true),
    new Char_D(false)
} {
    cameraMode = true;
    w = 0;
    map_name_idx = 0;
    req_keys = std::vector<Key>{
        sf::Keyboard::W,
        sf::Keyboard::A,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::Space,
        sf::Keyboard::Escape,
        sf::Keyboard::E,
        sf::Keyboard::Q,
        sf::Keyboard::H,
        sf::Keyboard::J
    };
    onSelectMapMenu = true;
    searchMaps();
};

void Playground::loadMap() {
    if (maps_names.empty()) return;
    getMap(maps_names.at(map_name_idx));
    setupChars();
    onSelectMapMenu = false;
};

void Playground::searchMaps() {
    maps_names = std::vector<std::string>{ "ice_0", "land_0", "steel_0" };
};

void Playground::getMap(std::string map_name) {
    map.load(map_name);

    tile_size = map.getTileSize();

    sf::Vector2i map_frame_size = sf::Vector2i(
        (tile_size.x + 1) * map.getDimX(),
        (tile_size.y + 1) * map.getDimY()
    );
    sf::Vector2i char_delta(5, -8);
    sf::Vector2i delta_map = (sf::Vector2i(config->window.width, config->window.height) / 2) - map_frame_size;

    map_frame.setConfig(delta_map, map_frame_size);
    map_frame.setScale(2);
    char_frame.setConfig(char_delta, map_frame_size);
};

void Playground::setupChars() {
    playable_chars.clear();
    notPlayable_chars.clear();
    int n_chars = all_chars.size();
    std::vector<sf::Vector2i> spawnBlue = map.getSpawnBlue();
    std::vector<sf::Vector2i> spawnRed = map.getSpawnRed();
    for (int i = 0; i < n_chars; i++) {
        Character* ch = all_chars.at(i);
        if (ch->isPlayable()) {
            if (spawnBlue.empty()) continue;
            ch->setPos(spawnBlue.back());
            spawnBlue.pop_back();
            playable_chars.push_back(ch);
        }
        else {
            if (spawnRed.empty()) continue;
            ch->setPos(spawnRed.back());
            spawnRed.pop_back();
            notPlayable_chars.push_back(ch);
        };
        ch->setMap(&map);
        ch->place();
    };
};

void Playground::clear() {
    if (!onSelectMapMenu) {
        char_frame.clear();
        map_frame.clear();
    };
    frame.clear();
};

void Playground::display() {
    if (!onSelectMapMenu) {
        display_map();
        display_player(notPlayable_chars, false);
        display_player(playable_chars, true);
        map_frame.draw(char_frame.getSprite());
        frame.draw(map_frame.getSprite());
        display_control_mode();
        display_char_select();
    }
    else {
        display_select_menu();
    };
};

void Playground::display_select_menu() {
    if (maps_names.empty()) {
        sf::Text error("No maps detected", config->theme.FONT);
        error.setCharacterSize(100);
        error.setFillColor(sf::Color::Red);
        error.setPosition(500, 500);
        frame.draw(error);
        return;
    };

    sf::Text title("CHOOSE MAP", config->theme.FONT);
    title.setCharacterSize(80);
    title.setFillColor(config->theme.colors.base);
    title.setPosition(10, 0);

    sf::Text name(maps_names.at(map_name_idx), config->theme.FONT);
    name.setCharacterSize(50);
    name.setFillColor(config->theme.colors.base);
    name.setPosition(500, 500);

    frame.draw(title);
    frame.draw(name);
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
    shade.a = 200;

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
        player.setOutlineThickness(2);

        if (!playable) player.setFillColor(sf::Color::Red);
        else if (i == w) {
            sf::Color sel_col;
            sel_col.b = 255;
            sel_col.r = 0;
            sel_col.g = 0;
            sel_col.a = 200;
            player.setOutlineColor(sel_col);
        }
        else player.setFillColor(sf::Color::Blue);

        float perCentLife = actual->getPercentageLife();

        float startRed = tile_size.x * perCentLife;

        sf::RectangleShape life_green(sf::Vector2f(startRed, 5));
        life_green.setFillColor(sf::Color::Green);
        life_green.setPosition(
            actual->getX() * (tile_size.x + 1),
            actual->getY() * (tile_size.y + 1)
        );

        sf::RectangleShape life_red(sf::Vector2f(tile_size.x - startRed, 5));
        life_red.setFillColor(sf::Color::Red);
        life_red.setPosition(
            actual->getX() * (tile_size.x + 1) + startRed,
            actual->getY() * (tile_size.y + 1)
        );

        char_frame.draw(player);
        map_frame.draw(life_green);
        map_frame.draw(life_red);
    };
};

void Playground::display_scope(int dx, int dy) {
    int TileValue = map.get_scope(dx, dy);
    if (TileValue == SCOPE_EMPTY) return;

    sf::Color shade_blue;
    shade_blue.r = 0;
    shade_blue.g = 0;
    shade_blue.b = 255;
    shade_blue.a = 100;

    sf::Color shade_white;
    shade_white.r = 255;
    shade_white.g = 255;
    shade_white.b = 255;
    shade_white.a = 100;

    sf::Color shade_red;
    shade_red.r = 255;
    shade_red.g = 0;
    shade_red.b = 0;
    shade_red.a = 100;

    sf::Color tile_color = TileValue == SCOPE_ONGO
        ? shade_blue
        : TileValue == SCOPE_ALLY
        ? shade_white
        : shade_red;

    sf::RectangleShape tile(sf::Vector2f(tile_size.x, tile_size.y));
    tile.setFillColor(tile_color);
    tile.setPosition(
        dx * (tile_size.x + 1),
        dy * (tile_size.y + 1)
    );
    tile.setOutlineThickness(1);

    tile_color.a = 200;

    tile.setOutlineColor(tile_color);
    map_frame.draw(tile);
};

void Playground::display_map() {
    for (int dy = 0; dy < map.getDimY(); dy++) {
        for (int dx = 0; dx < map.getDimX(); dx++) {
            MAP_VALUES TileValue = map.get_map(dx, dy);

            sf::Sprite tile_sprite = map.getTexture(TileValue);
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
            display_scope(dx, dy);

        };
    };
};


ViewRequest Playground::capture(Key k) {
    if (!onSelectMapMenu) {
        capture_onPlay(k);
        return ViewRequest(false);
    };
    switch (k) {
    case sf::Keyboard::Escape: {
        return ViewRequest("", ID, "#mainmenu", true);
    };
    case sf::Keyboard::Space: {
        loadMap();
        break;
    };
    case sf::Keyboard::A: {
        map_name_idx = prev_map_idx(map_name_idx);
        break;
    };
    case sf::Keyboard::D: {
        map_name_idx = next_map_idx(map_name_idx);
        break;
    };
    };
    return ViewRequest(false);
};

void Playground::capture_onPlay(Key k) {
    switch (k) {
    case sf::Keyboard::Escape: {
        onSelectMapMenu = true;
        break;
    };
    case sf::Keyboard::Space: {
        cameraMode = !cameraMode;
        break;
    };
    case sf::Keyboard::J: {
        if (!cameraMode) {
            playable_chars.at(w)->changeMovementMode();

            if (playable_chars.at(w)->onMovementMode()) playable_chars.at(w)->descope();
        }
        break;
    };
    case sf::Keyboard::H: {
        if (playable_chars.at(w)->onMovementMode()) return;
        Damage Dmg = playable_chars.at(w)->doDamage();
        if (Dmg.targets.empty()) return;
        for (int i = 0; i < Dmg.targets.size(); i++) {
            int idx = findIdxCharsByPos(Dmg.targets.at(i));
            if (idx == -1) return;
            if (Dmg.isPercentage) all_chars.at(idx)->recvDamage_perCent(Dmg.dmg);
            else all_chars.at(idx)->recvDamage(Dmg.dmg);
        };
        break;
    };
    case sf::Keyboard::W: {
        if (cameraMode) {
            map_frame.move(0, 100);
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
            map_frame.move(0, -100);
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
            map_frame.move(100, 0);
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
            map_frame.move(-100, 0);
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
            map_frame.zoomOut();
        }
        else {
            w = prev_char_idx(w);
        };
        break;
    };
    case sf::Keyboard::E: {
        if (cameraMode) {
            map_frame.zoomIn();
        }
        else {
            w = next_char_idx(w);
        };
        break;
    };
    };
};

int Playground::prev_char_idx(int actual) {
    if (actual == 0) return playable_chars.size() - 1;
    else return actual - 1;
};

int Playground::next_char_idx(int actual) {
    return (actual + 1) % playable_chars.size();
};

int Playground::prev_map_idx(int actual) {
    if (actual == 0) return maps_names.size() - 1;
    else return actual - 1;
};

int Playground::next_map_idx(int actual) {
    return (actual + 1) % maps_names.size();
};

int Playground::findIdxCharsByPos(sf::Vector2i pos) {
    for (int i = 0; i < all_chars.size(); i++)
        if (all_chars.at(i)->getPos() == pos)
            return i;
    return -1;
};