/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** core.hpp
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <string>
    #include "dynamicLib.hpp"
    #include "IGame.hpp"
    #include "IGraphic.hpp"
    #include "ICore.hpp"

    #define MENU_PATH_LIB "./lib/arcade_menu.so"

namespace arcade {
    class core : public ICore {

        public:
            int run(std::string graphPath) override;
            int load(std::string gamePath, std::string graphPath) override;

        private:
            dlManage<IGraphic> _graphic;
            dlManage<IGame> _game;
            int loop(void);
    };
}

#endif
