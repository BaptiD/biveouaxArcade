/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** SolarFox.hpp
*/

#ifndef SOLARFOX_HPP_
    #define SOLARFOX_HPP_

    #include <chrono>

    #include "events.hpp"
    #include "updates.hpp"
    #include "IGame.hpp"

    #define GAME_MAKER "makeGame" // Name of the extern function to create game class
    #define MENU_PATH "./lib/arcade_menu.so"
    #define GAME_PATH "./lib/arcade_solarfox.so"
    #define ASSETS_PATH "./lib/assets/arcade_solarfox/"

namespace arcade {

class SolarFox : public IGame {

    #define MAP_SIZE 30
    #define MARGIN_ZONE 5
    #define MAP_OFST vector_t{30, 5}

    #define PLAYER_START_POS vector_t{0, 0}
    #define PLAYER_SPEED 0.2
    #define PLAYER_SIZE 3

    #define ENNEMY_SIZE 1
    #define ENNEMY_SPEED 0.3
    #define ENNEMY_HIT_VALUE 100

    #define SHOT_SIZE 1
    #define SHOT_SPEED 0.5
    #define SHOOT_PERCENTAGE 0.2
    #define ENNEMY_SHOT_HIT_VALUE 250

    #define WALL_SIZE 2

    #define COIN_SIZE 3
    #define COIN_OFST 0
    #define COIN_VALUE 10

    #define FPS 60
    #define DELTA_TIME 1000 / FPS

    enum gamestatus_e {
        WAITING,
        RUNNING,
        WIN,
        LOSE,
        PAUSE,
    };

    public:
        SolarFox();
        ~SolarFox() {};
        void handleEvent(event_t) override;
        data_t update(void) override;

    private:
        arcade::SolarFox::gamestatus_e _gameStatus;
        int _score;
        entity_t _player;
        std::vector<entity_t> _ennemies;
        std::vector<int> _ennemiesDirections;
        std::vector<int> _ennemiesStatus;
        std::vector<entity_t> _ennemyShots;
        std::vector<entity_t> _playerShots;
        std::vector<entity_t> _coins;
        std::vector<entity_t> _border;
        std::chrono::_V2::system_clock::time_point _lastTime;
        libPaths_t _libs;
        bool _sendMusic;
        void initGame();
        void movePlayer(void);
        void moveEnnemies(void);
        void ennemyShoot(void);
        void moveShots(void);
        void checkShots(void);
        void setBorder(vector_t size);
        void setCoins(void);
        void setEnnemies(void);
        void isThereCoin(void);
        void playerShoot(void);
        bool checkIfShotOnCoin(std::vector<entity_t>::const_iterator shot);
        bool checkIfShotOnEnnemy(std::vector<entity_t>::const_iterator shot);
        bool checkIfShotOnEnnemyShot(std::vector<entity_t>::const_iterator shot);
        data_t displayBinds(data_t data);
};

extern "C" {
    IGame *makeGame() {
        return new SolarFox;
    }
}
}

#endif
