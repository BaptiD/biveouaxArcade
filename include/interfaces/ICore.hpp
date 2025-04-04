/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** ICore.hpp
*/

#ifndef ICORE_HPP_
    #define ICORE_HPP_

    #include <string>
    #include "tool.hpp"

namespace arcade {

class ICore {

    public:
        virtual ~ICore() = default;
        virtual void run(void) = 0;
        virtual void load(std::string libPath, typeLib_e type) = 0;

    private:

};

}

#endif
