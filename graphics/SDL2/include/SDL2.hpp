/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** SDL2.hpp
*/

#ifndef DLSDL2_HPP_
    #define DLSDL2_HPP_

    #include "memory"
    #include "IGraphic.hpp"

namespace arcade {

    class SDL2 : public IGraphic{
        
        private:
            event_t handleEvent(void) override;
            void display(datas_t) override;

        public:
            event_t _events;

    };
    extern "C" {
        IGraphic *makeGraphic() {
            return new SDL2;
        }
    }
}

#endif
