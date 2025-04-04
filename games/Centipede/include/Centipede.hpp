/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Centipede.hpp
*/

#ifndef CENTIPEDE_HPP_
    #define CENTIPEDE_HPP_

    #include "events.hpp"
    #include "updates.hpp"
    #include "IGame.hpp"

namespace arcade {
    class Centipede : public IGame {

        public:
            void handleEvent(event_t) override;
            datas_t update(void) override;

        private:
    };
}

#endif