#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "math_blib.h"

namespace frogger
{
	namespace object
	{
		enum Type
		{
			DANGER,
			PLATFORM
		};

		enum PathType
		{
			STATIC,
			OPEN_PATH,
			CLOSED_PATH,
			FOLLOW
		};

		struct Entity
		{
			Type type = Type::DANGER;
			PathType pathType = PathType::STATIC;

			vec::Vector2 pos = { 0.0f,0.0f };
			vec::Vector2 dir = { 0.0f,0.0f };

			float speed = 50.0f;

			std::vector<vec::Vector2> path = {};
			int objective = 0;

			vec::Vector2 size = { 0.0f,0.0f };

			vec::Vector2 coll = { 0.0f,0.0f };

			std::vector<sf::Sprite> anim = {};

			float animStart = 0.0f;
			float animCounter = 0.0f;

			float animFrameIncrease = 30.0f;
		};

		extern std::vector<Entity> entities;

		void Init();

		void Update();
		void Draw();

		void Reset();
	}
}