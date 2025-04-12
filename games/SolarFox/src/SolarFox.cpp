/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** test.cpp
*/

#include "SolarFox.hpp"

arcade::SolarFox::SolarFox() {
    initGame();
    setBorder({MAP_SIZE, MAP_SIZE});
    setCoins();
}

void arcade::SolarFox::initGame() {
    _player = {
        .pos = PLAYER_START_POS,
        .size = {PLAYER_SIZE, PLAYER_SIZE},
        .character = '^',
        .asset = "./lib/assets/arcade_solarfox/xwing.png",
        .color = {.r = 255, .g = 0, .b = 255, .a = 255},
        .direction = UP
    };
    _player.pos.y = MAP_OFST.y + MAP_SIZE - MARGIN_ZONE;
    _player.pos.x = MAP_OFST.x + MAP_SIZE / 2;
}

void arcade::SolarFox::movePlayer(void) {
    vector_t oldpos = _player.pos;

    if (_player.direction == UP)
        _player.pos.y -= PLAYER_SPEED;
    else if (_player.direction == DOWN)
        _player.pos.y += PLAYER_SPEED;
    else if (_player.direction == LEFT)
        _player.pos.x -= PLAYER_SPEED;
    else if (_player.direction == RIGHT)
        _player.pos.x += PLAYER_SPEED;

    if (_player.pos.x < MAP_OFST.x + MARGIN_ZONE ||
        _player.pos.y < MAP_OFST.y + MARGIN_ZONE ||
        _player.pos.x > MAP_OFST.x + MAP_SIZE - MARGIN_ZONE + 1 ||
        _player.pos.y > MAP_OFST.y + MAP_SIZE - MARGIN_ZONE + 1) {

        _player.pos = oldpos;
        if (_player.direction == DOWN) {
            _player.direction = UP;
            _player.character = '^';
        } else if (_player.direction == UP) {
            _player.direction = DOWN;
            _player.character = 'v';
        } else if (_player.direction == RIGHT) {
            _player.direction = LEFT;
            _player.character = '<';
        } else if (_player.direction == LEFT) {
            _player.direction = RIGHT;
            _player.character = '>';
        }
    }
}

void arcade::SolarFox::handleEvent(event_t events) {
    for (event_e event : events.events) {
        if (event == A_KEY_Z && _player.direction != DOWN) {
            _player.direction = UP;
            _player.character = '^';
        } else if (event == A_KEY_S && _player.direction != UP) {
            _player.direction = DOWN;
            _player.character = 'v';
        } else if (event == A_KEY_Q && _player.direction != RIGHT) {
            _player.direction = LEFT;
            _player.character = '<';
        } else if (event == A_KEY_D && _player.direction != LEFT) {
            _player.direction = RIGHT;
            _player.character = '>';
        }
    }
    movePlayer();
}

void arcade::SolarFox::setBorder(vector_t size) {
    _border = {};

    entity_t entity = {
        .pos = {0, 0},
        .size = {WALL_SIZE, WALL_SIZE},
        .character = '#',
        .asset = "",
        .color = {150, 150, 150, 255},
        .direction = UP,
    };
    for (std::size_t k = 0; k <= size.x; k++) {
        entity.pos = {static_cast<double>(k) + MAP_OFST.x, 0 + MAP_OFST.y};
        _border.push_back(entity);
        entity.pos = {static_cast<double>(k) + MAP_OFST.x, size.y + MAP_OFST.y};
        _border.push_back(entity);
    }
    for (std::size_t k = 0; k <= size.y; k++) {
        entity.pos = {0 + MAP_OFST.x, static_cast<double>(k) + MAP_OFST.y};
        _border.push_back(entity);
        entity.pos = {size.x + MAP_OFST.x, static_cast<double>(k) + MAP_OFST.y};
        _border.push_back(entity);
    }
}

void arcade::SolarFox::setCoins(void) {
    _coins = {};

    entity_t entity = {
        .pos = {0, 0},
        .size = {COIN_SIZE, COIN_SIZE},
        .character = 'c',
        .asset = "",
        .color = {255, 255, 0, 255},
        .direction = UP,
    };
    int nbCoins = (MAP_SIZE - (MARGIN_ZONE * 2)) / (COIN_SIZE + COIN_OFST);
    vector_t basePos = {
        .x = MAP_OFST.x + MARGIN_ZONE,
        .y = MAP_OFST.y + MARGIN_ZONE
    };
    for (std::size_t k = 0; k <= nbCoins; k++) {
        for (std::size_t i = 0; i <= nbCoins; i++) {
            entity.pos = {
                .x = basePos.x + (k * (COIN_SIZE + COIN_OFST)),
                .y = basePos.y + (i * (COIN_SIZE + COIN_OFST))
            };
            _coins.push_back(entity);
        }
    }
}

data_t arcade::SolarFox::update(void) {
    data_t data = {};

    data.objects.push_back(_player);
    for (auto wall : _border)
        data.bg.push_back(wall);
    for (auto coin : _coins)
        data.bg.push_back(coin);
    return data;
}