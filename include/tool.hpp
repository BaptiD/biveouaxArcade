/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** tool.hpp
*/

#ifndef TOOL_HPP_
    #define TOOL_HPP_

    #include <cstdint>
    #include <string>

    #define SUCCESS 0
    #define ERROR 84

typedef struct vector_s {
    double x;
    double y;
} vector_t;

typedef struct color_s {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

typedef struct libPaths_s {
    std::string game;
    std::string graphic;
} libPaths_t;

enum typeLib_e {
    GAME_LIB,
    GRAPHIC_LIB,
};

#endif
