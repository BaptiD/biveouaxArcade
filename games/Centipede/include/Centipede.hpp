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
    data_t update(void) override;

  private:
    data_t _state;
    int _score;

    void moveCentipede();
    void handleCollision();
    void shoot();
    void updateBullets();
};

extern "C" {
    IGame *makeGame() {
        return new Centipede;
    }
}

}



#endif