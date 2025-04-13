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
    {8, A_KEY_DEL},
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
    {127, A_KEY_DEL},
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
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
}

arcade::nCurses::~nCurses() {
    endwin();
}

event_t arcade::nCurses::getEvent(void) {
    _events.events.clear();
    int ch = getch();

    getyx(stdscr, _events.mPos.y, _events.mPos.x);
    //if input
    if (ch != -1) {
        if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_PRESSED)
                    _events.events.push_back(A_MOUSE_LEFT);
                else if (event.bstate & BUTTON2_PRESSED)
                    _events.events.push_back(A_MOUSE_MIDDLE);
                else if (event.bstate & BUTTON3_PRESSED)
                    _events.events.push_back(A_MOUSE_RIGHT);
            }     
        } else {
            //looking for equivalent input on our arcade's key (check also if we manage it or not)
            for (std::map<int, event_e>::const_iterator it = _map.begin(); it != _map.end(); ++it) {
                if (it->first == ch) {
                    _events.events.push_back(it->second);
                    break;
                }
                flushinp();
            }
        }
    }
    return _events;
}

void arcade::nCurses::getPos(data_t datas) {
    _minPos = {100, 100};
    _maxPos = {0, 0};
    for (auto& bg : datas.bg) {
        if (bg.pos.x < _minPos.x)
            _minPos.x = bg.pos.x;
        if (bg.pos.y < _minPos.y)
            _minPos.y = bg.pos.y;
        if (bg.pos.x > _maxPos.x)
            _maxPos.x = bg.pos.x;
        if (bg.pos.y > _maxPos.y)
            _maxPos.y = bg.pos.y;
    }
    for (auto& obj : datas.objects) {
        if (obj.pos.x < _minPos.x)
            _minPos.x = obj.pos.x;
        if (obj.pos.y < _minPos.y)
            _minPos.y = obj.pos.y;
        if (obj.pos.x > _maxPos.x)
            _maxPos.x = obj.pos.x;
        if (obj.pos.y > _maxPos.y)
            _maxPos.y = obj.pos.y;
    }
    for (auto& ui : datas.ui) {
        if (ui.pos.x < _minPos.x)
            _minPos.x = ui.pos.x;
        if (ui.pos.y < _minPos.y)
            _minPos.y = ui.pos.y;
        if (ui.pos.x > _maxPos.x)
            _maxPos.x = ui.pos.x;
        if (ui.pos.y > _maxPos.y)
            _maxPos.y = ui.pos.y;
    }
}

void arcade::nCurses::display(data_t datas) {
    clear();
    getPos(datas);

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
    for (auto& text : datas.texts) {
        if (text.color.a > 0) {
            int pairIndex = get_color_pair(text.color);
            attron(COLOR_PAIR(pairIndex));
        }
        mvprintw(static_cast<int>(text.pos.y), static_cast<int>(text.pos.x), "%s", text.value.c_str());
        if (text.color.a > 0) {
            attroff(COLOR_PAIR(get_color_pair(text.color)));
        }
    }
}

void arcade::nCurses::drawEntity(entity_t& entity) {
    if (entity.color.a > 0) {
        int pairIndex = get_color_pair(entity.color);
        attron(COLOR_PAIR(pairIndex));
    }
    mvprintw(static_cast<int>(entity.pos.y - _minPos.y), static_cast<int>(entity.pos.x - _minPos.x), "%c", entity.character);
    if (entity.color.a > 0) {
        attroff(COLOR_PAIR(get_color_pair(entity.color)));
    }
}

unsigned int arcade::nCurses::hash_rgba(const color_t &color) {
    unsigned int hash = HASH_START_VALUE;
    hash = hash * HASH_MULT + color.r;
    hash = hash * HASH_MULT + color.g;
    hash = hash * HASH_MULT + color.b;
    hash = hash * HASH_MULT + color.a;
    return hash;
}

int arcade::nCurses::convertColorComponent(int comp) {
    return (comp * MAX_COLOR_NCURSE) / MAX_RGBA;
}

int arcade::nCurses::get_color_pair(const color_t &color) {
    unsigned int key = hash_rgba(color);
    if (_rgbaToPair.find(key) != _rgbaToPair.end()) {
        return _rgbaToPair[key];
    } else {
        if (!can_change_color()) {
            return 0;
        }
        int customColorIndex = _nextCustomColorIndex++;
        int customPairIndex = _nextCustomPairIndex++;
        int ncurses_r = convertColorComponent(color.r);
        int ncurses_g = convertColorComponent(color.g);
        int ncurses_b = convertColorComponent(color.b);
        init_color(customColorIndex, ncurses_r, ncurses_g, ncurses_b);
        init_pair(customPairIndex, customColorIndex, COLOR_BLACK);
        _rgbaToPair[key] = customPairIndex;
        return customPairIndex;
    }
}