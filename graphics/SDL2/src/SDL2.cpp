/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** test.cpp
*/
#include <unistd.h>
#include <SDL2/SDL_image.h>

#include "SDL2.hpp"

arcade::SDL2::SDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw "Error: init SDL";
    _window = SDL_CreateWindow("SDL2",SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_SHOWN);
    if (_window == NULL)
        throw "Error: init SDL window";
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw "Error: init SDL renderer failed";
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
}

arcade::SDL2::~SDL2()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

event_t arcade::SDL2::getEvent(void)
{
    return _events;
}

void arcade::SDL2::eventManager(void)
{
    const Uint8 *keystate = NULL;

    if (SDL_PollEvent(&_SDLevent)) {
        if (_SDLevent.type == SDL_QUIT)
            exit(1);
    }
    keystate = SDL_GetKeyboardState(NULL);
    if (keystate != NULL) {
        for (std::size_t i = 0; i < SIZE_ARRAY(keystate); ++i) {
            if (keystate[i]) {
                _events.events.push_back(GET_VALUE(KEYS, i));
            }
        }
    }
}

void arcade::SDL2::displayEntity(entity_t entity_data)
{
    SDL_Surface *sprite = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect = RECT(entity_data);

    if (access(entity_data.asset.c_str(), F_OK)) {
        sprite = IMG_Load(entity_data.asset.c_str());
        texture = SDL_CreateTextureFromSurface(_renderer, sprite);
        SDL_FreeSurface(sprite);
        SDL_RenderCopy(_renderer, texture, &rect, &rect);
        SDL_DestroyTexture(texture);
    } else {
        DRAW_RECT(_renderer, entity_data);
        SDL_RenderFillRect(_renderer, &rect);
        SDL_RenderDrawRect(_renderer, &rect);
    }
}

void arcade::SDL2::display(data_t data)
{
    SDL_RenderClear(_renderer);
    for (auto& bg : data.bg)
        displayEntity(bg);
    for (auto& ui : data.ui)
        displayEntity(ui);
    for (auto& objects : data.objects)
        displayEntity(objects);
    eventManager();
}