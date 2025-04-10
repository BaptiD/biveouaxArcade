/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** test.cpp
*/
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "SDL2.hpp"

arcade::SDL2::SDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw "Error: init SDL";
    _window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_FULLSCREEN);
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
            exit(0);
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

    if (std::filesystem::exists(entity_data.asset)) {
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

#include <iostream>
void arcade::SDL2::displayText(text_t text_data)
{
    std::cout << \
        text_data.fontPath.c_str() << " - " << (int)text_data.fontSize \
        << " / " << text_data.pos.x << " " << text_data.pos.y \
        << std::endl;
    if (std::filesystem::exists(text_data.fontPath))
        std::cout << "ahah\n";
    TTF_Font* font = TTF_OpenFont(text_data.fontPath.c_str(),
        (int)text_data.fontSize);
    if (font == NULL)
        std::cout << "KO" << std::endl;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font,
        text_data.value.c_str(), COLOR(text_data));
    SDL_Texture* msg = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
    SDL_Rect rect = RECT_TEXT(text_data);

    SDL_RenderCopy(_renderer, msg, NULL, &rect);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);
    SDL_DestroyTexture(msg);
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
    for (auto& text : data.texts)
        displayText(text);
    SDL_RenderPresent(_renderer);
    eventManager();
}