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
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw "Error: init SDL";
    _window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_SHOWN);
    if (_window == NULL)
        throw "Error: init SDL window";
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw "Error: init SDL renderer failed";
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    CHANGE_RENDER_COLOR(_renderer, BLACK);
}

arcade::SDL2::~SDL2()
{
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

event_t arcade::SDL2::getEvent(void)
{
    event_t giveEvent = _events;

    _events.events.clear();
    giveEvent.mPos = MOUSE_POS_PERCENT(giveEvent.mPos);
    return giveEvent;
}

bool arcade::SDL2::eventNotAllreadySet(event_e event)
{
    for (std::size_t i = 0; i < _events.events.size(); ++i)
        if (event == _events.events[i])
            return false;
    return true;
}

void arcade::SDL2::eventManager(void)
{
    int x, y = 0;

    while (SDL_PollEvent(&_SDLevent)) {
        if (_SDLevent.type == SDL_QUIT)
            exit(0);
        if (_SDLevent.type == SDL_KEYDOWN)
            if (eventNotAllreadySet(GET_VALUE(KEYS, _SDLevent.key.keysym.sym)))
                _events.events.push_back(GET_VALUE(KEYS, _SDLevent.key.keysym.sym));
        if(_SDLevent.type == SDL_MOUSEMOTION) {
            _events.events.push_back(GET_VALUE(KEYS, SDL_MOUSEMOTION));
            SDL_GetGlobalMouseState(&x, &y);
            _events.mPos.x = (double)x;
            _events.mPos.y = (double)y;
        }
        if (_SDLevent.type == SDL_MOUSEBUTTONDOWN) {
            if (eventNotAllreadySet(GET_VALUE(KEYS, _SDLevent.button.button)))
                _events.events.push_back(GET_VALUE(KEYS, _SDLevent.button.button));
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
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(sprite);
        SDL_DestroyTexture(texture);
    } else {
        CHANGE_RENDER_COLOR(_renderer, entity_data.color);
        SDL_RenderFillRect(_renderer, &rect);
        CHANGE_RENDER_COLOR(_renderer, BLACK);
    }
}

void arcade::SDL2::displayText(text_t text_data)
{
    TTF_Font* font = TTF_OpenFont(text_data.fontPath.c_str(),
        (int)text_data.fontSize);
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