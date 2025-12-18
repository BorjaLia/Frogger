#pragma once

#include "SFML/Audio.hpp"

namespace frogger
{
	namespace sounds
	{
		namespace entities
		{
			extern sf::SoundBuffer jumpBuffer;
			extern sf::Sound jump;
		}
		namespace backgrounds
		{
			extern sf::Music gameplayBackground;
			extern sf::Music menuBackground;
		}

		void Init();
	}
}