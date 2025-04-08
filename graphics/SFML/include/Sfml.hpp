/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.hpp
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "IGraphic.hpp"
#include "updates.hpp"

namespace arcade {
class Sfml : public IGraphic {
  public:
    Sfml();
    ~Sfml() override;
    event_t getEvent() override;
    void display(data_t data) override;
    
  private:
    sf::RenderWindow window;
};

extern "C" IGraphic* makeGraphic() {
    return new Sfml();
};

};

#endif