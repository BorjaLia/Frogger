#include "danger.h"

#include "globals.h"

namespace frogger
{
	namespace danger
	{
		static void BordersUpdate();
		static void PathUpdate();
	}

	namespace danger
	{
		std::vector<Danger> dangers = {Danger()};

		static Danger& currentDanger = dangers[0];

		void Init()
		{
			Reset();
		}

		void Update()
		{
			for (int d = 0; d < dangers.size(); d++)
			{
				currentDanger = dangers[d];

				switch (currentDanger.type)
				{
				case frogger::danger::STATIC:
				{

					break;
				}
				case frogger::danger::OPEN_PATH:
				{
					PathUpdate();
					break;
				}
				case frogger::danger::CLOSED_PATH:
				{
					PathUpdate();
					BordersUpdate();
					break;
				}
				case frogger::danger::FOLLOW:
				{
					PathUpdate();
					BordersUpdate();
					break;
				}
				default:
					break;
				}

			}
		}

		void Draw()
		{
			for (int d = 0; d < dangers.size(); d++)
			{
				currentDanger = dangers[d];

#ifdef _DEBUG
			sf::RectangleShape sizeShape({ currentDanger.size.x,currentDanger.size.y });
			sizeShape.setPosition(sf::Vector2f(currentDanger.pos.x - (currentDanger.size.x / 2.0f), currentDanger.pos.y - (currentDanger.size.y / 2.0f)));
			sizeShape.setFillColor(sf::Color::Red);
			global::window.draw(sizeShape);

			sf::RectangleShape collShape({ currentDanger.coll.x,currentDanger.coll.y });
			collShape.setPosition(sf::Vector2f(currentDanger.pos.x - (currentDanger.coll.x / 2.0f), currentDanger.pos.y - (currentDanger.coll.y / 2.0f)));
			collShape.setFillColor(sf::Color::Red);
			global::window.draw(collShape);

			float radius = 5.0f;
			sf::CircleShape center(radius);
			center.setPosition(sf::Vector2f(currentDanger.pos.x - (radius), currentDanger.pos.y - (radius)));
			center.setFillColor(sf::Color::Magenta);
			global::window.draw(center);
#endif // _DEBUG
			}
		}

		void Reset()
		{
			dangers.clear();

			Danger danger;
			danger.pos = { global::screenWidth / 2.0f,global::screenHeight / 3.0f };
			danger.size = { 30.0f,30.0f };
			danger.coll = danger.size;

			dangers.push_back(danger);

			if (!dangers.empty())
			{
				currentDanger = dangers[0];
			}
			else
			{

			}
		}

		static void BordersUpdate()
		{
			float speedMultiplier = 0.4f;

			if (currentDanger.pos.x < 0.0f && currentDanger.dir.x < 0.0f)
			{
				currentDanger.dir.x *= -speedMultiplier;
				currentDanger.pos.x = 0.0f;
			}

			if (currentDanger.pos.x + (currentDanger.size.x / 2.0f) > global::screenWidth && currentDanger.dir.x > 0.0f)
			{
				currentDanger.dir.x *= -speedMultiplier;
				currentDanger.pos.x = currentDanger.pos.x + (currentDanger.size.x / 2.0f);
			}

			if (currentDanger.pos.y < 0.0f && currentDanger.dir.y < 0.0f)
			{
				currentDanger.dir.y *= -speedMultiplier;
				currentDanger.pos.y = 0.0f;
			}

			if (currentDanger.pos.y + (currentDanger.size.y / 2.0f) > global::screenHeight && currentDanger.dir.y > 0.0f)
			{
				currentDanger.dir.y *= -speedMultiplier;
				currentDanger.pos.y = currentDanger.pos.y + (currentDanger.size.y / 2.0f);
			}
		}

		static void PathUpdate()
		{
		}
	}
}