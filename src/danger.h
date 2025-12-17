#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "math_blib.h"

namespace frogger
{
	namespace danger
	{
		enum Type
		{
			STATIC,
			OPEN_PATH,
			CLOSED_PATH,
			FOLLOW
		};

		struct Danger
		{
			Type type = Type::STATIC;

			vec::Vector2 pos = { 0.0f,0.0f };
			vec::Vector2 dir = { 0.0f,0.0f };

			std::vector<vec::Vector2> path = {};

			vec::Vector2 size = { 0.0f,0.0f };

			vec::Vector2 coll = { 0.0f,0.0f };

			std::vector<sf::Sprite> anim = {};

			float animStart = 0.0f;
			float animCounter = 0.0f;

			float animFrameIncrease = 30.0f;
		};

		extern std::vector<Danger> dangers;

		void Init();

		void Update();
		void Draw();

		void Reset();
	}
}