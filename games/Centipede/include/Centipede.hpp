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

    #define GAME_PATH "./lib/arcade_centiped.so"
    #define SET_BASE_GAME(c) (c->_state.libs.game = GAME_PATH)

    #define FRAME_RATE 10
    #define FPS (1000 / FRAME_RATE)
    #define GET_TIME std::chrono::steady_clock::now()
    #define CHRONO(lc) (std::chrono::duration_cast<std::chrono::microseconds>(GET_TIME - lc))
    #define DELTA_TIME 30

    #define WHITE {255, 255, 255, 255}
    #define PINK {248, 148, 200, 255}
    #define GREEN {107, 200, 107, 255}
    #define BLUE {107, 158, 200, 255}
    #define RED {250, 57, 18, 255}
    #define BLACK {0, 0, 0, 0}

    #define ASSET_DIR "./lib/assets/arcade_centipede/"
    #define FONT_PATH "./lib/assets/arcade_menu/font/arcade.ttf"
    #define BULLET_PATH "./lib/assets/arcade_centipede/sprites/Dart.png"
    #define CENTIPEDE_PATH "./lib/assets/arcade_centipede/sprites/CentipedeBody.png"
    #define MUSHROOM_PATH "./lib/assets/arcade_centipede/sprites/Mushroom01.png"
    #define PLAYER_PATH "./lib/assets/arcade_centipede/sprites/Blaster.png"

    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #define MAP_AREA 28
    #define OFFSETY_GAME 35
    #define OFFSETX_GAME 35

    #define MUSHROOM_PTS 10
    #define CENTIPEDE_PTS 100
    #define MUSHROOM_HEATH 5
    #define BULLET_DMG 1

    #define DEFAULT_NB_MUSHROOMS 5
    #define DEFAULT_LEN_CENTIPEDE 10

    #define MUSHROOM_SIZE 1
    #define PLAYER_SIZE 1
    #define CENTIPEDE_SIZE 1
    #define WALL_SIZE 1
    #define BULLET_SIZE 1
    #define FONT_SIZE 10

    #define DEFAULT_PLAYER_POS {10 + OFFSETX_GAME, 20 + OFFSETY_GAME}
    #define DEFAULT_CENTIPEDE_POS(x) {(double)5 + i + OFFSETX_GAME, 5 + OFFSETY_GAME}
    #define DEFAULT_RANDOM_MUSH_POS {(double)(rand() % 20) + OFFSETX_GAME + 1, (double)(rand() % 15) + OFFSETY_GAME + 1}
    #define DEFAULT_TEXT_POS {0, 0}

    #define CENTIPEDE_CHAR 's'
    #define WALL_CHAR '#'
    #define MUSHROOM_CHAR 'm'
    #define BULLET_CHAR '*'
    #define TILE_CHAR ' '
    #define PLAYER_CHAR 'P'

namespace arcade {
class Centipede : public IGame {
  public:
    typedef struct mushroom_s {
      std::size_t health;
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
    bool _isBullet = false;
    std::chrono::_V2::system_clock::time_point _lastTime;

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