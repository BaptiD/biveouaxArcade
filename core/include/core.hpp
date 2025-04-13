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
    #define CORE_EXIT 1

namespace arcade {

/**
 * @brief 
 * 
 */
class core : public ICore {

    public:
        core(std::string graphicPath);
        void run(void) override;
        void load(std::string libPath, typeLib_e type) override;

    private:
        dlManage<IGraphic> _graphic;
        dlManage<IGame> _game;
        std::string _graphicpath;

        int checkCoreEvents(event_t);
        data_t checkLibUpdate(libPaths_t paths, data_t data);
        data_t setupNewGame(void);
};

}

#endif
