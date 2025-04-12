/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** nCursesDL.hpp
*/

#ifndef DLNCURSES_HPP_
    #define DLNCURSES_HPP_

    #include "memory"
    #include "IGraphic.hpp"
    #include <map>

    #define HASH_START_VALUE 17
    #define HASH_MULT 31
    #define MAX_COLOR_NCURSE 1000
    #define MAX_RGBA 255
    #define GAME_WIDTH 30
    #define GAME_HEIGHT 30
namespace arcade {

class nCurses : public IGraphic {

    public:
        nCurses();
        ~nCurses();
        event_t getEvent(void) override;
        void display(data_t) override;

    private:
        static const std::map<int, event_e> _map;
        event_t _events;
        std::map<unsigned int, int> _rgbaToPair;
        int _nextCustomColorIndex = 16;
        int _nextCustomPairIndex  = 8;
        vector_t _minPos = {100, 100};
        vector_t _maxPos = {0, 0};
        void drawEntity(entity_t& entity);
        void getPos(data_t datas);
        unsigned int hash_rgba(const color_t &color);
        int convertColorComponent(int comp);
        int get_color_pair(const color_t &color);
};

extern "C" {
    IGraphic *makeGraphic() {
        return new nCurses;
    }
};

};

#endif
