#pragma once

#include"SFML/Graphics.hpp"

namespace frogger
{
	namespace textures
	{
		extern sf::Texture temp;

		namespace entities
		{
			extern sf::Texture frogIdle;
			extern sf::Texture frogJump;
			extern sf::Texture water;
			extern sf::Texture log;
			extern sf::Texture bee;
		}
		namespace backgrounds
		{
			extern sf::Texture gameplayBackground;
			extern sf::Texture menuBackground;
		}

		void Init();
	}
}