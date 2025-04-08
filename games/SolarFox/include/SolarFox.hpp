/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** SolarFox.hpp
*/

#ifndef SOLARFOX_HPP_
    #define SOLARFOX_HPP_

    #include "events.hpp"
    #include "updates.hpp"
    #include "IGame.hpp"

    #define GAME_MAKER "makeGame" // Name of the extern function to create game class

namespace arcade {

class SolarFox : public IGame {

    public:
        void handleEvent(event_t) override;
        data_t update(void) override;

    private:
};

extern "C" {
    IGame *makeGame() {
        return new SolarFox;
    }
}
}

#endif