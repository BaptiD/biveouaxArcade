/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** entity.hpp
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include <cstdint>
    #include <string>
    #include "tool.hpp"

enum direction_e {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct entity_s {
    vector_t pos;
    vector_t size;
    char character;
    std::string asset;
    color_t color;
    direction_e direction;
} entity_t;

typedef struct text_s {
    vector_t pos;
    uint8_t fontSize;
    std::string value;
    std::string fontPath;
    color_t color;
} text_t;

#endif
