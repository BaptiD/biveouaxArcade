/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.hpp
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <dlfcn.h>
    #include <memory>
    #include <array>

    #include "IGame.hpp"
    #include "IGraphic.hpp"

    #define WHITE {255, 255, 255, 255}
    #define FONT_PATH "./lib/assets/arcade_menu/font/arcade.ttf"
    #define PATH_LIBS "./lib"
    #define GAME_LIBS 0
    #define GRAPHIC_LIBS 1
    #define FONT_SIZE 20
    #define OFST_PERCENTAGE 3

    #define MENU_LIB "./lib/arcade_menu.so"
    #define SET_BASE_GAME(c) (c->_state.libs.game = MENU_LIB)

namespace arcade {

class Menu : public IGame {

  public:
    Menu();
    void handleEvent(event_t) override;
    data_t update(void) override;

  private:
    std::vector<std::string> _gamePaths;
    std::vector<std::string> _graphicPaths;
    int _gameIndex = 0;
    int _graphicIndex = 0;
    data_t _state;
    
    void getLibs(void);

    template<typename Lib>
    void tryLib(const std::string& filename) {
        void *handlegame = NULL;
        Lib *(*make)(void) = NULL;
        if (!filename.compare(MENU_LIB))
            return;
        handlegame = dlopen(filename.c_str(), RTLD_LAZY);
        if (handlegame == NULL)
            return;
        if (typeid(Lib) == typeid(arcade::IGame)) {
            make = (Lib *(*)())dlsym(handlegame, "makeGame");
            if (make == NULL)
                return;
            _gamePaths.push_back(filename);
        } else {
            make = (Lib *(*)())dlsym(handlegame, "makeGraphic");
            if (make == NULL)
                return;
            _graphicPaths.push_back(filename);
        }
        dlclose(handlegame);
    }
    void buildMenu();
};

extern "C" {
    IGame *makeGame() {
        return new Menu;
    }
}

}

#endif
