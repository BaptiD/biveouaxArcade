/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

const std::map<int, event_e> arcade::Sfml::_conversionMap = {
    {sf::Keyboard::Escape, A_KEY_ESC},
    {sf::Keyboard::Enter, A_KEY_ENTER},
    {sf::Keyboard::Space, A_KEY_SPACE},
    {sf::Keyboard::Delete, A_KEY_DEL},
    {sf::Keyboard::Tab, A_KEY_TAB},
    {sf::Keyboard::Up, A_KEY_UP},
    {sf::Keyboard::Down, A_KEY_DOWN},
    {sf::Keyboard::Left, A_KEY_LEFT},
    {sf::Keyboard::Right, A_KEY_RIGHT},
    {sf::Keyboard::F1, A_KEY_F1},
    {sf::Keyboard::F2, A_KEY_F2},
    {sf::Keyboard::F3, A_KEY_F3},
    {sf::Keyboard::F4, A_KEY_F4},
    {sf::Keyboard::F5, A_KEY_F5},
    {sf::Keyboard::F6, A_KEY_F6},
    {sf::Keyboard::F7, A_KEY_F7},
    {sf::Keyboard::F8, A_KEY_F8},
    {sf::Keyboard::F9, A_KEY_F9},
    {sf::Keyboard::F10, A_KEY_F10},
    {sf::Keyboard::F11, A_KEY_F11},
    {sf::Keyboard::F12, A_KEY_F12},
    {sf::Keyboard::A, A_KEY_A},
    {sf::Keyboard::B, A_KEY_B},
    {sf::Keyboard::C, A_KEY_C},
    {sf::Keyboard::D, A_KEY_D},
    {sf::Keyboard::E, A_KEY_E},
    {sf::Keyboard::F, A_KEY_F},
    {sf::Keyboard::G, A_KEY_G},
    {sf::Keyboard::H, A_KEY_H},
    {sf::Keyboard::I, A_KEY_I},
    {sf::Keyboard::J, A_KEY_J},
    {sf::Keyboard::K, A_KEY_K},
    {sf::Keyboard::L, A_KEY_L},
    {sf::Keyboard::M, A_KEY_M},
    {sf::Keyboard::N, A_KEY_N},
    {sf::Keyboard::O, A_KEY_O},
    {sf::Keyboard::P, A_KEY_P},
    {sf::Keyboard::Q, A_KEY_Q},
    {sf::Keyboard::R, A_KEY_R},
    {sf::Keyboard::S, A_KEY_S},
    {sf::Keyboard::T, A_KEY_T},
    {sf::Keyboard::U, A_KEY_U},
    {sf::Keyboard::V, A_KEY_V},
    {sf::Keyboard::W, A_KEY_W},
    {sf::Keyboard::X, A_KEY_X},
    {sf::Keyboard::Y, A_KEY_Y},
    {sf::Keyboard::Z, A_KEY_Z}
};

arcade::Sfml::Sfml() {
    _window.create(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Arcade SFML");

    if (!_font.loadFromFile("./lib/assets/arcade_menu/font/arcade.ttf")) {
        std::cerr << "Error: Can't load font" << std::endl;
    }
}

arcade::Sfml::~Sfml() {
    _window.close();
}

event_t arcade::Sfml::getEvent() {
    event_t events;
    sf::Event sfEvent;

    while (_window.pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            events.events.push_back(A_KEY_F4);
        } else if (sfEvent.type == sf::Event::KeyPressed) {
            for (std::map<int, event_e>::const_iterator it = _conversionMap.begin(); it != _conversionMap.end(); ++it) {
                if (it->first == sfEvent.key.code) {
                    events.events.push_back(it->second);
                }
            }
        }
    }
    return events;
}

sf::Sprite arcade::Sfml::rotateSprite(sf::Sprite sprite, int direction) {
    if (direction == UP)
        return sprite;
    sf::Vector2f size = sprite.getLocalBounds().getSize();
    if (direction == DOWN) {
        sprite.setRotation(180);
        sprite.setOrigin(size);
    } else if (direction == RIGHT) {
        sprite.setRotation(90);
        sprite.setOrigin({0, size.y});
    } else if (direction == LEFT) {
        sprite.setRotation(-90);
        sprite.setOrigin({size.x, 0});
    }
    return sprite;
}

void arcade::Sfml::drawSprites(std::vector<entity_t> entities) {
    for (entity_t entity : entities) {
        if (entity.asset == "") {
            sf::RectangleShape rectangle({static_cast<float>(WIN_SIZE_X / 100 * entity.size.x), static_cast<float>(WIN_SIZE_Y / 100 * entity.size.y)});
            rectangle.setPosition(WIN_SIZE_X / 100 * entity.pos.x, WIN_SIZE_Y / 100 * entity.pos.y);
            sf::Color color;
            color.r = entity.color.r;
            color.g = entity.color.g;
            color.b = entity.color.b;
            color.a = entity.color.a;
            rectangle.setFillColor(color);
            _window.draw(rectangle);
        } else {
            sf::Sprite sprite;
            sf::Texture texture;
            texture.loadFromFile(entity.asset);
            sprite.setTexture(texture);
            sprite.setPosition(WIN_SIZE_X / 100 * entity.pos.x, WIN_SIZE_Y / 100 * entity.pos.y);
            sf::FloatRect spriteBounds = sprite.getLocalBounds();
            sf::Vector2f scale;
            scale.x = (WIN_SIZE_X / 100 * entity.size.x) / spriteBounds.width;
            scale.y = (WIN_SIZE_Y / 100 * entity.size.y) / spriteBounds.height;
            sprite.setScale(scale);
            sprite = rotateSprite(sprite, entity.direction);
            _window.draw(sprite);
        }
    }
}

void arcade::Sfml::drawTexts(std::vector<text_t> texts) {
    for (text_t txt : texts) {
        sf::Text text;
        text.setFont(_font);
        text.setString(txt.value);
        text.setCharacterSize(txt.fontSize);
        sf::Color color;
        color.r = txt.color.r;
        color.g = txt.color.g;
        color.b = txt.color.b;
        color.a = txt.color.a;
        text.setFillColor(color);
        text.setPosition(WIN_SIZE_X / 100 * txt.pos.x, WIN_SIZE_Y / 100 * txt.pos.y);
        _window.draw(text);
    }
}

void arcade::Sfml::display(data_t data) {
    _window.clear(sf::Color::Black);

    drawSprites(data.bg);
    drawSprites(data.objects);
    drawSprites(data.ui);
    drawTexts(data.texts);
    _window.display();
}