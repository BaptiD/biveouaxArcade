/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** IGame.hpp
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include "events.hpp"
    #include "updates.hpp"

    #define GAME_MAKER "makeGame" // Name of the extern function to create game class

namespace arcade {

    class IGame {

        public:
            virtual ~IGame() = default;
            virtual void getEvent(event_t) = 0;
            virtual data_t update(void) = 0;

        private:

    };
}

#endif
