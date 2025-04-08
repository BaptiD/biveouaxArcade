/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

arcade::Sfml::Sfml() {
    window.create(sf::VideoMode(800, 600), "Arcade SFML");
    window.setFramerateLimit(60);
}

arcade::Sfml::~Sfml() {
    window.close();
}

event_t arcade::Sfml::getEvent() {
    event_t events;
    sf::Event sfEvent;
    while (window.pollEvent(sfEvent)) {
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
    window.clear(sf::Color::Black);
    
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error: Can't load font" << std::endl;
        } else {
            fontLoaded = true;
        }
    }
    for (const auto& txt : data.texts) {
        sf::Text sfText;
        sfText.setFont(font);
        sfText.setString(txt.value);
        sfText.setCharacterSize(24);
        sfText.setFillColor(sf::Color::White);
        sfText.setPosition(txt.pos.x, txt.pos.y);
        window.draw(sfText);
    }
    
    window.display();
}