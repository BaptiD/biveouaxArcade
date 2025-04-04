/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** updateManagement.hpp
*/

#ifndef UPDATEMANAGEMENT_HPP_
    #define UPDATEMANAGEMENT_HPP_

    #include "vector"
    #include "entity.hpp"

typedef struct data_s {
    std::vector<entity_t> bg;
    std::vector<entity_t> objects;
    std::vector<entity_t> ui;
    std::vector<std::string> audios;
    std::vector<text_t> texts;
    libPaths_t libs;
} data_t;

#endif
