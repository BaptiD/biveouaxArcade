/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.cpp
*/

#include <iostream>

#include "tool.hpp"
#include "core.hpp"

int arcade::core::loop()
{
    event_t events = {};
    datas_t datas = {};

    while (1) {
        events = CALL(_graphic)->handleEvent();
        CALL(_game)->handleEvent(events);
        datas = CALL(_game)->update();
    //     change lib ? / break loop ?
        CALL(_graphic)->display(datas);
    }
    return SUCCESS;
}

int arcade::core::load(std::string gamePath, std::string graphPath)
{
    try {
        _game.openLib(gamePath);
        _graphic.openLib(graphPath);
    } catch (arcade::dynLibError& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}   

int arcade::core::run(std::string graphLib)
{
    if (load(MENU_PATH_LIB, graphLib))
        return ERROR;
    return loop();
}