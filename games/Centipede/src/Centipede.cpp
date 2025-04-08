/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Centipede.cpp
*/

#include "Centipede.hpp"

#include <cstdlib>

arcade::Centipede::Centipede() {
    entity_t centipede;
    entity_t mushroom;
    entity_t player;

    player.pos = {10, 20};
    player.character = 'P';
    _state.objects.push_back(player);

    //the centipede
    for (size_t i = 0; i < 10; i++) {
        centipede.pos = {(double)5 + i, 5};
        centipede.character = 'S';
        _state.objects.push_back(centipede);
    }

    //some mushrooms
    for (size_t i = 0; i < 5; i++) {
        mushroom.pos = {(double)(rand() % 30), (double)(rand() % 15)};
        mushroom.character = 'M';
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
            _state.objects[0].pos.x = std::min((double)0, _state.objects[0].pos.x - 1);
        if (event == A_KEY_D)
            _state.objects[0].pos.x = std::min((double)30, _state.objects[0].pos.x + 1);
        if (event == A_KEY_Z)
            _state.objects[0].pos.y = std::min((double)0, _state.objects[0].pos.y - 1);
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
        if (entity.character == 'S') {
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
    _state.objects.erase(std::__remove_if(_state.objects.begin(), _state.objects.end(), [](entity_t& entity) {
        return entity.character == '*' && entity.pos.y < 0;
        }),
        _state.objects.end()
    );
}

void arcade::Centipede::handleCollision() {
    std::vector<entity_t>::iterator bulletIt;
    for (bulletIt = _state.objects.begin(); bulletIt != _state.objects.end();) {
        if (bulletIt->character != '*') {
            bulletIt++;
            continue;
        }
    }

    bool hit = false;

    for (auto targetIt = _state.objects.begin(); targetIt != _state.objects.end(); ) {
        if ((targetIt->character == 'M' || targetIt->character == 'S')
            && bulletIt->pos.x == targetIt->pos.x
            && bulletIt->pos.y == targetIt->pos.y) {
                _score += (targetIt->character == 'S') ? 100 : 10;
                targetIt = _state.objects.erase(targetIt);
                hit = true;
                break;
        } else {
            targetIt++;
        }
    }
    if (hit)
        bulletIt = _state.objects.erase(bulletIt);
    else
        bulletIt++;
}