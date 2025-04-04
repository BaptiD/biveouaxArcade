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

namespace arcade {

    class nCurses : public IGraphic{
        
        public:
            nCurses() {};
            event_t handleEvent(void) override;
            void display(data_t) override;

        private:
            event_t event;

    };
    extern "C" {
        IGraphic *makeGraphic() {
            return new nCurses;
        }
    }
}

#endif
