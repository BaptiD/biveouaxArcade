/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.cpp
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "tool.hpp"
#include "core.hpp"

arcade::core::core(std::string graphicPath)
{
    load(MENU_PATH_LIB, GAME_LIB);
    load(graphicPath, GRAPHIC_LIB);
    _graphicpath = graphicPath;
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
    // if (data.libs.game.empty())
    //     return data;
    if (!data.libs.graphic.empty() && paths.graphic.compare(data.libs.graphic)) {
        _graphic.closeLib();
        load(data.libs.graphic, GRAPHIC_LIB);
    }
    if (paths.game.compare(data.libs.game)) {
        _game.closeLib();
        load(data.libs.game, GAME_LIB);
        return setupNewGame();
    }
    return data;
}

void arcade::core::run(void)
{
    event_t events = {};
    data_t datas = {};
    const int targetFPS = 60;
    const std::chrono::milliseconds frameDuration(1000 / targetFPS);

    datas.libs.game = MENU_PATH_LIB;
    datas.libs.graphic = _graphicpath;
    while (1) {
        auto frameStart = std::chrono::steady_clock::now();
        events = CALL(_graphic)->getEvent();
        if (!CALL(_game))
            return;
        CALL(_game)->handleEvent(events);
        datas = checkLibUpdate(datas.libs, CALL(_game)->update());
        // if (datas.libs.game.empty())
        //     return;
        CALL(_graphic)->display(datas);
        
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        if (elapsed < frameDuration)
            std::this_thread::sleep_for(frameDuration - elapsed);
    }
}