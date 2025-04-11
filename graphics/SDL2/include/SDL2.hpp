/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** SDL2.hpp
*/

#ifndef DLSDL2_HPP_
    #define DLSDL2_HPP_

    #include <map>
    #include <memory>
    #include <SDL2/SDL.h>

    #include "IGraphic.hpp"

    #define WINDOW_SIZE_X 1000
    #define WINDOW_SIZE_Y 1000
    #define BLACK (color_t){0, 0, 0, 255}

    // Get mouse pos in percentage
    #define MOUSE_POS_PERCENT(mPos) ((vector_t){mPos.x / WINDOW_SIZE_X * 100, mPos.y / WINDOW_SIZE_Y * 100})

    #define SIZE_ARRAY(a) (sizeof(a)/sizeof(a[0])) // Get size of no-empty any const array
    #define GET_VALUE(m, i) (m.find(i)->second) // Get value from map with index

    // Set SDL_Rect from entity data
    #define RECT(e) ((SDL_Rect){WINDOW_SIZE_X * (int)e.pos.x / 100, WINDOW_SIZE_Y * (int)e.pos.y / 100, \
        WINDOW_SIZE_X * (int)e.size.x / 100, WINDOW_SIZE_Y * (int)e.size.y / 100})
    // Set SDL_Color from entity data
    #define COLOR(e) ((SDL_Color){(Uint8)e.color.r, (Uint8)e.color.g, (Uint8)e.color.b, (Uint8)e.color.a})
    // Draw colored rectangle
    #define DRAW_RECT(re, c) (SDL_SetRenderDrawColor(re, (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, (Uint8)c.a))
    // Get height of text
    #define HEIGHT_TEXT(t) (int)(t.fontSize)
    // Get width of text
    #define WIDTH_TEXT(t) (int)(t.value.size() * t.fontSize)
    // Set SDL_Rect from text data
    #define RECT_TEXT(t) ((SDL_Rect){WINDOW_SIZE_X * (int)t.pos.x / 100, \
        WINDOW_SIZE_Y * (int)t.pos.y / 100, WIDTH_TEXT(t), HEIGHT_TEXT(t)})

    #define NOT_SET -1

const std::map<int, event_e> KEYS = {
    {SDLK_ESCAPE, A_KEY_ESC},
    {SDLK_SPACE, A_KEY_SPACE},
    {SDLK_BACKSPACE, A_KEY_DEL},
    {SDLK_RETURN, A_KEY_ENTER},
    {SDLK_TAB, A_KEY_TAB},
    {SDLK_LCTRL, A_KEY_CTRL},
    {SDLK_LSHIFT, A_KEY_SHIFT},
    {NOT_SET, A_KEY_SHIFTLOCK},
    {SDLK_LALT, A_KEY_ALT},
    {NOT_SET, A_KEY_SQUARE},
    {SDLK_UP, A_KEY_UP},
    {SDLK_DOWN, A_KEY_DOWN},
    {SDLK_LEFT, A_KEY_LEFT},
    {SDLK_RIGHT, A_KEY_RIGHT},
    {SDLK_a, A_KEY_A},
    {SDLK_b, A_KEY_B},
    {SDLK_c, A_KEY_C},
    {SDLK_d, A_KEY_D},
    {SDLK_e, A_KEY_E},
    {SDLK_f, A_KEY_F},
    {SDLK_g, A_KEY_G},
    {SDLK_h, A_KEY_H},
    {SDLK_i, A_KEY_I},
    {SDLK_j, A_KEY_J},
    {SDLK_k, A_KEY_K},
    {SDLK_l, A_KEY_L},
    {SDLK_m, A_KEY_M},
    {SDLK_n, A_KEY_N},
    {SDLK_o, A_KEY_O},
    {SDLK_p, A_KEY_P},
    {SDLK_q, A_KEY_Q},
    {SDLK_r, A_KEY_R},
    {SDLK_s, A_KEY_S},
    {SDLK_t, A_KEY_T},
    {SDLK_u, A_KEY_U},
    {SDLK_v, A_KEY_V},
    {SDLK_w, A_KEY_W},
    {SDLK_x, A_KEY_X},
    {SDLK_y, A_KEY_Y},
    {SDLK_z, A_KEY_Z},
    {SDLK_0, A_KEY_0},
    {SDLK_1, A_KEY_1},
    {SDLK_2, A_KEY_2},
    {SDLK_3, A_KEY_3},
    {SDLK_4, A_KEY_4},
    {SDLK_5, A_KEY_5},
    {SDLK_6, A_KEY_6},
    {SDLK_7, A_KEY_7},
    {SDLK_8, A_KEY_8},
    {SDLK_9, A_KEY_9},
    {SDL_BUTTON_LEFT, A_MOUSE_LEFT},
    {SDL_BUTTON_RIGHT, A_MOUSE_RIGHT},
    {SDL_BUTTON_MIDDLE, A_MOUSE_MIDDLE},
    {NOT_SET, A_MOUSE_XBUTTON1},
    {NOT_SET, A_MOUSE_XBUTTON2},
    {NOT_SET, A_MOUSE_VERTICALWHEEL},
    {NOT_SET, A_MOUSE_HORIZONTALWHEEL},
    {SDL_MOUSEMOTION, A_MOUSE_MOVE},
};

namespace arcade {

class SDL2 : public IGraphic{
    
    public:
        SDL2();
        ~SDL2();
        event_t getEvent(void) override;
        void display(data_t) override;

    private:
        bool eventNotAllreadySet(event_e);
        void eventManager(void);
        void displayText(text_t text_data);
        void displayEntity(entity_t entity);
        SDL_Window *_window = NULL;
        SDL_Renderer *_renderer = NULL;
        SDL_Event _SDLevent;
        event_t _events;

};

extern "C" {
    IGraphic *makeGraphic() {
        return new SDL2;
    }
}
}

#endif
