/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.cpp
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>

#include "tool.hpp"
#include "core.hpp"

arcade::core::core(std::string graphicPath)
{
    load(MENU_PATH_LIB, GAME_LIB);
    load(graphicPath, GRAPHIC_LIB);
    for (const auto &lib : std::filesystem::directory_iterator(PATH_LIBS)) {
        if (tryLib<IGraphic>(lib.path())) {
            if (!graphicPath.compare(lib.path()))
                _graphicIndex = _graphicPaths.size() - 1;
        } else
            tryLib<IGame>(lib.path());
    }
}

void arcade::core::load(std::string libPath, typeLib_e type)
{
    try {
        if (type == GAME_LIB) {
            _game.openLib(libPath);
        } else
            _graphic.openLib(libPath);
    } catch (arcade::dynLibError& e) {
        std::cerr << e.what() << std::endl;
        exit(ERROR);
    }
}

data_t arcade::core::setupNewGame(void)
{
    event_t events = CALL(_graphic)->getEvent();

    CALL(_game)->handleEvent(events);
    return CALL(_game)->update();
}

data_t arcade::core::checkLibUpdate(libPaths_t paths, data_t data)
{
    if (_updateGraphic == true) {
        _graphic.closeLib();
        load(_graphicPaths[_graphicIndex], GRAPHIC_LIB);
        _updateGraphic = false;
    } else if (_updateGame == true) {
        _game.closeLib();
        load(_gamePaths[_gameIndex], GAME_LIB);
        _updateGame = false;
        return setupNewGame();
    }
    if (!data.libs.graphic.empty() && paths.graphic.compare(data.libs.graphic)) {
        _graphic.closeLib();
        load(data.libs.graphic, GRAPHIC_LIB);
    }
    if (!data.libs.game.empty() && paths.game.compare(data.libs.game)) {
        _game.closeLib();
        load(data.libs.game, GAME_LIB);
        return setupNewGame();
    }
    return data;
}

int arcade::core::checkCoreEvents(event_t events)
{
    for (event_e &event : events.events) {
        if (event == A_KEY_DEL)
            return CORE_EXIT;
        if (event == A_KEY_A) {
            if (_graphicPaths.size() - 1 <= _graphicIndex)
                _graphicIndex = 0;
            else
                _graphicIndex += 1;
            _updateGraphic = true;
        }
        if (event == A_KEY_E) {
            if (_gamePaths.size() - 1 <= _gameIndex)
                _gameIndex = 0;
            else
                _gameIndex += 1;
            _updateGame = true;
        }
        if (event == A_KEY_R) {
            _game.closeLib();
            load(_gamePaths[_gameIndex], GAME_LIB);
        }
    }
    return 0;
}

void arcade::core::run(void)
{
    event_t events = {};
    data_t datas = {};

    datas.libs.game = MENU_PATH_LIB;
    datas.libs.graphic = _graphicPaths[_graphicIndex];
    while (1) {
        events = CALL(_graphic)->getEvent();
        if (checkCoreEvents(events) == CORE_EXIT)
            return;
        CALL(_game)->handleEvent(events);
        datas = checkLibUpdate(datas.libs, CALL(_game)->update());
        CALL(_graphic)->display(datas);
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}