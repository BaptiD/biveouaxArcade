/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** menu.hpp
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "memory"
    #include "array"
    #include "IGame.hpp"

    #define WHITE {255, 255, 255, 255}
    #define FONT_PATH "./lib/assets/arcade_menu/font/arcade.ttf"
    #define PATH_LIBS "./lib"
    #define GAME_LIBS 0
    #define GRAPHIC_LIBS 1
    #define FONT_SIZE 20
    #define OFST_PERCENTAGE 3


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
    void buildMenu();
};

extern "C" {
    IGame *makeGame() {
        return new Menu;
    }
}

}

#endif
