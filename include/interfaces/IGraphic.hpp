/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** IGraphic.hpp
*/

#ifndef IGRAPHIC_HPP_
    #define IGRAPHIC_HPP_

    #include "events.hpp"
    #include "updates.hpp"

    #define GRAPHIC_MAKER "makeGraphic" // Name of the extern function to create graphic class

namespace arcade {

    class IGraphic {

        public:
            virtual ~IGraphic() = default;
            virtual event_t getEvent(void) = 0;
            virtual void display(data_t) = 0;

        private:

    };
}

#endif