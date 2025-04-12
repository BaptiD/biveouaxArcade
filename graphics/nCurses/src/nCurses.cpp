/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** nCursesDL.cpp
*/

#include "nCurses.hpp"

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

const std::map<int, event_e> arcade::nCurses::_map = {
    {27, A_KEY_ESC},
    {10, A_KEY_ENTER},
    {32, A_KEY_SPACE},
    {127, A_KEY_DEL},
    {48,  A_KEY_0},
    {49,  A_KEY_1},
    {50,  A_KEY_2},
    {51,  A_KEY_3},
    {52,  A_KEY_4},
    {53,  A_KEY_5},
    {54,  A_KEY_6},
    {55,  A_KEY_7},
    {56,  A_KEY_8},
    {57,  A_KEY_9},
    {97, A_KEY_A},
    {98, A_KEY_B},
    {99, A_KEY_C},
    {100, A_KEY_D},
    {101, A_KEY_E},
    {102, A_KEY_F},
    {103, A_KEY_G},
    {104, A_KEY_H},
    {105, A_KEY_I},
    {106, A_KEY_J},
    {107, A_KEY_K},
    {108, A_KEY_L},
    {109, A_KEY_M},
    {110, A_KEY_N},
    {111, A_KEY_O},
    {112, A_KEY_P},
    {113, A_KEY_Q},
    {114, A_KEY_R},
    {115, A_KEY_S},
    {116, A_KEY_T},
    {117, A_KEY_U},
    {118, A_KEY_V},
    {119, A_KEY_W},
    {120, A_KEY_X},
    {121, A_KEY_Y},
    {122, A_KEY_Z},
    {KEY_UP, A_KEY_UP},
    {KEY_DOWN, A_KEY_DOWN},
    {KEY_RIGHT, A_KEY_RIGHT},
    {KEY_LEFT, A_KEY_LEFT},
    {264, A_KEY_F1},
    {265, A_KEY_F2},
    {266, A_KEY_F3},
    {267, A_KEY_F4},
    {268, A_KEY_F5},
    {269, A_KEY_F6},
    {270, A_KEY_F7},
    {271, A_KEY_F8},
    {272, A_KEY_F9},
    {273, A_KEY_F10},
    {274, A_KEY_F11},
    {275, A_KEY_F12},
 };

arcade::nCurses::nCurses() {
    initscr();
    noecho();
    cbreak();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

arcade::nCurses::~nCurses() {
    endwin();
}

event_t arcade::nCurses::getEvent(void) {
    _events.events.clear();
    int ch = getch();
    
    //if input
    if (ch != -1) {
        //looking for equivalent input on our arcade's key (check also if we manage it or not)
        for (std::map<int, event_e>::const_iterator it = _map.begin(); it != _map.end(); ++it) {
            if (it->first == ch) {
                _events.events.push_back(it->second);
                break;
            }
            flushinp();
        }
    }
    return _events;
}

void arcade::nCurses::display(data_t datas) {
    clear();

    float offsetX = (COLS - GAME_WIDTH) / 2;
    float offsetY = (LINES - GAME_HEIGHT) / 2;
    //display bg
    for (auto& bg : datas.bg)
        drawEntity(bg, offsetX, offsetY);

    //display items
    for (auto& item : datas.objects)
        drawEntity(item, offsetX, offsetY);

    //display UI
    for (auto& ui : datas.ui)
        drawEntity(ui, offsetX, offsetY);
    
    //display texts
    for (auto& text : datas.texts) {
        mvprintw(static_cast<int>(((float)text.pos.y / 100) * LINES), static_cast<int>(((float)text.pos.x / 100) * COLS), "%s", text.value.c_str());
    }
}

void arcade::nCurses::drawEntity(entity_t& entity, float offsetX, float offsetY) {
        mvprintw(static_cast<int>(entity.pos.y / 100 * LINES), static_cast<int>(entity.pos.x / 100 * COLS), "%c", entity.character);
}
