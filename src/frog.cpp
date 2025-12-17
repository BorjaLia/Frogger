#include "frog.h"

#include "globals.h"

#include <iostream>

namespace frogger
{
	namespace frog
	{
		static void prepareJump(vec::Vector2 dir, bool& preparingJump);
		static void JumpUpdate();
		static void BordersUpdate();
	}

	namespace frog
	{
		namespace defaults
		{
			const bool isAlive = true;

			const vec::Vector2 size = { 20.0f,20.0f };

			const vec::Vector2 pos = { (global::screenWidth / 2.0f),(global::screenHeight * 0.75f) };
			const vec::Vector2 dir = { 0.0f,0.0f };

			const float jumpForceMultiplier = 4000.0f;
			const float jumpForce = 0.0f;
			const float maxJumpForce = 2000.0f;
			const float deceleraton = 8000.0f;

			const vec::Vector2 coll = { 18.0f,18.0f };

			const float animStart = 0.0f;
			const float animCounter = 0.0f;

			const float animFrameIncrease = 30.0f;

			const bool isJumping = false;
			const bool maxJump = false;

			const float jumpInterval = 0.5f;
			const float lastJump = -jumpInterval;
		}

		Frog player = Frog();

		void Init()
		{
			player.upKey = { sf::Keyboard::Key::W, sf::Keyboard::Key::Up };
			player.leftKey = { sf::Keyboard::Key::A, sf::Keyboard::Key::Left };
			player.dowKey = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
			player.rightKey = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };
			Reset();
		}

		void Input()
		{
			if (player.lastJump + player.jumpInterval >= global::timeCounter || player.isJumping)
			{
				return;
			}

			bool preparingJump = false;

			for (int k = 0; k < player.upKey.size(); k++)
			{
				if (sf::Keyboard::isKeyPressed(player.upKey[k]))
				{
					prepareJump(vec::Vector2(0.0f, -1.0f), preparingJump);
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.leftKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.leftKey[k]))
					{
						prepareJump(vec::Vector2(-1.0f, 0.0f), preparingJump);
					}
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.dowKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.dowKey[k]))
					{
						prepareJump(vec::Vector2(0.0f, 1.0f), preparingJump);
					}
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.rightKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.rightKey[k]))
					{
						prepareJump(vec::Vector2(1.0f, 0.0f), preparingJump);
					}
				}
			}

			if (!preparingJump && player.jumpForce != defaults::jumpForce)
			{
				player.lastJump = global::timeCounter;
				player.isJumping = true;
				player.maxJump = false;
				std::cout << "jump with " << player.jumpForce << " force " << player.maxJumpForce << std::endl;
				player.jumpForce = defaults::jumpForce;
			}
		}

		void Update()
		{
			if (player.isAlive)
			{
				JumpUpdate();
				BordersUpdate();
			}
		}

		void Draw()
		{
#ifdef _DEBUG
			sf::RectangleShape sizeShape({ player.size.x,player.size.y });
			sizeShape.setPosition(sf::Vector2f(player.pos.x - (player.size.x / 2.0f), player.pos.y - (player.size.y / 2.0f)));
			sizeShape.setFillColor(sf::Color::Red);
			global::window.draw(sizeShape);

			sf::RectangleShape collShape({ player.coll.x,player.coll.y });
			collShape.setPosition(sf::Vector2f(player.pos.x - (player.coll.x / 2.0f), player.pos.y - (player.coll.y / 2.0f)));
			collShape.setFillColor(sf::Color((unsigned char)((player.jumpForce / player.maxJumpForce) * 254.0f), (unsigned char)((1.0f - (player.jumpForce / player.maxJumpForce)) * 254.0f), (unsigned char)(100)));
			if (player.maxJump)
			{
				collShape.setFillColor(sf::Color::Blue);
			}
			if (!player.isAlive)
			{
				collShape.setFillColor(sf::Color::Red);
			}
			global::window.draw(collShape);

			float radius = 5.0f;
			sf::CircleShape center(radius);
			center.setPosition(sf::Vector2f(player.pos.x - (radius), player.pos.y - (radius)));
			center.setFillColor(sf::Color::Magenta);
			global::window.draw(center);
#endif // _DEBUG
		}

		void Reset()
		{
			player.isAlive = defaults::isAlive;

			player.pos = defaults::pos;
			player.dir = defaults::dir;

			player.jumpForceMultiplier = defaults::jumpForceMultiplier;
			player.jumpForce = defaults::jumpForce;
			player.maxJumpForce = defaults::maxJumpForce;
			player.deceleraton = defaults::deceleraton;

			player.size = defaults::size;

			player.coll = defaults::coll;

			player.animStart = defaults::animStart;
			player.animCounter = defaults::animCounter;

			player.animFrameIncrease = defaults::animFrameIncrease;

			player.isJumping = defaults::isJumping;
			player.maxJump = defaults::maxJump;

			player.jumpInterval = defaults::jumpInterval;
			player.lastJump = defaults::lastJump;
		}

		void TakeHit()
		{
			player.isAlive = false;
		}

		static void prepareJump(vec::Vector2 dir, bool& preparingJump)
		{
			std::cout << "charge... " << player.jumpForce << std::endl;

			player.jumpForce += player.jumpForceMultiplier * global::deltaTime;
			if (player.jumpForce >= player.maxJumpForce * 0.9f)
			{
				player.maxJump = true;
			}
			mth::Clamp(player.jumpForce, player.maxJumpForce * 0.1f, player.maxJumpForce);
			player.dir = dir * player.jumpForce;
			preparingJump = true;
		}

		static void JumpUpdate()
		{
			if (player.isJumping)
			{
				player.pos += player.dir * global::deltaTime;

				float currentSpeed = player.dir.magnitude();
				float speedDrop = player.deceleraton * global::deltaTime;

				if (currentSpeed > speedDrop)
				{
					player.dir = (player.dir * (1.0f / currentSpeed)) * (currentSpeed - speedDrop);
				}
				else
				{
					player.dir = { 0.0f, 0.0f };
					player.isJumping = false;
				}
			}
		}

		static void BordersUpdate()
		{
			float speedMultiplier = 0.4f;

			if (player.pos.x < 0.0f && player.dir.x < 0.0f)
			{
				player.dir.x *= -speedMultiplier;
				player.pos.x = 0.0f;
			}

			if (player.pos.x + (player.size.x / 2.0f) > global::screenWidth && player.dir.x > 0.0f)
			{
				player.dir.x *= -speedMultiplier;
				player.pos.x = player.pos.x + (player.size.x / 2.0f);
			}

			if (player.pos.y < 0.0f && player.dir.y < 0.0f)
			{
				player.dir.y *= -speedMultiplier;
				player.pos.y = 0.0f;
			}

			if (player.pos.y + (player.size.y / 2.0f) > global::screenHeight && player.dir.y > 0.0f)
			{
				player.dir.y *= -speedMultiplier;
				player.pos.y = player.pos.y + (player.size.y / 2.0f);
			}
		}
	}
}