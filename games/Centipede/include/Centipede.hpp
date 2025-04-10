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

    #define WHITE {255, 255, 255, 255}
    #define FONT_PATH "./lib/assets/arcade_menu/font/arcade.ttf"
    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #define ASSET_DIR "./lib/assets/arcade_centipede/"

namespace arcade {
class Centipede : public IGame {
  public:
    Centipede();
    void handleEvent(event_t) override;
    data_t update(void) override;

  private:
    data_t _state;
    int _score;
    std::vector<vector_t> _mushroomsPos;
    vector_t _playerPos;
    bool _gameOver = false;

    void moveCentipede();
    bool isCollision(const entity_t& a, const entity_t& b);
    void handleCollision();
    void shoot();
    void updateBullets();
    bool isThereMushroom(double x, double y);
    void initGame();
    void spawnNewCentipede();
    void checkPlayerCollision();
};

extern "C" {
    IGame *makeGame() {
        return new Centipede;
    }
}

}



#endif