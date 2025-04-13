/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** test.cpp
*/
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SDL2.hpp"

arcade::SDL2::SDL2()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw SDL_GetError();
    _window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_SHOWN);
    if (_window == NULL)
        throw SDL_GetError();
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw SDL_GetError();
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    TTF_Init();
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        throw SDL_GetError();
    Mix_Volume(1, MIX_MAX_VOLUME);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    CHANGE_RENDER_COLOR(_renderer, BLACK);
}

arcade::SDL2::~SDL2()
{
    for (Mix_Music*&music : _musics)
        Mix_FreeMusic(music);
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
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
        if (_SDLevent.type == SDL_KEYDOWN) {
            if (eventNotAllreadySet(GET_VALUE(KEYS, GET_KEY_EVENT(_SDLevent))))
                _events.events.push_back(GET_VALUE(KEYS, GET_KEY_EVENT(_SDLevent)));
            if (GET_KEY_EVENT(_SDLevent) == SDLK_ESCAPE || GET_KEY_EVENT(_SDLevent) == SDLK_e)
                Mix_PauseMusic();
        }
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

double getAngle(direction_e direction)
{
    if (direction == UP)
        return 0.0;
    if (direction == DOWN)
        return 180.0;
    if (direction == LEFT)
        return 270.0;
    if (direction == RIGHT)
        return 90.0;
    return 0.0;
}

void arcade::SDL2::displayEntity(entity_t entity_data)
{
    SDL_Surface *sprite = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect = RECT(entity_data);

    if (std::filesystem::exists(entity_data.asset)) {
        sprite = IMG_Load(entity_data.asset.c_str());
        texture = SDL_CreateTextureFromSurface(_renderer, sprite);
        SDL_RenderCopyEx(_renderer, texture, NULL, &rect,
            getAngle(entity_data.direction), NULL, SDL_FLIP_NONE);
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

void arcade::SDL2::playSound(std::string path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());

    if (music == NULL)
        return;
    _musics.push_back(music);
    Mix_PlayMusic(music, -1);
}

void arcade::SDL2::display(data_t data)
{
    SDL_RenderClear(_renderer);
    for (entity_t& bg : data.bg)
        displayEntity(bg);
    for (entity_t& ui : data.ui)
        displayEntity(ui);
    for (entity_t& objects : data.objects)
        displayEntity(objects);
    for (text_t& text : data.texts)
        displayText(text);
    for (std::string& audio : data.audios)
        playSound(audio);
    SDL_RenderPresent(_renderer);
    eventManager();
}