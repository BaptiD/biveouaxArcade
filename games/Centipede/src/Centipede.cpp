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
    _state.objects.clear();
    _state.texts.clear();
    _mushroomsPos.clear();
    _score = 0;
    _gameOver = false;
    entity_t centipede;
    mushroom_t mushroom;
    entity_t player;
    srand(time(nullptr));

    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                entity_t wall = {{static_cast<double>(x), static_cast<double>(y)}, {WALL_SIZE, WALL_SIZE}, '#', "", WHITE, RIGHT};
                _state.bg.push_back(wall);
            }
        }
    }
    player = {{10, 20}, {PLAYER_SIZE, PLAYER_SIZE}, 'P', "./lib/assets/arcade_centipede/sprites/Blaster.png", WHITE, RIGHT};
    _state.objects.push_back(player);

    //the centipede
    for (std::size_t i = 0; i < 10; i++) {
        centipede = {{(double)5 + i, 5}, {CENTIPEDE_SIZE, CENTIPEDE_SIZE}, 's', "./lib/assets/arcade_centipede/sprites/CentipedeBody.png", WHITE, RIGHT};
        _state.objects.push_back(centipede);
    }

    //some mushrooms
    for (std::size_t i = 0; i < 5; i++) {
        mushroom.health = 3;
        mushroom.entity = {{(double)(rand() % 20), (double)(rand() % 15)}, {MUSHROOM_SIZE, MUSHROOM_SIZE}, 'm', "./lib/assets/arcade_centipede/sprites/Mushroom01.png", WHITE, RIGHT};
        _mushroomsPos.push_back(mushroom.entity.pos);
        _state.objects.push_back(mushroom.entity);
        _mushrooms.push_back(mushroom);
    }

    //score
    text_t score = {{50, 10}, 10, "Score: 0", FONT_PATH, WHITE};
    _state.texts.push_back(score);
    _score = 0;
}

void arcade::Centipede::handleEvent(event_t events) {
    if (_gameOver) {
        for (auto event : events.events) {
            if (event == A_KEY_ENTER) {
                initGame();
                return;
            }
        }
        _state.texts[0].value = "You lost! Score: " + std::to_string(_score) + " - Press Enter to restart";
        return;
    }
    for (auto event : events.events) {
        if (event == A_KEY_Q)
            _state.objects[0].pos.x = std::max((double)0, _state.objects[0].pos.x - 1);
        if (event == A_KEY_D)
            _state.objects[0].pos.x = std::min((double)28, _state.objects[0].pos.x + 1);
        if (event == A_KEY_Z)
            _state.objects[0].pos.y = std::max((double)0, _state.objects[0].pos.y - 1);
        if (event == A_KEY_S)
            _state.objects[0].pos.y = std::min((double)28, _state.objects[0].pos.y + 1);
        if (event == A_KEY_SPACE)
            shoot();
        if (event == A_KEY_ESC)
            _state.libs.game = MENU_PATH;
    }
    moveCentipede();
    handleCollision();
    updateBullets();
    checkPlayerCollision();
    if (!_gameOver)
        spawnNewCentipede();
    if (_gameOver) {
        _state.texts[0].value = "You lost! Score: " + std::to_string(_score) + " - Press Enter to restart";
        _state.texts[0].pos = {40, 10};
    } else
        _state.texts[0].value = "Score: " + std::to_string(_score);
}

void arcade::Centipede::spawnNewCentipede() {
    bool centipedeExists = false;

    for (auto& entity : _state.objects) {
        if (entity.character == 's') {
            centipedeExists = true;
            break;
        }
    }

    if (!centipedeExists) {
        for (std::size_t i = 0; i < 10; i++) {
            entity_t centipede = {{5.0 + i, 5}, {CENTIPEDE_SIZE, CENTIPEDE_SIZE}, 's', "./lib/assets/arcade_centipede/sprites/CentipedeBody.png", WHITE, RIGHT};
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
        if (entity.character == 's') {
            if (entity.direction == RIGHT) {
                if (isThereMushroom(entity.pos.x + 1, entity.pos.y) || entity.pos.x + 1 > 28) {
                    entity.pos.y += 1;
                    entity.direction = LEFT;
                } else {
                    entity.pos.x += 1;
                }
            } else {
                if (isThereMushroom(entity.pos.x - 1, entity.pos.y) || entity.pos.x - 1 == 0) {
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
    entity_t bullet = {{_state.objects[0].pos.x, _state.objects[0].pos.y - 1}, {MUSHROOM_SIZE, MUSHROOM_SIZE}, '*', "./lib/assets/arcade_centipede/sprites/Dart.png", WHITE, RIGHT};
    _state.objects.push_back(bullet);
}

void arcade::Centipede::updateBullets() {
    for (auto& entity : _state.objects) {
        if (entity.character == '*')
            entity.pos.y -= 1;
    }
    _state.objects.erase(std::remove_if(_state.objects.begin(), _state.objects.end(), [](entity_t& entity) {
        return entity.character == '*' && entity.pos.y < 0;
        }),
        _state.objects.end()
    );
}

bool arcade::Centipede::isCollision(const entity_t& a, const entity_t& b) {
    return (a.pos.x == b.pos.x && a.pos.y == b.pos.y);
}

void arcade::Centipede::handleCollision() {
    std::vector<bool> toRemove(_state.objects.size(), false);
    std::size_t nbMushroom = 0;

    for (std::size_t i = 0; i < _state.objects.size(); i++) {
        if (_state.objects[i].character == '*') {
            for (std::size_t j = 0; j < _state.objects.size(); j++) {
                if (_state.objects[j].character == 'm')
                    nbMushroom += 1;
                if (i == j)
                    continue;
                if ((_state.objects[j].character == 'm' || _state.objects[j].character == 's') &&
                    isCollision(_state.objects[i], _state.objects[j])) {
                    if (_state.objects[j].character == 's') {
                        _score += 100;
                        toRemove[j] = true;
                        mushroom_t newMushroom;
                        newMushroom.health = 3;
                        newMushroom.entity = {_state.objects[i].pos, {MUSHROOM_SIZE, MUSHROOM_SIZE}, 'm', "./lib/assets/arcade_centipede/sprites/Mushroom01.png", WHITE, RIGHT};
                        _state.objects.push_back(newMushroom.entity);
                        _mushroomsPos.push_back(_state.objects[i].pos);
                        _mushrooms.push_back(newMushroom);
                    } else if (_state.objects[j].character == 'm') {
                        _mushrooms[nbMushroom - 1].health -= 1;
                        if (_mushrooms[nbMushroom - 1].health <= 0) {
                            _score += 10;
                            toRemove[j] = true;
                            _mushrooms.erase(_mushrooms.begin() + nbMushroom - 1);
                        }
                    }
                    toRemove[i] = true;
                    break;
                }
            }
        }
    }
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
        if (_state.objects[i].character == 'P') {
            player = _state.objects[i];
            break;
        }
    }
    for (auto& entity : _state.objects) {
        if (entity.character == 's' && isCollision(player, entity)) {
            _gameOver = true;
            break;
        }
    }
    for (auto& centipede : _state.objects) {
        if (centipede.character == 's' && centipede.pos.y >= 28) {
            _gameOver = true;
            break;
        }
    }
}