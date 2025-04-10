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

	#define WIN_SIZE_X 1700
	#define WIN_SIZE_Y 1700

namespace arcade {
	class Sfml : public IGraphic {
		public:
			Sfml();
			~Sfml() override;
			event_t getEvent() override;
			void display(data_t data) override;
			void drawSprites(std::vector<entity_t> entities);
			void drawTexts(std::vector<text_t> texts);

		private:
			static const std::map<int, event_e> _conversionMap;
			sf::RenderWindow _window;
			sf::Font _font;
	};

	extern "C" IGraphic* makeGraphic() {
		return new Sfml();
	};

};

#endif