/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.cpp
*/

#include <iostream>
#include <thread>
#include <chrono>

#include "tool.hpp"
#include "core.hpp"

arcade::core::core(std::string graphicPath)
{
    load(MENU_PATH_LIB, GAME_LIB);
    load(graphicPath, GRAPHIC_LIB);
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
    if (!data.libs.game.empty() && paths.game != data.libs.game) {
        _game.closeLib();
        load(data.libs.game, GAME_LIB);
        return setupNewGame();
    } else if (!data.libs.graphic.empty() && paths.graphic != data.libs.graphic) {
        _graphic.closeLib();
        load(data.libs.graphic, GRAPHIC_LIB);
    }
    return data;
}

void arcade::core::run(void)
{
    event_t events = {};
    data_t datas = {};

    int fpsLimit = 60;
    std::chrono::milliseconds frame(1000 / fpsLimit);
    while (1) {
        auto frameStart = std::chrono::high_resolution_clock::now();
        events = CALL(_graphic)->getEvent();
        if (!CALL(_game))
            return;
        CALL(_game)->handleEvent(events);
        datas = checkLibUpdate(datas.libs, CALL(_game)->update());
        CALL(_graphic)->display(datas);

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);

        if (elapsed < frame) {
            std::this_thread::sleep_for(frame - elapsed);
        }
    }
}