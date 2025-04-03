/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** main.cpp
*/

#include "tool.hpp"
#include "core.hpp"

int main(const int ac, const char * const *av)
{
    arcade::core core;

    if (ac != 2)
        return ERROR;
    return core.run(std::string(av[1]));
}
