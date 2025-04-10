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
        void drawEntity(entity_t& entity, float offsetX, float offsetY);
};

extern "C" {
    IGraphic *makeGraphic() {
        return new nCurses;
    }
};

};

#endif
