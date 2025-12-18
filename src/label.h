#pragma once

#include <SFML/Graphics.hpp>

#include "math_blib.h"


namespace frogger
{
	namespace label
	{
		struct Label
		{
			vec::Vector2 pos;
			std::string text;
			sf::Color color;
			int fontSize = 0;
		};

		Label Init(vec::Vector2 pos, std::string text, int fontSize, sf::Color color);
		Label Init(vec::Vector2 pos, char text, int fontSize, sf::Color color);
		void Draw(Label& label, sf::RenderWindow& window);
	}
}