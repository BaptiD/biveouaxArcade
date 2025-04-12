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
        void drawEntity(entity_t& entity, float offsetX, float offsetY);
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
