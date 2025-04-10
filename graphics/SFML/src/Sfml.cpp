/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

arcade::Sfml::Sfml() {
    _window.create(sf::VideoMode(1000, 1000), "Arcade SFML");
    _window.setFramerateLimit(60);

    if (!_font.loadFromFile("./lib/assets/arcade_sfml/arial.ttf")) {
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
            events.events.push_back(A_KEY_C);
        }
        else if (sfEvent.type == sf::Event::KeyPressed) {
            switch (sfEvent.key.code) {
                case sf::Keyboard::Z:
                    events.events.push_back(A_KEY_Z);
                    break;
                case sf::Keyboard::S:
                    events.events.push_back(A_KEY_S);
                    break;
                case sf::Keyboard::Q:
                    events.events.push_back(A_KEY_Q);
                    break;
                case sf::Keyboard::D:
                    events.events.push_back(A_KEY_D);
                    break;
                default:
                    break;
            }
        }
    }
    return events;
}

void arcade::Sfml::display(data_t data) {
    _window.clear(sf::Color::Black);

    for (entity_t bg : data.bg) {
        sf::Sprite sprite;
        sf::Texture texture;
        texture.loadFromFile(bg.asset);
        sprite.setTexture(texture);
        sprite.setPosition(1000 / bg.pos.x, 1000 / bg.pos.y);
        sf::FloatRect spriteBounds = sprite.getLocalBounds();
        sf::Vector2f scale;
        scale.x = (1000 / 100 * bg.size.x) / spriteBounds.width;
        scale.y = (1000 / 100 * bg.size.y) / spriteBounds.height;
        sprite.setScale(scale);
        _window.draw(sprite);
    }

    for (entity_t objects : data.objects) {
        sf::Sprite sprite;
        sf::Texture texture;
        texture.loadFromFile(objects.asset);
        sprite.setTexture(texture);
        sprite.setPosition(1000 / objects.pos.x, 1000 / objects.pos.y);
        sf::FloatRect spriteBounds = sprite.getLocalBounds();
        sf::Vector2f scale;
        scale.x = (1000 / 100 * objects.size.x) / spriteBounds.width;
        scale.y = (1000 / 100 * objects.size.y) / spriteBounds.height;
        sprite.setScale(scale);
        _window.draw(sprite);
    }

    for (entity_t ui : data.ui) {
        sf::Sprite sprite;
        sf::Texture texture;
        texture.loadFromFile(ui.asset);
        sprite.setTexture(texture);
        sprite.setPosition(1000 / ui.pos.x, 1000 / ui.pos.y);
        sf::FloatRect spriteBounds = sprite.getLocalBounds();
        sf::Vector2f scale;
        scale.x = (1000 / 100 * ui.size.x) / spriteBounds.width;
        scale.y = (1000 / 100 * ui.size.y) / spriteBounds.height;
        sprite.setScale(scale);
        _window.draw(sprite);
    }

    for (text_t txt : data.texts) {
        sf::Text text;
        text.setFont(_font);
        text.setString(txt.value);
        text.setCharacterSize(txt.fontSize);
        text.setFillColor((const sf::Color&)txt.color);
        text.setPosition(1000 / 100 * txt.pos.x, 1000 / 100 * txt.pos.y);
        _window.draw(text);
    }
    
    _window.display();
}