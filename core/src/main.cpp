/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** main.cpp
*/

#include <iostream>

#include "tool.hpp"
#include "core.hpp"

int main(const int ac, const char * const *av)
{
    if (ac != 2)
        return ERROR;
    try {
        arcade::core core(av[1]);
        core.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    };
    return SUCCESS;
}
