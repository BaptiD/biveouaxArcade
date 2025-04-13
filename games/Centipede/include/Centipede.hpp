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
    #define DELTA_TIME_CENTIPEDE 100000000
    #define DELTA_TIME_BULLET 99700000

    #define WHITE {255, 255, 255, 255}
    #define PINK {248, 148, 200, 255}
    #define GREEN {107, 200, 107, 255}
    #define BLUE {107, 158, 200, 255}
    #define RED {250, 57, 18, 255}
    #define BLACK {0, 0, 0, 0}

    #define ASSET_DIR "./lib/assets/arcade_centipede/"
    #define FONT_PATH "./lib/assets/arcade_centipede/fonts/arcade.ttf"
    #define BULLET_PATH "./lib/assets/arcade_centipede/sprites/Dart.png"
    #define CENTIPEDE_PATH "./lib/assets/arcade_centipede/sprites/CentipedeBody.png"
    #define MUSHROOM_PATH "./lib/assets/arcade_centipede/sprites/Mushroom01.png"
    #define PLAYER_PATH "./lib/assets/arcade_centipede/sprites/Blaster.png"

    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #define MAP_AREA 28
    #define MAX_Y_PLAYER (MAP_HEIGHT / 5)
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

    #define DEFAULT_PLAYER_POS {(MAP_AREA / 2) + OFFSETX_GAME, MAP_AREA + OFFSETY_GAME}
    #define DEFAULT_CENTIPEDE_POS(x) {(double)5 + i + OFFSETX_GAME, 5 + OFFSETY_GAME}
    #define DEFAULT_RANDOM_MUSH_POS {(double)(rand() % 20) + OFFSETX_GAME + 1, (double)(rand() % 15) + OFFSETY_GAME + 1}
    #define DEFAULT_SCORE_POS {0, 2}
    #define SCORE_INDEX 1

    #define CENTIPEDE_CHAR 's'
    #define WALL_CHAR '#'
    #define MUSHROOM_CHAR 'm'
    #define BULLET_CHAR '*'
    #define TILE_CHAR ' '
    #define PLAYER_CHAR 'P'
    
    #define KEYS_TEXT "Move: z,q,s,d | Shot: Spacebar | change lib: a,e | restart: r | Return menu: échap | Leave: suppr"
    #define KEYS_TEXT_POS {0, 0}
    #define KEYS_INDEX 0

namespace arcade {
class Centipede : public IGame {
  public:
    typedef enum {
      WIN,
      LOSE,
      INGAME
    } state_t;
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
    state_t _gameStatus;
    std::size_t _nbKilledCentipede;
    bool _isBullet;
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
};
};

#endif