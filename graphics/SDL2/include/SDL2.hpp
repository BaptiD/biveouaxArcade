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

    #define WINDOW_SIZE_X 1280
    #define WINDOW_SIZE_Y 720

    #define SIZE_ARRAY(a) (sizeof(a)/sizeof(a[0])) // Get size of no-empty any const array
    #define GET_VALUE(m, i) (m.find(i)->second) // Get value from map with index

    #define RECT(e) ((SDL_Rect){(int)e.pos.x, (int)e.pos.y, (int)e.size.y, (int)e.size.x}) // Get the rectangle from an entity data
    #define COLOR(e) ((SDL_Color){(Uint8)e.color.r, (Uint8)e.color.g, (Uint8)e.color.b}) // Get color from an entity or text
    #define DRAW_RECT(re, e) (SDL_SetRenderDrawColor(re, e.color.r, e.color.g, e.color.b, e.color.a)) // Draw colored rectangle
    #define RECT_TEXT(t) ((SDL_Rect){(int)t.pos.x, (int)t.pos.y, 0, 0}) // Get the rectangle from an text data

    #define NOT_SET -1

const std::map<int, event_e> KEYS = {
    {SDL_SCANCODE_ESCAPE, A_KEY_ESC},
    {SDL_SCANCODE_SPACE, A_KEY_SPACE},
    {SDL_SCANCODE_RETURN, A_KEY_DEL},
    {SDL_SCANCODE_BACKSPACE, A_KEY_ENTER},
    {SDL_SCANCODE_TAB, A_KEY_TAB},
    {SDL_SCANCODE_LCTRL, A_KEY_CTRL},
    {SDL_SCANCODE_LSHIFT, A_KEY_SHIFT},
    {NOT_SET, A_KEY_SHIFTLOCK},
    {SDL_SCANCODE_LALT, A_KEY_ALT},
    {NOT_SET, A_KEY_SQUARE},
    {SDL_SCANCODE_UP, A_KEY_UP},
    {SDL_SCANCODE_DOWN, A_KEY_DOWN},
    {SDL_SCANCODE_LEFT, A_KEY_LEFT},
    {SDL_SCANCODE_RIGHT, A_KEY_RIGHT},
    {SDL_SCANCODE_A, A_KEY_A},
    {SDL_SCANCODE_B, A_KEY_B},
    {SDL_SCANCODE_C, A_KEY_C},
    {SDL_SCANCODE_D, A_KEY_D},
    {SDL_SCANCODE_E, A_KEY_E},
    {SDL_SCANCODE_F, A_KEY_F},
    {SDL_SCANCODE_G, A_KEY_G},
    {SDL_SCANCODE_H, A_KEY_H},
    {SDL_SCANCODE_I, A_KEY_I},
    {SDL_SCANCODE_J, A_KEY_J},
    {SDL_SCANCODE_K, A_KEY_K},
    {SDL_SCANCODE_L, A_KEY_L},
    {SDL_SCANCODE_M, A_KEY_M},
    {SDL_SCANCODE_N, A_KEY_N},
    {SDL_SCANCODE_O, A_KEY_O},
    {SDL_SCANCODE_P, A_KEY_P},
    {SDL_SCANCODE_Q, A_KEY_Q},
    {SDL_SCANCODE_R, A_KEY_R},
    {SDL_SCANCODE_S, A_KEY_S},
    {SDL_SCANCODE_T, A_KEY_T},
    {SDL_SCANCODE_U, A_KEY_U},
    {SDL_SCANCODE_V, A_KEY_V},
    {SDL_SCANCODE_W, A_KEY_W},
    {SDL_SCANCODE_X, A_KEY_X},
    {SDL_SCANCODE_Y, A_KEY_Y},
    {SDL_SCANCODE_Z, A_KEY_Z},
    {SDL_SCANCODE_0, A_KEY_0},
    {SDL_SCANCODE_1, A_KEY_1},
    {SDL_SCANCODE_2, A_KEY_2},
    {SDL_SCANCODE_3, A_KEY_3},
    {SDL_SCANCODE_4, A_KEY_4},
    {SDL_SCANCODE_5, A_KEY_5},
    {SDL_SCANCODE_6, A_KEY_6},
    {SDL_SCANCODE_7, A_KEY_7},
    {SDL_SCANCODE_8, A_KEY_8},
    {SDL_SCANCODE_9, A_KEY_9},
    {NOT_SET, A_MOUSE_LEFT},
    {NOT_SET, A_MOUSE_RIGHT},
    {NOT_SET, A_MOUSE_MIDDLE},
    {NOT_SET, A_MOUSE_XBUTTON1},
    {NOT_SET, A_MOUSE_XBUTTON2},
    {NOT_SET, A_MOUSE_VERTICALWHEEL},
    {NOT_SET, A_MOUSE_HORIZONTALWHEEL},
};

namespace arcade {

class SDL2 : public IGraphic{
    
    public:
        SDL2();
        ~SDL2();
        event_t getEvent(void) override;
        void display(data_t) override;

    private:
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
