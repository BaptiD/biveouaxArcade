/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.cpp
*/

#include <iostream>

#include "tool.hpp"
#include "core.hpp"

void arcade::core::load(std::string libPath, typeLib_e type)
{
    try {
        if (type == GAME_LIB)
            _game.openLib(libPath);
        else
            _graphic.openLib(libPath);
    } catch (arcade::dynLibError& e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}   

data_t arcade::core::checkLibUpdate(libPaths_t paths, data_t data)
{
    return data;
}

void arcade::core::run(void)
{
    event_t events = {};
    data_t datas = {};

    while (1) {
        events = CALL(_graphic)->getEvent();
        CALL(_game)->handleEvent(events);
        datas = checkLibUpdate(datas.libs, CALL(_game)->update());
        CALL(_graphic)->display(datas);
    }
}