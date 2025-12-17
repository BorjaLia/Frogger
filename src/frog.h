#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "math_blib.h"

namespace frogger
{
	namespace frog
	{
		struct Frog
		{
			bool isAlive = true;

			vec::Vector2 pos = {0.0f,0.0f};
			vec::Vector2 dir = {0.0f,0.0f};

			float jumpForceMultiplier = 10.0f;
			float jumpForce = 0.0f;
			float maxJumpForce = 250.0f;
			float deceleraton = 0.8f;

			vec::Vector2 size = {0.0f,0.0f};

			vec::Vector2 coll = {0.0f,0.0f};

			std::vector<sf::Sprite> idleAnim = {};
			std::vector<sf::Sprite> jumpAnim = {};

			float animStart = 0.0f;
			float animCounter = 0.0f;

			float animFrameIncrease = 30.0f;

			bool isJumping = false;
			bool maxJump = false;

			float jumpInterval = 0.5f;
			float lastJump = 0.0f;

			std::vector<sf::Keyboard::Key> upKey;
			std::vector<sf::Keyboard::Key> leftKey;
			std::vector<sf::Keyboard::Key> dowKey;
			std::vector<sf::Keyboard::Key> rightKey;
		};

		extern Frog player;

		void Init();

		void Input();
		void Update();
		void Draw();

		void Reset();

		void TakeHit();
	}
}