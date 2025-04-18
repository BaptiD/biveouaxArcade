/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Centipede.cpp
*/

#include <cstdlib>
#include <time.h>
#include <algorithm>

#include "Centipede.hpp"

arcade::Centipede::Centipede() {
    initGame();
}

void arcade::Centipede::initGame() {
    //set all set to default ones
    _state.objects.clear();
    _state.texts.clear();
    _mushroomsPos.clear();
    _score = 0;
    _gameStatus = INGAME;
    _isBullet = false;
    _nbKilledCentipede = 0;
    entity_t centipede;
    mushroom_t mushroom;
    entity_t player;
    srand(time(nullptr));

    //background and walls
    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                entity_t wall = {{static_cast<double>(x) + OFFSETX_GAME, static_cast<double>(y) + OFFSETY_GAME}, {WALL_SIZE, WALL_SIZE}, WALL_CHAR, "", WHITE, UP};
                _state.bg.push_back(wall);
            } else {
                entity_t tile = {{static_cast<double>(x) + OFFSETX_GAME, static_cast<double>(y) + OFFSETY_GAME}, {WALL_SIZE, WALL_SIZE}, TILE_CHAR, "", BLACK, UP};
                _state.bg.push_back(tile);
            }
        }
    }
    //the player
    player = {DEFAULT_PLAYER_POS, {PLAYER_SIZE, PLAYER_SIZE}, PLAYER_CHAR, PLAYER_PATH, BLUE, UP};
    _state.objects.push_back(player);

    //the centipede
    for (std::size_t i = 0; i < DEFAULT_LEN_CENTIPEDE; i++) {
        centipede = {DEFAULT_CENTIPEDE_POS(i), {CENTIPEDE_SIZE, CENTIPEDE_SIZE}, CENTIPEDE_CHAR, CENTIPEDE_PATH, PINK, UP};
        _state.objects.push_back(centipede);
    }

    //some mushrooms
    for (std::size_t i = 0; i < DEFAULT_NB_MUSHROOMS; i++) {
        mushroom.health = MUSHROOM_HEATH;
        mushroom.entity = {DEFAULT_RANDOM_MUSH_POS, {MUSHROOM_SIZE, MUSHROOM_SIZE}, MUSHROOM_CHAR, MUSHROOM_PATH, GREEN, UP};
        _mushroomsPos.push_back(mushroom.entity.pos);
        _state.objects.push_back(mushroom.entity);
        _mushrooms.push_back(mushroom);
    }

    //keys text
    text_t keys = {KEYS_TEXT_POS, FONT_SIZE, KEYS_TEXT, FONT_PATH, WHITE};
    _state.texts.push_back(keys);

    //score text
    text_t score = {DEFAULT_SCORE_POS, FONT_SIZE, "Score: 0, number of centipede killed: " + std::to_string(_nbKilledCentipede) + "/20", FONT_PATH, WHITE};
    _state.texts.push_back(score);
    _lastTime = std::chrono::high_resolution_clock::now();
}

void arcade::Centipede::handleEvent(event_t events) {
    if (_gameStatus == LOSE) {
        for (event_e event : events.events) {
            if (event == A_KEY_ENTER) {
                initGame();
                return;
            }
        }
        _state.texts[SCORE_INDEX].value = "You lost! Score: " + std::to_string(_score) + + ", number of centipede killed: " + std::to_string(_nbKilledCentipede) + "/20" + " - Press Enter to restart";
        _state.texts[SCORE_INDEX].pos = DEFAULT_SCORE_POS;
        return;
    }
    if (_gameStatus == WIN) {
        for (event_e event : events.events) {
            if (event == A_KEY_ENTER) {
                initGame();
                return;
            }
        }
        _state.texts[SCORE_INDEX].value = "You won ! Score: " + std::to_string(_score) + " - Press Enter to restart";
        _state.texts[SCORE_INDEX].pos = DEFAULT_SCORE_POS;
        return;
    }
    for (event_e event : events.events) {
        if (event == A_KEY_Q)
            _state.objects[PLAYER_INDEX].pos.x = std::max((double)1 + OFFSETX_GAME, _state.objects[PLAYER_INDEX].pos.x - 1);
        if (event == A_KEY_D)
            _state.objects[PLAYER_INDEX].pos.x = std::min((double)MAP_AREA + OFFSETX_GAME, _state.objects[PLAYER_INDEX].pos.x + 1);
        if (event == A_KEY_Z)
            _state.objects[PLAYER_INDEX].pos.y = std::max((double)MAP_AREA - MAX_Y_PLAYER + OFFSETY_GAME, _state.objects[PLAYER_INDEX].pos.y - 1);
        if (event == A_KEY_S)
            _state.objects[PLAYER_INDEX].pos.y = std::min((double)MAP_AREA + OFFSETY_GAME, _state.objects[PLAYER_INDEX].pos.y + 1);
        if (event == A_KEY_SPACE)
            shoot();
        if (event == A_KEY_ESC)
            _state.libs.game = MENU_PATH;
    }
    events.events.clear();
    handleCollision();
    checkPlayerCollision();
    std::chrono::_V2::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    if (now - _lastTime > (std::chrono::nanoseconds)DELTA_TIME_BULLET) {
        updateBullets();
        spawnNewCentipede();
        if (_nbKilledCentipede == NB_CENTIPEDE_TO_KILL)
            _gameStatus = WIN;
        _state.texts[SCORE_INDEX].value = "Score: " + std::to_string(_score) + ", number of centipede killed: " + std::to_string(_nbKilledCentipede) + "/20";
        if (now - _lastTime > (std::chrono::nanoseconds)DELTA_TIME_CENTIPEDE) {
            _lastTime = now;
            moveCentipede();
            return;
        }
    }
}

void arcade::Centipede::spawnNewCentipede() {
    bool centipedeExists = false;

    for (auto& entity : _state.objects) {
        if (entity.character == CENTIPEDE_CHAR) {
            centipedeExists = true;
            break;
        }
    }

    if (!centipedeExists) {
        _nbKilledCentipede++;
        for (std::size_t i = 0; i < DEFAULT_LEN_CENTIPEDE; i++) {
            entity_t centipede = {DEFAULT_CENTIPEDE_POS(i), {CENTIPEDE_SIZE, CENTIPEDE_SIZE}, CENTIPEDE_CHAR, CENTIPEDE_PATH, PINK, UP};
            _state.objects.push_back(centipede);
        }
    }
}

data_t arcade::Centipede::update(void) {
    return _state;
}

bool arcade::Centipede::isThereMushroom(double x, double y) {
    for (auto& pos : _mushroomsPos) {
        if (x == pos.x && y == pos.y)
            return true;
    }
    return false;
}

void arcade::Centipede::moveCentipede() {
    for (auto& entity : _state.objects) {
        if (entity.character == CENTIPEDE_CHAR) {
            if (entity.direction == RIGHT) {
                if (isThereMushroom(entity.pos.x + 1, entity.pos.y) || entity.pos.x + 1 > MAP_AREA + OFFSETX_GAME) {
                    entity.pos.y += 1;
                    entity.direction = LEFT;
                } else {
                    entity.pos.x += 1;
                }
            } else {
                if (isThereMushroom(entity.pos.x - 1, entity.pos.y) || entity.pos.x - 1 == OFFSETX_GAME) {
                    entity.pos.y += 1;
                    entity.direction = RIGHT;
                } else {
                    entity.pos.x -= 1;
                }
            }
        }
    }
}

void arcade::Centipede::shoot() {
    if (_isBullet == true)
        return;
    entity_t bullet = {{_state.objects[PLAYER_INDEX].pos.x, _state.objects[PLAYER_INDEX].pos.y - 1}, {MUSHROOM_SIZE, MUSHROOM_SIZE}, BULLET_CHAR, BULLET_PATH, RED, UP};
    _state.objects.push_back(bullet);
    _isBullet = true;
}

void arcade::Centipede::updateBullets() {
    std::vector<entity_t>::const_iterator i;
    for (entity_t& entity : _state.objects) {
        if (entity.character == BULLET_CHAR) {
            entity.pos.y -= 1;
            if (entity.pos.y <= 0 + OFFSETY_GAME)
                _isBullet = false;
        }
    }
    _state.objects.erase(std::remove_if(_state.objects.begin(), _state.objects.end(), [](entity_t& entity) {
        return entity.character == BULLET_CHAR && entity.pos.y < 0 + OFFSETY_GAME;
        }),
        _state.objects.end()
    );
}

bool arcade::Centipede::isCollision(const entity_t& a, const entity_t& b) {
    return (a.pos.x == b.pos.x && a.pos.y == b.pos.y);
}

void arcade::Centipede::handleCollision(){
    std::vector<bool> toRemove(_state.objects.size(), false);
    std::size_t nbMushroom = 0;

    for (std::size_t i = 0; i < _state.objects.size(); i++) {
        if (_state.objects[i].character == BULLET_CHAR) {
            for (std::size_t j = 0; j < _state.objects.size(); j++) {
                if (i == j)
                    continue;

                //if a bullet hit a centipede or a mushroom
                if ((_state.objects[j].character == MUSHROOM_CHAR || _state.objects[j].character == CENTIPEDE_CHAR) &&
                    isCollision(_state.objects[i], _state.objects[j])) {
                    if (_state.objects[j].character == CENTIPEDE_CHAR) {
                        _score += CENTIPEDE_PTS;
                        toRemove[j] = true;
                        mushroom_t newMushroom;
                        newMushroom.health = MUSHROOM_HEATH;
                        newMushroom.entity = {_state.objects[i].pos, {MUSHROOM_SIZE, MUSHROOM_SIZE}, MUSHROOM_CHAR, MUSHROOM_PATH, GREEN, UP};
                        _state.objects.push_back(newMushroom.entity);
                        _mushroomsPos.push_back(_state.objects[i].pos);
                        _mushrooms.push_back(newMushroom);
                    } else if (_state.objects[j].character == MUSHROOM_CHAR) {
                        _mushrooms[nbMushroom].health -= BULLET_DMG;
                        if (_mushrooms[nbMushroom].health <= 0) {
                            _score += MUSHROOM_PTS;
                            toRemove[j] = true;
                            _mushrooms.erase(_mushrooms.begin() + nbMushroom);
                        }
                    }
                    _isBullet = false;
                    toRemove[i] = true;
                    break;
                }
                if (_state.objects[j].character == MUSHROOM_CHAR)
                nbMushroom += 1;
            }
        }
    }

    //remove object hit by bullet and the bullet
    std::vector<entity_t> newObjects;
    for (std::size_t i = 0; i < _state.objects.size(); i++) {
        if (!toRemove[i]) {
            newObjects.push_back(_state.objects[i]);
        }
    }
    _state.objects = std::move(newObjects);
}

void arcade::Centipede::checkPlayerCollision() {
    entity_t player;
    for (std::size_t i = 0; i < _state.objects.size(); i++) {
        if (_state.objects[i].character == PLAYER_CHAR) {
            player = _state.objects[i];
            break;
        }
    }
    for (entity_t& entity : _state.objects) {
        if (entity.character == CENTIPEDE_CHAR && isCollision(player, entity)) {
            _gameStatus = LOSE;
            break;
        }
    }
    for (entity_t& centipede : _state.objects) {
        if (centipede.character == CENTIPEDE_CHAR && centipede.pos.y >= MAP_AREA + OFFSETY_GAME) {
            _gameStatus = LOSE;
            break;
        }
    }
}
