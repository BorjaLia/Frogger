#include "frog.h"

#include "globals.h"

#include <iostream>

namespace frogger
{
	namespace frog
	{
		static void PrepareJump(vec::Vector2 dir, bool& preparingJump);
		static void JumpUpdate();
		static void BordersUpdate();
		static void SpriteUpdate();
	}

	namespace frog
	{
		namespace defaults
		{
			const bool isAlive = true;

			const bool onPlatform = false;

			const vec::Vector2 size = { 75.0f,75.0f };

			const vec::Vector2 pos = { (global::screenWidth / 2.0f),(global::screenHeight * 0.85f) };
			const vec::Vector2 dir = { 0.0f,0.0f };

			const float jumpForceMultiplier = 1500.0f;
			const float jumpForce = 0.0f;
			const float maxJumpForce = 1400.0f;
			const float deceleraton = 6000.0f;

			const vec::Vector2 coll = { size.x * 0.8f,size.y * 0.8f };

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
			player.idleSprite.setTexture(textures::entities::frogIdle, true);
			player.jumpSprite.setTexture(textures::entities::frogJump, true);

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
					PrepareJump(vec::Vector2(0.0f, -1.0f), preparingJump);
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.leftKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.leftKey[k]))
					{
						PrepareJump(vec::Vector2(-1.0f, 0.0f), preparingJump);
					}
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.dowKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.dowKey[k]))
					{
						PrepareJump(vec::Vector2(0.0f, 1.0f), preparingJump);
					}
				}
			}

			if (!preparingJump)
			{
				for (int k = 0; k < player.rightKey.size(); k++)
				{
					if (sf::Keyboard::isKeyPressed(player.rightKey[k]))
					{
						PrepareJump(vec::Vector2(1.0f, 0.0f), preparingJump);
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
				SpriteUpdate();
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

			if (!player.isJumping)
			{
				global::window.draw(player.idleSprite);
			}
			else
			{
				global::window.draw(player.jumpSprite);
			}
		}

		void Reset()
		{
			player.isAlive = defaults::isAlive;

			player.onPlatform = defaults::onPlatform;

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

		void Move(vec::Vector2 dir)
		{
			player.pos += dir * global::deltaTime;
		}

		void TakeHit()
		{
			player.isAlive = false;
		}

		static void PrepareJump(vec::Vector2 dir, bool& preparingJump)
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

			if (player.pos.x < player.size.x / 2.0f)
			{
				player.pos.x = player.size.x / 2.0f;
				if (player.dir.x < 0.0f)
				{
					player.dir.x *= -speedMultiplier;
				}
			}

			if (player.pos.x + (player.size.x / 2.0f) > global::screenWidth)
			{
				player.pos.x = global::screenWidth - (player.size.x / 2.0f);
				if (player.dir.x > 0.0f)
				{
					player.dir.x *= -speedMultiplier;
				}
			}

			if (player.pos.y < player.size.y / 2.0f)
			{
				player.pos.y = player.size.y / 2.0f;
				if (player.dir.y < 0.0f)
				{
					player.dir.y *= -speedMultiplier;
				}
			}

			if (player.pos.y + (player.size.y / 2.0f) > global::screenHeight)
			{
				player.pos.y = global::screenWidth - (player.size.y / 2.0f);

				if (player.dir.y > 0.0f)
				{
					player.dir.y *= -speedMultiplier;
				}
			}
		}
		static void SpriteUpdate()
		{

			float angleRad = std::atan2(player.dir.y, player.dir.x);

			if (player.dir.x != 0.0f || player.dir.y != 0.0f)
			{
				player.idleSprite.setRotation(sf::radians(angleRad) + sf::degrees(90.f));
			}

			player.idleSprite.setOrigin(sf::Vector2f(static_cast<float>(player.idleSprite.getTexture().getSize().x) / 2.0f, static_cast<float>(player.idleSprite.getTexture().getSize().y) / 2.0f));

			player.idleSprite.setScale(sf::Vector2f(player.size.x / player.idleSprite.getTexture().getSize().x, player.size.y / player.idleSprite.getTexture().getSize().y));
			player.idleSprite.setPosition(sf::Vector2f(player.pos.x, player.pos.y));
			
			player.jumpSprite.setRotation(player.idleSprite.getRotation());

			player.jumpSprite.setOrigin(player.idleSprite.getOrigin());

			player.jumpSprite.setPosition(player.idleSprite.getPosition());
			player.jumpSprite.setScale(player.idleSprite.getScale());
		}
	}
}