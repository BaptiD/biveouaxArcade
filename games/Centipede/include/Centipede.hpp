/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Centipede.hpp
*/

#ifndef CENTIPEDE_HPP_
    #define CENTIPEDE_HPP_

    #include <chrono>

    #include "events.hpp"
    #include "updates.hpp"
    #include "IGame.hpp"

    #define MENU_PATH "./lib/arcade_menu.so"

    #define FRAME_RATE 10
    #define FPS (1000 / FRAME_RATE)
    #define GET_TIME std::chrono::steady_clock::now()
    #define CHRONO(lc) (std::chrono::duration_cast<std::chrono::microseconds>(GET_TIME - lc))

    #define WHITE {255, 255, 255, 255}
    #define PINK {248, 148, 200, 255}
    #define GREEN {107, 200, 107, 255}
    #define BLUE {107, 158, 200, 255}
    #define RED {250, 57, 18, 255}
    #define FONT_PATH "./lib/assets/arcade_menu/font/arcade.ttf"
    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #define ASSET_DIR "./lib/assets/arcade_centipede/"
    #define OFFSETY_GAME 20
    #define OFFSETX_GAME 40

    #define MUSHROOM_SIZE 1
    #define PLAYER_SIZE 1
    #define CENTIPEDE_SIZE 1
    #define WALL_SIZE 1
    #define BULLET_SIZE 1

namespace arcade {
class Centipede : public IGame {
  public:
    typedef struct mushroom_s {
      size_t health;
      entity_t entity;
    } mushroom_t;

    Centipede();
    void handleEvent(event_t) override;
    data_t update(void) override;

  private:
    data_t _state;
    int _score;
    std::vector<vector_t> _mushroomsPos;
    std::vector<mushroom_t> _mushrooms;
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