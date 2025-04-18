/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** test.cpp
*/

#include <cstdlib>
#include "SolarFox.hpp"

arcade::SolarFox::SolarFox() {
    setBorder({MAP_SIZE, MAP_SIZE});
    initGame();
    _sendMusic = true;
}

void arcade::SolarFox::initGame() {
    _gameStatus = WAITING;
    _score = 0;
    _ennemies.clear();
    _ennemiesDirections.clear();
    _ennemiesStatus = {-1, -1};
    _ennemyShots.clear();
    _playerShots.clear();
    _coins.clear();
    _libs.game = GAME_PATH;
    _player = {
        .pos = PLAYER_START_POS,
        .size = {PLAYER_SIZE, PLAYER_SIZE},
        .character = '^',
        .asset = ASSETS_PATH + static_cast<std::string>("xwing.png"),
        .color = {.r = 255, .g = 0, .b = 255, .a = 255},
        .direction = UP
    };
    _player.pos.y = MAP_OFST.y + MAP_SIZE - MARGIN_ZONE;
    _player.pos.x = MAP_OFST.x + MAP_SIZE / 2;
    setCoins();
    setEnnemies();
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

bool arcade::SolarFox::checkIfShotOnCoin(std::vector<entity_t>::const_iterator shot) {
    std::vector<entity_t>::const_iterator to_delete;
    bool found = false;
    vector_t laser_center_pos = {shot->pos.x + (SHOT_SIZE / 2), shot->pos.y + (SHOT_SIZE / 2)};

    for (std::vector<entity_t>::const_iterator coin = _coins.begin(); coin != _coins.end(); coin++) {
        if (laser_center_pos.x - coin->pos.x >= 0 && laser_center_pos.x - coin->pos.x <= COIN_SIZE &&
            laser_center_pos.y - coin->pos.y >= 0 && laser_center_pos.y - coin->pos.y <= COIN_SIZE) {
            to_delete = coin;
            found = true;
            _score += COIN_VALUE;
        }
    }
    if (found) {
        _coins.erase(to_delete);
        return true;
    }
    return false;
}

bool arcade::SolarFox::checkIfShotOnEnnemy(std::vector<entity_t>::const_iterator shot) {
    vector_t laser_center_pos = {shot->pos.x + (SHOT_SIZE / 2), shot->pos.y + (SHOT_SIZE / 2)};
    std::size_t index = 0;

    for (std::vector<entity_t>::const_iterator ennemy = _ennemies.begin(); ennemy != _ennemies.end(); ennemy++) {
        if (laser_center_pos.x - ennemy->pos.x >= 0 && laser_center_pos.x - ennemy->pos.x <= ENNEMY_SIZE &&
            laser_center_pos.y - ennemy->pos.y >= 0 && laser_center_pos.y - ennemy->pos.y <= ENNEMY_SIZE) {
            _score += ENNEMY_HIT_VALUE;
            _ennemiesStatus[index] = 0;
            return true;
        }
        index++;
    }
    return false;
}

bool arcade::SolarFox::checkIfShotOnEnnemyShot(std::vector<entity_t>::const_iterator shot) {
    vector_t laser_center_pos = {shot->pos.x + (SHOT_SIZE / 2), shot->pos.y + (SHOT_SIZE / 2)};

    for (std::vector<entity_t>::const_iterator ennemyShot = _ennemyShots.begin(); ennemyShot != _ennemyShots.end(); ennemyShot++) {
        if (laser_center_pos.x - ennemyShot->pos.x >= 0 && laser_center_pos.x - ennemyShot->pos.x <= SHOT_SIZE &&
            laser_center_pos.y - ennemyShot->pos.y >= 0 && laser_center_pos.y - ennemyShot->pos.y <= SHOT_SIZE) {
            _score += ENNEMY_SHOT_HIT_VALUE;
            _ennemyShots.erase(ennemyShot);
            return true;
        }
    }
    return false;
}

void arcade::SolarFox::checkShots(void) {
    std::vector<std::vector<entity_t>::const_iterator> to_delete;
    bool found = false;

    for (std::vector<entity_t>::const_iterator shot = _ennemyShots.begin(); shot != _ennemyShots.end(); shot++) {
        if (shot->pos.y < MAP_OFST.y + WALL_SIZE ||
            shot->pos.y > MAP_OFST.y + MAP_SIZE) {
                to_delete.push_back(shot);
        } else if ((shot->pos.x - _player.pos.x >= 0 && shot->pos.x - _player.pos.x <= PLAYER_SIZE) &&
                (shot->pos.y - _player.pos.y >= 0 && shot->pos.y - _player.pos.y <= PLAYER_SIZE)) {
                    to_delete.push_back(shot);
                    _gameStatus = LOSE;
        }
    }
    for (std::size_t k = 0; k < to_delete.size(); k++) {
        _ennemyShots.erase(to_delete[k]);
    }
    to_delete.clear();
    for (std::vector<entity_t>::const_iterator shot = _playerShots.begin(); shot != _playerShots.end(); shot++) {
        if (shot->pos.y < MAP_OFST.y + WALL_SIZE ||
            shot->pos.y > MAP_OFST.y + MAP_SIZE ||
            shot->pos.x < MAP_OFST.x + WALL_SIZE ||
            shot->pos.x > MAP_OFST.x + MAP_SIZE) {
                to_delete.push_back(shot);
        } else if (checkIfShotOnEnnemyShot(shot) == true) {
            to_delete.push_back(shot);            
        } else if (checkIfShotOnCoin(shot) == true) {
            to_delete.push_back(shot);            
        } else if (checkIfShotOnEnnemy(shot) == true) {
            to_delete.push_back(shot);
        }
    }
    for (std::size_t k = 0; k < to_delete.size(); k++) {
        _playerShots.erase(to_delete[k]);
    }

}

void arcade::SolarFox::moveShots(void) {
    for (std::size_t k = 0; k < _ennemyShots.size(); k++) {
        if (_ennemyShots[k].direction == UP) {
            _ennemyShots[k].pos.y -= SHOT_SPEED;
        } else {
            _ennemyShots[k].pos.y += SHOT_SPEED;
        }
    }
    for (std::size_t k = 0; k < _playerShots.size(); k++) {
        if (_playerShots[k].direction == UP) {
            _playerShots[k].pos.y -= SHOT_SPEED;
        } else if (_playerShots[k].direction == DOWN) {
            _playerShots[k].pos.y += SHOT_SPEED;
        } else if (_playerShots[k].direction == LEFT) {
            _playerShots[k].pos.x -= SHOT_SPEED;
        } else if (_playerShots[k].direction == RIGHT) {
            _playerShots[k].pos.x += SHOT_SPEED;
        }
    }
}

void arcade::SolarFox::ennemyShoot(void) {
    for (std::size_t index = 0; index < _ennemies.size(); index++) {
        if (_ennemiesStatus[index] == -1) {
            int chance = rand() % 100;
            if (chance <= SHOOT_PERCENTAGE) {
                entity_t newShot = {
                    .pos = _ennemies[index].pos,
                    .size = {SHOT_SIZE, SHOT_SIZE},
                    .character = '*',
                    .asset = ASSETS_PATH + static_cast<std::string>("green_laser.png"),
                    .color = {.r = 0, .g = 255, .b = 0, .a = 255},
                    .direction = DOWN
                };
                if (_ennemies[index].pos.y > MAP_OFST.y + MAP_SIZE / 2)
                    newShot.direction = UP;
                _ennemyShots.push_back(newShot);
            }
        }
    }
}

void arcade::SolarFox::moveEnnemies(void) {
    for (std::size_t index = 0; index < _ennemies.size(); index++) {
        if (_ennemiesStatus[index] == -1) {
            _ennemies[index].pos.x += ENNEMY_SPEED * _ennemiesDirections[index];
            if (_ennemies[index].pos.x < MAP_OFST.x + WALL_SIZE ||
                _ennemies[index].pos.x > MAP_OFST.x + MAP_SIZE - WALL_SIZE) {
                _ennemiesDirections[index] *= -1;
            }
        } else {
            _ennemiesStatus[index] += 1;
            if (_ennemiesStatus[index] > (FPS)) {
                _ennemiesStatus[index] = -1;
            }
        }
    }
}

void arcade::SolarFox::isThereCoin(void) {
    if (_coins.size() == 0)
        _gameStatus = WIN;
}

void arcade::SolarFox::playerShoot(void) {
    entity_t newShot = {
        .pos = {_player.pos.x + PLAYER_SIZE / 2, _player.pos.y + PLAYER_SIZE / 2},
        .size = {SHOT_SIZE, SHOT_SIZE},
        .character = '*',
        .asset = ASSETS_PATH + static_cast<std::string>("red_laser.png"),
        .color = {.r = 255, .g = 0, .b = 0, .a = 255},
        .direction = _player.direction
    };
    _playerShots.push_back(newShot);
}

void arcade::SolarFox::handleEvent(event_t events) {
    if (_gameStatus != RUNNING) {
        for (event_e event : events.events) {
            if (event == A_KEY_ENTER) {
                initGame();
            } else if (event == A_KEY_ESC) {
                _libs.game = MENU_PATH;
            } else if (event == A_KEY_F4) {
                _libs.game.clear();
            } else if (event == A_KEY_SPACE && (_gameStatus == PAUSE || _gameStatus == WAITING)) {
                _gameStatus = RUNNING;
            }
        }
        return;
    }
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
        } else if (event == A_KEY_ENTER) {
            playerShoot();
        } else if (event == A_KEY_ESC) {
            _libs.game = MENU_PATH;
        } else if (event == A_KEY_F4) {
            _libs.game.clear();
        } else if (event == A_KEY_SPACE) {
            _gameStatus = PAUSE;
        }
    }
    std::chrono::_V2::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    if (now - _lastTime < (std::chrono::milliseconds)DELTA_TIME) {
        return;
    }
    _lastTime = now;
    movePlayer();
    moveEnnemies();
    ennemyShoot();
    moveShots();
    checkShots();
    isThereCoin();
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
        .asset = ASSETS_PATH + static_cast<std::string>("stormtrooper.png"),
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

void arcade::SolarFox::setEnnemies(void) {
    entity_t ennemy = {
        .pos = {0, 0},
        .size = {PLAYER_SIZE, PLAYER_SIZE},
        .character = '$',
        .asset = ASSETS_PATH + static_cast<std::string>("tie_fighter.png"),
        .color = {.r = 150, .g = 0, .b = 0, .a = 255},
        .direction = UP
    };
    ennemy.pos.x = MAP_OFST.x + WALL_SIZE;
    ennemy.pos.y = MAP_OFST.y + MAP_SIZE - (WALL_SIZE + 1);
    _ennemies.push_back(ennemy);
    _ennemiesDirections.push_back(1);
    ennemy.direction = DOWN;
    ennemy.pos.x = MAP_OFST.x + MAP_SIZE - WALL_SIZE;
    ennemy.pos.y = MAP_OFST.y + WALL_SIZE;
    _ennemies.push_back(ennemy);
    _ennemiesDirections.push_back(-1);
}

data_t arcade::SolarFox::displayBinds(data_t data) {
    text_t text = {
        .pos = {MAP_SIZE + MAP_OFST.x + WALL_SIZE * 2 + 2, 0},
        .fontSize = 14,
        .value = "keybinds: " + std::to_string(_score),
        .fontPath = ASSETS_PATH + static_cast<std::string>("Starjedi.ttf"),
        .color = {255, 255, 0, 255}
    };
    text.pos.y = 20;
    text.value = "move:  z q s d";
    data.texts.push_back(text);

    text.pos.y  = 22;
    text.value = "shoot:  enter";
    data.texts.push_back(text);

    text.pos.y  = 24;
    text.value = "pause: space";
    data.texts.push_back(text);

    text.pos.y = 26;
    text.value = "menu:  esc";
    data.texts.push_back(text);

    text.pos.y = 28;
    text.value = "change graphic:  a";
    data.texts.push_back(text);

    text.pos.y = 30;
    text.value = "change game:  e";
    data.texts.push_back(text);

    text.pos.y = 32;
    text.value = "restart: r";
    data.texts.push_back(text);

    return data;
}

data_t arcade::SolarFox::update(void) {
    data_t data = {};

    if (_gameStatus == RUNNING || _gameStatus == PAUSE || _gameStatus == WAITING) {
        for (auto wall : _border)
            data.bg.push_back(wall);
        for (auto coin : _coins)
            data.objects.push_back(coin);
        for (auto ennemy : _ennemies)
            data.objects.push_back(ennemy);
        for (auto ennemyShot : _ennemyShots)
            data.objects.push_back(ennemyShot);
        for (auto playerShot : _playerShots)
            data.objects.push_back(playerShot);
        data.objects.push_back(_player);
        text_t text = {
            .pos = {MAP_OFST.x, 2},
            .fontSize = 20,
            .value = "score : " + std::to_string(_score),
            .fontPath = ASSETS_PATH + static_cast<std::string>("Starjedi.ttf"),
            .color = {255, 255, 0, 255}
        };
        data.texts.push_back(text);
        data = displayBinds(data);
        if (_gameStatus == PAUSE) {
            text.pos = {60, 2};
            text.value = "paused";
            data.texts.push_back(text);
        } else if (_gameStatus == WAITING) {
            text.pos = {60, 2};
            text.value = "press space to start";
            data.texts.push_back(text);
        }
    } else {
        text_t text = {
            .pos = {35, 40},
            .fontSize = 20,
            .value = "press enter to restart",
            .fontPath = ASSETS_PATH + static_cast<std::string>("Starjedi.ttf"),
            .color = {255, 255, 0, 255}
        };
        data.texts.push_back(text);
        text.pos = {40, 30};
        text.fontSize = 30;
        if (_gameStatus == WIN) {
            text.value = "victory !";
        } else {
            text.value = "defeat !";
        }
        data.texts.push_back(text);
    }
    if (_sendMusic) {
        data.audios = {ASSETS_PATH + static_cast<std::string>("resistance.wav")};
        _sendMusic = false;
    }
    data.libs = _libs;
    return data;
}