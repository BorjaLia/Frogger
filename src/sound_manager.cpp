#include "sound_manager.h"

#include <iostream>

namespace frogger
{
	namespace sounds
	{
		namespace entities
		{
			sf::SoundBuffer jumpBuffer;
			sf::Sound jump{ jumpBuffer };
		}
		namespace backgrounds
		{
			sf::Music gameplayBackground;
			sf::Music menuBackground;
		}

		void Init()
		{
			if (!entities::jumpBuffer.loadFromFile("res/snd/entity/jump.wav"))
			{
				std::cout << "ERROR - falied loading a sound!" << std::endl;
			}

			if (!backgrounds::gameplayBackground.openFromFile("res/snd/entity/gameplay_music.ogg"))
			{
				std::cout << "ERROR - falied loading music!" << std::endl;
			}
		}
	}
}