/*
** EPITECH PROJECT, 2024
** biveouaxArcade
** File description:
** Sfml.hpp
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>
	#include <SFML/Window.hpp>
	#include <iostream>
	#include "IGraphic.hpp"
	#include "updates.hpp"

	#define WIN_SIZE_X 1000
	#define WIN_SIZE_Y 1000

namespace arcade {
	class Sfml : public IGraphic {
		public:
			Sfml();
			~Sfml() override;
			event_t getEvent() override;
			void display(data_t data) override;
			void drawSprites(std::vector<entity_t> entities);
			void drawTexts(std::vector<text_t> texts);
			sf::Sprite rotateSprite(sf::Sprite, int direction, sf::Vector2f size);
			void playMusic(std::vector<std::string>);

		private:
			static const std::map<int, event_e> _conversionKeyboard;
			static const std::map<int, event_e> _conversionMouse;
			sf::RenderWindow _window;
			sf::Music _music;
	};

	extern "C" IGraphic* makeGraphic() {
		return new Sfml();
	};

};

#endif
