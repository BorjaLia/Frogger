#include "entity.h"

#include "globals.h"

namespace frogger
{
	namespace object
	{
		static void BordersUpdate();
		static void PathUpdate();
	}

	namespace object
	{
		std::vector<Entity> entities = {Entity()};

		static Entity& currentEntity = entities[0];

		void Init()
		{
			Reset();
		}

		void Update()
		{
			for (int d = 0; d < entities.size(); d++)
			{
				currentEntity = entities[d];

				switch (currentEntity.pathType)
				{
				case frogger::object::STATIC:
				{

					break;
				}
				case frogger::object::OPEN_PATH:
				{
					PathUpdate();
					break;
				}
				case frogger::object::CLOSED_PATH:
				{
					PathUpdate();
					BordersUpdate();
					break;
				}
				case frogger::object::FOLLOW:
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
			for (int d = 0; d < entities.size(); d++)
			{
				currentEntity = entities[d];

#ifdef _DEBUG
			sf::RectangleShape sizeShape({ currentEntity.size.x,currentEntity.size.y });
			sizeShape.setPosition(sf::Vector2f(currentEntity.pos.x - (currentEntity.size.x / 2.0f), currentEntity.pos.y - (currentEntity.size.y / 2.0f)));
			sizeShape.setFillColor(sf::Color::Red);
			global::window.draw(sizeShape);

			sf::RectangleShape collShape({ currentEntity.coll.x,currentEntity.coll.y });
			collShape.setPosition(sf::Vector2f(currentEntity.pos.x - (currentEntity.coll.x / 2.0f), currentEntity.pos.y - (currentEntity.coll.y / 2.0f)));
			collShape.setFillColor(sf::Color::Red);
			global::window.draw(collShape);

			float radius = 5.0f;
			sf::CircleShape center(radius);
			center.setPosition(sf::Vector2f(currentEntity.pos.x - (radius), currentEntity.pos.y - (radius)));
			center.setFillColor(sf::Color::Magenta);
			global::window.draw(center);
#endif // _DEBUG
			}
		}

		void Reset()
		{
			entities.clear();

			Entity water;
			water.pos = { global::screenWidth / 2.0f,global::screenHeight / 3.0f };
			water.size = { global::screenWidth,60.0f };
			water.coll = water.size;

			entities.push_back(water);

			if (!entities.empty())
			{
				currentEntity = entities[0];
			}
			else
			{

			}
		}

		static void BordersUpdate()
		{
			float speedMultiplier = 0.4f;

			if (currentEntity.pos.x < 0.0f && currentEntity.dir.x < 0.0f)
			{
				currentEntity.dir.x *= -speedMultiplier;
				currentEntity.pos.x = 0.0f;
			}

			if (currentEntity.pos.x + (currentEntity.size.x / 2.0f) > global::screenWidth && currentEntity.dir.x > 0.0f)
			{
				currentEntity.dir.x *= -speedMultiplier;
				currentEntity.pos.x = currentEntity.pos.x + (currentEntity.size.x / 2.0f);
			}

			if (currentEntity.pos.y < 0.0f && currentEntity.dir.y < 0.0f)
			{
				currentEntity.dir.y *= -speedMultiplier;
				currentEntity.pos.y = 0.0f;
			}

			if (currentEntity.pos.y + (currentEntity.size.y / 2.0f) > global::screenHeight && currentEntity.dir.y > 0.0f)
			{
				currentEntity.dir.y *= -speedMultiplier;
				currentEntity.pos.y = currentEntity.pos.y + (currentEntity.size.y / 2.0f);
			}
		}

		static void PathUpdate()
		{
		}
	}
}