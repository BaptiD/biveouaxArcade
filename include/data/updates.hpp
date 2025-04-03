/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** updateManagement.hpp
*/

#ifndef UPDATEMANAGEMENT_HPP_
    #define UPDATEMANAGEMENT_HPP_

    #include "vector"
    #include "entitys.hpp"

typedef struct datas_s {
    std::vector<entity_t> bg;
    std::vector<entity_t> items;
    std::vector<entity_t> ui;
    std::vector<text_t> texts;
} datas_t;

#endif
