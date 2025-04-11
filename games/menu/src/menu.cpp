/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.cpp
*/

#include <stddef.h>
#include <filesystem>
#include <iostream>

#include "menu.hpp"

arcade::Menu::Menu()
{
    getLibs();
    buildMenu();
}

void arcade::Menu::handleEvent(event_t events)
{
    SET_BASE_GAME(this);
    if (_gamePaths.empty() || _graphicPaths.empty())
        return;
    if (!events.events.empty()) {
        event_e event = events.events[0];
        if (event == A_KEY_ESC || event == A_KEY_F4)
            _state.libs.game.clear();
        if (event == A_KEY_Z || event == A_KEY_UP)
            _gameIndex = (_gameIndex - 1) < 0 ? 0 : (_gameIndex - 1);
        if (event == A_KEY_S || event == A_KEY_DOWN)
            _gameIndex = (_gameIndex + 1) > (_gamePaths.size() - 1) ? _gameIndex : _gameIndex + 1;
        if (event == A_KEY_Q || event == A_KEY_LEFT)
            _graphicIndex = (_graphicIndex - 1) < 0 ? 0 : (_graphicIndex - 1);
        if (event == A_KEY_D || event == A_KEY_RIGHT)
            _graphicIndex = (_graphicIndex + 1) > (_graphicPaths.size() - 1) ? _graphicIndex : _graphicIndex + 1;
        if (event == A_KEY_ENTER || event == A_KEY_SPACE) {
            _state.libs.game = _gamePaths[_gameIndex];
            _state.libs.graphic = _graphicPaths[_graphicIndex];
        }
        events.events.clear();
    }
    buildMenu();
}

data_t arcade::Menu::update(void)
{
    return _state;
}

void arcade::Menu::getLibs(void)
{
    for (const auto &lib : std::filesystem::directory_iterator(PATH_LIBS)) {
        tryLib<arcade::IGame>(lib.path());
        tryLib<arcade::IGraphic>(lib.path());
    }
}

void arcade::Menu::buildMenu()
{
    _state.texts.clear();

    int y = 5;
    _state.texts.push_back({{50, (float)(y += OFST_PERCENTAGE)}, 30, "--- MENU ---", FONT_PATH, WHITE});
    y += OFST_PERCENTAGE * 2;
    _state.texts.push_back({{40, (float)(y += OFST_PERCENTAGE)}, 30, "Games:", FONT_PATH, WHITE});
    y += OFST_PERCENTAGE;
    //set a cursor to see what is the game selected
    if (!_gamePaths.empty()) {
        for (std::size_t i = 0; i < _gamePaths.size(); i++) {
            std::string prefix = (i == _gameIndex) ? "> " : "  ";
            _state.texts.push_back({{45, (float)(y += OFST_PERCENTAGE)}, 20, prefix + _gamePaths[i], FONT_PATH, WHITE});
        }
    } else {
        _state.texts.push_back({{45, (float)(y += OFST_PERCENTAGE)}, 20, "No game in lib directory", FONT_PATH, WHITE});
    }
    y += OFST_PERCENTAGE;
    _state.texts.push_back({{40, (float)(y += OFST_PERCENTAGE)}, 30, "Graphic libraries:", FONT_PATH, WHITE});
    y += OFST_PERCENTAGE;
    //set a cursor to see what is the game selected
    if (!_graphicPaths.empty()) {
        for (std::size_t i = 0; i < _graphicPaths.size(); i++) {
            std::string prefix = (i == _graphicIndex) ? "> " : "  ";
            _state.texts.push_back({{45, (float)(y += OFST_PERCENTAGE)}, 20, prefix + _graphicPaths[i], FONT_PATH, WHITE});
        }
    } else {
        _state.texts.push_back({{45, (float)(y += OFST_PERCENTAGE)}, 20, "No graphic library in lib directory", FONT_PATH, WHITE});
    }
}
