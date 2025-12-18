#include "texture_manager.h"

#include <iostream>

namespace frogger
{
	namespace textures
	{
		sf::Texture temp = sf::Texture();

		namespace entities
		{
			sf::Texture frogIdle;
			sf::Texture frogJump;
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
			if (!entities::frogIdle.loadFromFile("res/img/sprite/frog_idle.png"))
			{
				std::cout << "ERROR - falied loading a texture!" << std::endl;
			}
			if (!entities::frogJump.loadFromFile("res/img/sprite/frog_jump.png"))
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