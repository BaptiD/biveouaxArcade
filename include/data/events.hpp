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
    A_KEY_ESC,
    A_KEY_SPACE,
    A_KEY_DEL,
    A_KEY_ENTER,
    A_KEY_TAB,
    A_KEY_CTRL,
    A_KEY_SHIFT,
    A_KEY_SHIFTLOCK,
    A_KEY_ALT,
    A_KEY_SQUARE,
    A_KEY_UP,
    A_KEY_DOWN,
    A_KEY_LEFT,
    A_KEY_RIGHT,
    A_KEY_A,
    A_KEY_B,
    A_KEY_C,
    A_KEY_D,
    A_KEY_E,
    A_KEY_F,
    A_KEY_G,
    A_KEY_H,
    A_KEY_I,
    A_KEY_J,
    A_KEY_K,
    A_KEY_L,
    A_KEY_M,
    A_KEY_N,
    A_KEY_O,
    A_KEY_P,
    A_KEY_Q,
    A_KEY_R,
    A_KEY_S,
    A_KEY_T,
    A_KEY_U,
    A_KEY_V,
    A_KEY_W,
    A_KEY_X,
    A_KEY_Y,
    A_KEY_Z,
    A_KEY_0,
    A_KEY_1,
    A_KEY_2,
    A_KEY_3,
    A_KEY_4,
    A_KEY_5,
    A_KEY_6,
    A_KEY_7,
    A_KEY_8,
    A_KEY_9,
    A_MOUSE_LEFT,
    A_MOUSE_RIGHT,
    A_MOUSE_MIDDLE,
    A_MOUSE_XBUTTON1,
    A_MOUSE_XBUTTON2,
    A_MOUSE_VERTICALWHEEL,
    A_MOUSE_HORIZONTALWHEEL
};

typedef struct event_s {
    std::vector<event_e> events;
    vector_t mPos;
} event_t;

#endif
