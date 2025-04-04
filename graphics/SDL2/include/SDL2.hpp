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
    
    public:
        SDL2() {};
        event_t getEvent(void) override;
        void display(data_t) override;

    private:
        event_t _event;

};

extern "C" {
    IGraphic *makeGraphic() {
        return new SDL2;
    }
}
}

#endif
