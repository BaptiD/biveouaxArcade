/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.cpp
*/

#include <filesystem>

#include "menu.hpp"
#include "entitys.hpp"

void arcade::Menu::handleEvent(event_t events)
{

}

void arcade::Menu::getLibs(void)
{
    for (const auto &entity : std::filesystem::directory_iterator(PATH_LIBS)) {
        
    }
}

datas_t arcade::Menu::update(void)
{
    datas_t datas = {};

    return datas;
}
