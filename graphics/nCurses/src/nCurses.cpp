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

const std::map<char, event_e> arcade::nCurses::_map = {
    {'a', A_KEY_A},
    {'b', A_KEY_B},
    {'c', A_KEY_C},
    {'d', A_KEY_D},
    {'e', A_KEY_E},
    {'f', A_KEY_F},
    {'g', A_KEY_G},
    {'h', A_KEY_H},
    {'i', A_KEY_I},
    {'j', A_KEY_J},
    {'k', A_KEY_K},
    {'l', A_KEY_L},
    {'m', A_KEY_M},
    {'n', A_KEY_N},
    {'o', A_KEY_O},
    {'p', A_KEY_P},
    {'q', A_KEY_Q},
    {'r', A_KEY_R},
    {'s', A_KEY_S},
    {'t', A_KEY_T},
    {'u', A_KEY_U},
    {'v', A_KEY_V},
    {'w', A_KEY_W},
    {'x', A_KEY_X},
    {'y', A_KEY_Y},
    {'z', A_KEY_Z}
 };

arcade::nCurses::nCurses() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

arcade::nCurses::~nCurses() {
    endwin();
}

event_t arcade::nCurses::getEvent(void) {
    int ch;
    
    //while input
    while ((ch = getch()) != ERR) {
        //looking for equivalent input on our arcade's key (check also if we manage it or not)
        for (std::map<char, event_e>::const_iterator it = _map.begin(); it != _map.end(); ++it) {
            if (it->first == ch) {
                _events.events.push_back(it->second);
                break;
            }
        }
    }
    return _events;
}

void arcade::nCurses::display(data_t datas) {
    clear();
    
    //display bg
    for (auto& bg : datas.bg)
        drawEntity(bg);

    //display items
    for (auto& item : datas.objects)
        drawEntity(item);

    //display UI
    for (auto& ui : datas.ui)
        drawEntity(ui);
    
    //display texts
    for (auto& text : datas.texts)
        mvprintw(static_cast<int>(text.pos.y), static_cast<int>(text.pos.x), "%s", text.value.c_str());
}

void arcade::nCurses::drawEntity(entity_t& entity) {
    mvprintw(static_cast<int>(entity.pos.y), static_cast<int>(entity.pos.x), "%c", '#');
}
