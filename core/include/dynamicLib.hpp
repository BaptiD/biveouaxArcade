/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** dynamicLib.hpp
*/

#ifndef LIBLD_HPP_
    #define LIBLD_HPP_

    #include <dlfcn.h>
    #include <string>
    #include <exception>
    #include <memory>
    #include "events.hpp"
    #include "updates.hpp"
    #include "IGame.hpp"
    #include "IGraphic.hpp"

    #define CALL(lib)(lib.call())

namespace arcade {

class dynLibError : public std::exception {
    public:
        dynLibError(void) noexcept {errMessage = dlerror();};
        const char *what() const noexcept override{
            return errMessage.c_str();
        }
    private:
        std::string errMessage;
};

template<typename Lib>
class dlManage {
    public:
        ~dlManage() {closeLib();};

        void openLib(const std::string& libPath)
        {
            Lib *(*make)(void) = NULL;

            _handle = dlopen(libPath.c_str(), RTLD_LAZY);
            if (_handle == NULL)
                throw arcade::dynLibError();
            if (typeid(Lib) == typeid(IGraphic))
                make = (Lib *(*)())dlsym(_handle, GRAPHIC_MAKER);
            else
                make = (Lib *(*)())dlsym(_handle, GAME_MAKER);
            if (make == NULL) {
                throw arcade::dynLibError();
            }
            _lib = make();
        }

        void closeLib(void)
        {
            if (_handle != NULL)
                dlclose(_handle);
            if (_lib != NULL)
                free(_lib);
        }

        Lib *call(void)
        {
            return _lib;
        }

    private:
        void *_handle = NULL;
        Lib *_lib = NULL;
};

};

#endif