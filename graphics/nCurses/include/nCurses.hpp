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
namespace arcade {

class nCurses : public IGraphic {

    public:
        nCurses();
        ~nCurses();
        event_t getEvent(void) override;
        void display(data_t) override;

    private:
        static const std::map<char, event_e> _map;
        event_t _events;
        void drawEntity(entity_t& entity);
};

extern "C" {
    IGraphic *makeGraphic() {
        return new nCurses;
    }
};

};

#endif
