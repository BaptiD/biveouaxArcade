/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.cpp
*/

#include <filesystem>
#include <iostream>

#include "menu.hpp"
#include "entity.hpp"
#include "dynamicLib.hpp"

arcade::Menu::Menu() {
    getLibs();
    buildMenu();
}

void arcade::Menu::handleEvent(event_t events) {
    if (_gamePaths.empty() || _graphicPaths.empty())
        return;
    if (!events.events.empty()) {
        event_e event = events.events[0];
        if (event == A_KEY_Z)
            _gameIndex = (_gameIndex - 1) < 0 ? 0 : (_gameIndex - 1);
        if (event == A_KEY_S)
            _gameIndex = (_gameIndex + 1) > (_gamePaths.size() - 1) ? _gameIndex : _gameIndex + 1;
        if (event == A_KEY_Q)
            _graphicIndex = (_graphicIndex - 1) < 0 ? 0 : (_graphicIndex - 1);
        if (event == A_KEY_D)
            _graphicIndex = (_graphicIndex + 1) > (_graphicPaths.size() - 1) ? _graphicIndex : _graphicIndex + 1;
        if (event == A_KEY_ENTER) {
            _state.libs.game = _gamePaths[_gameIndex];
            _state.libs.graphic = _graphicPaths[_graphicIndex];
        }
        events.events.clear();
    }
    buildMenu();
}

data_t arcade::Menu::update(void) {
    return _state;
}

std::vector<std::string> find_graphic(void) {
    void *handlegraph = nullptr;
    arcade::IGraphic *(*graphlib)(void) = nullptr;
    std::vector<std::string> paths;

    for (const auto &lib : std::filesystem::directory_iterator(PATH_LIBS)) {
        const std::string filename = lib.path();
        handlegraph = dlopen(filename.c_str(), RTLD_LAZY);
        if (handlegraph == NULL)
            continue;
        graphlib = (arcade::IGraphic *(*)())dlsym(handlegraph, "makeGraphic");
        if (graphlib == nullptr)
            continue;
        paths.push_back(filename);
        dlclose(handlegraph);
    }
    return paths;
}

std::vector<std::string> find_game(void) {
    void *handlegame = nullptr;
    arcade::IGame *(*gamelib)(void) = nullptr;
    std::vector<std::string> paths;

    for (const auto &lib : std::filesystem::directory_iterator(PATH_LIBS)) {
        const std::string filename = lib.path();
        handlegame = dlopen(filename.c_str(), RTLD_LAZY);
        if (handlegame == NULL)
            continue;
        gamelib = (arcade::IGame *(*)())dlsym(handlegame, "makeGame");
        if (gamelib == nullptr)
            continue;
        paths.push_back(filename);
        dlclose(handlegame);
    }
    return paths;
}

void arcade::Menu::getLibs(void) {
    _gamePaths = find_game();
    _graphicPaths = find_graphic();
}

void arcade::Menu::buildMenu() {
    _state.texts.clear();

    int y = 5;
    _state.texts.push_back({{2, 2}, 1, "--- MENU ---", FONT_PATH, WHITE});
    _state.texts.push_back({{2, 4}, 1, "Games:", FONT_PATH, WHITE});

    //set a cursor to see what is the game selected
    if (!_gamePaths.empty()) {
        for (std::size_t i = 0; i < _gamePaths.size(); i++) {
            std::string prefix = (i == _gameIndex) ? "> " : "  ";
            _state.texts.push_back({{4, (float)y++}, 1, prefix + _gamePaths[i], FONT_PATH, WHITE});
        }
    } else {
        _state.texts.push_back({{4, (float)y++}, 1, "No game in lib directory", FONT_PATH, WHITE});
    }
    y++;
    _state.texts.push_back({{2, (float)y++}, 1, "Graphic libraries:", FONT_PATH, WHITE});
    //set a cursor to see what is the game selected
    if (!_graphicPaths.empty()) {
        for (std::size_t i = 0; i < _graphicPaths.size(); i++) {
            std::string prefix = (i == _graphicIndex) ? "> " : "  ";
            _state.texts.push_back({{4, (float)y++}, 1, prefix + _graphicPaths[i], FONT_PATH, WHITE});
        }
    } else {
        _state.texts.push_back({{4, (float)y++}, 1, "No graphic library in lib directory", FONT_PATH, WHITE});
    }
}
