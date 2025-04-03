/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** input.hpp
*/

#ifndef EVENT_HPP_
    #define EVENT_HPP_

    #include <vector>
    #include <tool.hpp>

enum event_e {
    KEY_A_PRESSED,
    KEY_A_RELEASED,
    KEY_B_PRESSED,
    KEY_B_RELEASED,
    R_CLICK_PRESSED,
    R_CLICK_RELEASED,
    L_CLICK_PRESSED,
    L_CLICK_RELEASED
};

typedef struct event_s {
    std::vector<event_e> events;
    vector_t mPos;
} event_t;

#endif
