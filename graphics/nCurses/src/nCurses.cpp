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
    {122, A_KEY_Z}
 };

arcade::nCurses::nCurses() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    //halfdelay(1); //100ms getch
}

arcade::nCurses::~nCurses() {
    endwin();
}

event_t arcade::nCurses::getEvent(void) {
    int ch = getch();
    
    //if input
    if (ch != -1) {
        //looking for equivalent input on our arcade's key (check also if we manage it or not)
        for (std::map<int, event_e>::const_iterator it = _map.begin(); it != _map.end(); ++it) {
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
