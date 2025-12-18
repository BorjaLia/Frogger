#include "texture_manager.h"

#include <iostream>

namespace frogger
{
	namespace textures
	{
		namespace entities
		{
			sf::Texture frog;
			sf::Texture water;
			sf::Texture log;
			sf::Texture bee;
		}
		namespace backgrounds
		{
			sf::Texture gameplayBackground;
			sf::Texture menuBackground;
		}

		void Init()
		{
			if (!entities::frog.loadFromFile("res/img/sprite/frog.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
			if (!entities::water.loadFromFile("res/img/sprite/water.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
			if (!entities::log.loadFromFile("res/img/sprite/log.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
			if (!entities::bee.loadFromFile("res/img/sprite/bee.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}

			if (!backgrounds::gameplayBackground.loadFromFile("res/img/background/gameplay_background.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
			if (!backgrounds::menuBackground.loadFromFile("res/img/background/menu_background.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
		}
	}
}