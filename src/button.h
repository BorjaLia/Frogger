#pragma once

#include <SFML/Graphics.hpp>

#include "math_blib.h"

namespace frogger
{
	namespace button
	{
		enum class State
		{
			Normal,
			Hover,
			Pressed
		};

		struct Button
		{
			vec::Vector2 pos;
			vec::Vector2 size;

			std::string text;
			State state;
			bool clicked = false;
		};

		Button Init(vec::Vector2 pos, vec::Vector2 size, std::string text);
		void Update(Button& button);
		void Draw(Button& button);

	}
}