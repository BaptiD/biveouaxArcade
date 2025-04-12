/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.cpp
*/

#include <unistd.h>
#include "Sfml.hpp"

const std::map<int, event_e> arcade::Sfml::_conversionKeyboard = {
    {sf::Keyboard::Escape, A_KEY_ESC},
    {sf::Keyboard::Enter, A_KEY_ENTER},
    {sf::Keyboard::Space, A_KEY_SPACE},
    {sf::Keyboard::Delete, A_KEY_DEL},
    {sf::Keyboard::Tab, A_KEY_TAB},
    {sf::Keyboard::LControl, A_KEY_CTRL},
    {sf::Keyboard::RControl, A_KEY_CTRL},
    {sf::Keyboard::LShift, A_KEY_SHIFT},
    {sf::Keyboard::RShift, A_KEY_SHIFT},
    {sf::Keyboard::LAlt, A_KEY_ALT},
    {sf::Keyboard::RAlt, A_KEY_ALT},
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

const std::map<int, event_e> arcade::Sfml::_conversionMouse = {
    {sf::Mouse::Button::Left, A_MOUSE_LEFT},
    {sf::Mouse::Button::Right, A_MOUSE_RIGHT},
    {sf::Mouse::Button::Middle, A_MOUSE_MIDDLE},
    {sf::Mouse::Wheel::HorizontalWheel, A_MOUSE_HORIZONTALWHEEL},
    {sf::Mouse::Wheel::HorizontalWheel, A_MOUSE_VERTICALWHEEL},
    {sf::Mouse::Button::XButton1, A_MOUSE_XBUTTON1},
    {sf::Mouse::Button::XButton2, A_MOUSE_XBUTTON2},
};


arcade::Sfml::Sfml() {
    _window.create(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Arcade SFML");
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
            for (std::map<int, event_e>::const_iterator it = _conversionKeyboard.begin(); it != _conversionKeyboard.end(); ++it) {
                if (it->first == sfEvent.key.code) {
                    events.events.push_back(it->second);
                }
            }
        } else if (sfEvent.type == sf::Event::MouseButtonPressed) {
            for (std::map<int, event_e>::const_iterator it = _conversionMouse.begin(); it != _conversionMouse.end(); ++it) {
                if (it->first == sfEvent.key.code) {
                    events.events.push_back(it->second);
                }
            }
        } else if (sfEvent.type == sf::Event::MouseMoved) {
            events.events.push_back(A_MOUSE_MOVE);
        }

    }
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window));
    events.mPos.x = mousePos.x / static_cast<float>(_window.getSize().x) * 100;
    events.mPos.y = mousePos.y / static_cast<float>(_window.getSize().y) * 100;
    return events;
}

sf::Sprite arcade::Sfml::rotateSprite(sf::Sprite sprite, int direction, sf::Vector2f size) {
    if (direction == UP)
        return sprite;
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
            rectangle.setFillColor((sf::Color){entity.color.r, entity.color.g, entity.color.b, entity.color.a});
            _window.draw(rectangle);
        } else {
            if (access(entity.asset.c_str(), F_OK) == -1) {
                sf::RectangleShape rectangle({static_cast<float>(WIN_SIZE_X / 100 * entity.size.x), static_cast<float>(WIN_SIZE_Y / 100 * entity.size.y)});
                rectangle.setPosition(WIN_SIZE_X / 100 * entity.pos.x, WIN_SIZE_Y / 100 * entity.pos.y);
                rectangle.setFillColor((sf::Color){entity.color.r, entity.color.g, entity.color.b, entity.color.a});
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
                sf::Vector2f size = static_cast<sf::Vector2f>(texture.getSize());
                sprite = rotateSprite(sprite, entity.direction, size);
                _window.draw(sprite);
            }
        }
    }
}

void arcade::Sfml::drawTexts(std::vector<text_t> texts) {
    for (text_t txt : texts) {
        sf::Font font;
        sf::Text text;
        if (access(txt.fontPath.c_str(), F_OK) != -1) {
            font.loadFromFile(txt.fontPath);
            text.setFont(font);
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
}

void arcade::Sfml::playMusic(std::vector<std::string> audios) {
    std::vector<sf::SoundBuffer> soundBuffers;

    for (const auto& path : audios) {
        _music.setVolume(10);
        _music.openFromFile(path);
        _music.play();
    }
}

void arcade::Sfml::display(data_t data) {
    _window.clear(sf::Color::Black);

    drawSprites(data.bg);
    drawSprites(data.objects);
    drawSprites(data.ui);
    drawTexts(data.texts);
    playMusic(data.audios);
    _window.display();
}