/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.cpp
*/

#include <filesystem>

#include "menu.hpp"
#include "entity.hpp"

void arcade::Menu::getEvent(event_t events)
{

}

void arcade::Menu::getLibs(void)
{
    for (const auto &entity : std::filesystem::directory_iterator(PATH_LIBS)) {
        
    }
}

data_t arcade::Menu::update(void)
{
    data_t datas = {};

    return datas;
}
