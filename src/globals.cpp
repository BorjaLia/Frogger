#include "globals.h"

namespace frogger
{
	namespace global
	{
		bool isRunning = true;

		float deltaTime = 0.0f;

		float screenWidth = 600;
		float screenHeight = 1080;

		sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(global::screenWidth), static_cast<unsigned int>(global::screenHeight) }), "Frogger!");
		sf::View camera = window.getView();

		sf::Font font = sf::Font("res/font/Jumps Winter.ttf");
	}
}