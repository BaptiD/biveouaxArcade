/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Centipede.cpp
*/

#include "Centipede.hpp"

#include <cstdlib>
#include <time.h>
#include <algorithm>

arcade::Centipede::Centipede() {
    entity_t centipede;
    entity_t mushroom;
    entity_t player;

    srand(time(nullptr));
    player.pos = {10, 20};
    player.character = 'P';
    _state.objects.push_back(player);

    //the centipede
    for (size_t i = 0; i < 10; i++) {
        centipede.pos = {(double)5 + i, 5};
        centipede.character = 's';
        _state.objects.push_back(centipede);
    }

    //some mushrooms
    for (size_t i = 0; i < 5; i++) {
        mushroom.pos = {(double)(rand() % 30), (double)(rand() % 15)};
        mushroom.character = 'm';
        _state.objects.push_back(mushroom);
    }

    //score
    text_t score;
    score.pos = {0, 0};
    score.value = "Score: 0";
    _state.texts.push_back(score);
}

void arcade::Centipede::handleEvent(event_t events) {
    for (auto event : events.events) {
        if (event == A_KEY_Q)
            _state.objects[0].pos.x = std::max((double)0, _state.objects[0].pos.x - 1);
        if (event == A_KEY_D)
            _state.objects[0].pos.x = std::min((double)30, _state.objects[0].pos.x + 1);
        if (event == A_KEY_Z)
            _state.objects[0].pos.y = std::max((double)0, _state.objects[0].pos.y - 1);
        if (event == A_KEY_S)
            _state.objects[0].pos.y = std::min((double)30, _state.objects[0].pos.y + 1);
        if (event == A_KEY_SPACE)
            shoot();
    }
    moveCentipede();
    handleCollision();
    updateBullets();
    _state.texts[0].value = "Score: " + std::to_string(_score);
}

data_t arcade::Centipede::update(void) {
    return _state;
}

void arcade::Centipede::moveCentipede() {
    for (auto& entity : _state.objects) {
        if (entity.character == 's') {
            entity.pos.x += 1;
            if (entity.pos.x > 30) {
                entity.pos.x = 0;
                entity.pos.y += 1;
            }
        }
    }
}

void arcade::Centipede::shoot() {
    entity_t bullet;

    bullet.pos = {_state.objects[0].pos.x, _state.objects[0].pos.y - 1};
    bullet.character = '*';
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
    for (size_t i = 0; i < _state.objects.size(); i++) {
        if (_state.objects[i].character == '*') {
            for (size_t j = 0; j < _state.objects.size(); j++) {
                if (i == j)
                    continue;
                if ((_state.objects[j].character == 'm' || _state.objects[j].character == 's') &&
                isCollision(_state.objects[i], _state.objects[j])) {
                    _score += (_state.objects[j].character == 's') ? 100 : 10;
                    toRemove[i] = true;
                    toRemove[j] = true;
                    break;
                }
            }
        }
    }
    std::vector<entity_t> newObjects;
    for (size_t i = 0; i < _state.objects.size(); i++) {
        if (!toRemove[i]) {
            newObjects.push_back(_state.objects[i]);
        }
    }
    _state.objects = std::move(newObjects);
}