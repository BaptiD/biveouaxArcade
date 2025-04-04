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

    #define PATH_LIBS "./lib"
    #define GAME_LIBS 0
    #define GRAPHIC_LIBS 1


namespace arcade {

class Menu : public IGame {

    public:
        void getEvent(event_t) override;
        data_t update(void) override;

    private:
        void getLibs(void);
        std::array<std::vector<std::string>, 2> _libs;

};

extern "C" {
    IGame *makeGame() {
        return new Menu;
    }
}

}

#endif
