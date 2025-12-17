#pragma once

#include "SFML/Graphics.hpp"

namespace frogger
{
	namespace global
	{
		extern bool isRunning;

		extern float deltaTime;

		extern float timeCounter;
		extern int frameCounter;

		extern float screenWidth;
		extern float screenHeight;

		extern sf::RenderWindow window;
		extern sf::View camera;

		extern sf::Font font;

		void Update();
	}
}