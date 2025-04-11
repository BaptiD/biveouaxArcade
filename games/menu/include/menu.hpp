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
    void findLibs(void)
    {
        void *handlegame = NULL;
        Lib *(*gamelib)(void) = NULL;
        std::vector<std::string> paths;

        for (const auto &lib : std::filesystem::directory_iterator(PATH_LIBS)) {
            const std::string filename = lib.path();
            if (!filename.compare(MENU_LIB))
                continue;
            handlegame = dlopen(filename.c_str(), RTLD_LAZY);
            if (handlegame == NULL)
                continue;
            gamelib = (Lib *(*)())dlsym(handlegame, "makeGame");
            if (gamelib == NULL)
                continue;
            if (typeid(Lib) == typeid(arcade::IGame))
            _path.push_back(filename);
            dlclose(handlegame);
        }
        return paths;
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
