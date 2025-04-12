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
    #include "map.hpp"

    #define GAME_MAKER "makeGame" // Name of the extern function to create game class
    #define MENU_PATH "./lib/arcade_menu.so"
    #define GAME_PATH "./lib/arcade_solarfox.so"

namespace arcade {

class SolarFox : public IGame {

    #define MAP_SIZE 50
    #define MARGIN_ZONE 15
    #define MAP_OFST vector_t{30, 5}

    #define PLAYER_START_POS vector_t{0, 0}
    #define PLAYER_SPEED 0.2
    #define PLAYER_SIZE 3

    #define ENNEMY_SPEED 0.3
    #define SHOT_SPEED 0.5
    #define SHOOT_PERCENTAGE 0.2

    #define WALL_SIZE 2

    #define COIN_SIZE 3
    #define COIN_OFST 0

    enum gamestatus_e {
        RUNNING,
        WIN,
        LOSE
    };

    public:
        SolarFox();
        ~SolarFox() {};
        void handleEvent(event_t) override;
        data_t update(void) override;

    private:
        arcade::SolarFox::gamestatus_e _gameStatus;
        entity_t _player;
        std::vector<entity_t> _ennemies;
        std::vector<int> _ennemiesDirections;
        std::vector<entity_t> _ennemyShots;
        std::vector<entity_t> _playerShots;
        std::vector<entity_t> _coins;
        std::vector<entity_t> _border;
        libPaths_t _libs;
        void initGame();
        void movePlayer(void);
        void moveEnnemies(void);
        void ennemyShoot(void);
        void moveShots(void);
        void checkShots(void);
        void checkIfPlayerOnCoin(void);
        void setBorder(vector_t size);
        void setCoins(void);
        void setEnnemies(void);
};

extern "C" {
    IGame *makeGame() {
        return new SolarFox;
    }
}
}

#endif
