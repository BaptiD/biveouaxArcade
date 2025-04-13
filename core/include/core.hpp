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
    #define MENU_LIB "./lib/arcade_menu.so"
    #define PATH_LIBS "./lib"
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

        template<typename Lib>
        bool tryLib(const std::string& filename) {
            void *handlegame = NULL;
            Lib *(*make)(void) = NULL;
            if (!filename.compare(MENU_LIB))
                return false;
            handlegame = dlopen(filename.c_str(), RTLD_LAZY);
            if (handlegame == NULL)
                return false;
            if (typeid(Lib) == typeid(arcade::IGame)) {
                make = (Lib *(*)())dlsym(handlegame, "makeGame");
                if (make == NULL)
                    return false;
                _gamePaths.push_back(filename);
            } else {
                make = (Lib *(*)())dlsym(handlegame, "makeGraphic");
                if (make == NULL)
                    return false;
                _graphicPaths.push_back(filename);
            }
            dlclose(handlegame);
            return true;
        }

        std::size_t _graphicIndex = 0;
        std::size_t _gameIndex = 0;
        bool _update = false;
        std::vector<std::string> _graphicPaths;
        std::vector<std::string> _gamePaths;

        int checkCoreEvents(event_t);
        data_t checkLibUpdate(libPaths_t paths, data_t data);
        data_t setupNewGame(void);
};

}

#endif
