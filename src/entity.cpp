#include "entity.h"

#include "globals.h"

namespace frogger
{
	namespace object
	{
		static void Move();
		static void BordersUpdate();
		static void PathUpdate();
	}

	namespace object
	{
		std::vector<Entity> entities = { Entity() };

		static int currentEntity = 0;

		void Init()
		{
			Reset();
		}

		void Update()
		{
			for (currentEntity = 0; currentEntity < entities.size(); currentEntity++)
			{
				switch (entities[currentEntity].pathType)
				{
				case frogger::object::STATIC:
				{

					break;
				}
				case frogger::object::OPEN_PATH:
				{
					PathUpdate();
					Move();
					break;
				}
				case frogger::object::CLOSED_PATH:
				{
					PathUpdate();
					Move();
					BordersUpdate();
					break;
				}
				case frogger::object::FOLLOW:
				{
					PathUpdate();
					Move();
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
			for (currentEntity = 0; currentEntity < entities.size(); currentEntity++)
			{

#ifdef _DEBUG
				sf::Color color;

				if (entities[currentEntity].type == Type::DANGER)
				{
					color = sf::Color::Red;
				}
				else
				{
					color = sf::Color::Yellow;
				}

				sf::RectangleShape sizeShape({ entities[currentEntity].size.x,entities[currentEntity].size.y });
				sizeShape.setPosition(sf::Vector2f(entities[currentEntity].pos.x - (entities[currentEntity].size.x / 2.0f), entities[currentEntity].pos.y - (entities[currentEntity].size.y / 2.0f)));
				sizeShape.setFillColor(color);
				global::window.draw(sizeShape);

				sf::RectangleShape collShape({ entities[currentEntity].coll.x,entities[currentEntity].coll.y });
				collShape.setPosition(sf::Vector2f(entities[currentEntity].pos.x - (entities[currentEntity].coll.x / 2.0f), entities[currentEntity].pos.y - (entities[currentEntity].coll.y / 2.0f)));
				collShape.setFillColor(color);
				global::window.draw(collShape);

				float radius = 5.0f;
				sf::CircleShape center(radius);
				center.setPosition(sf::Vector2f(entities[currentEntity].pos.x - (radius), entities[currentEntity].pos.y - (radius)));
				center.setFillColor(sf::Color::Magenta);
				global::window.draw(center);
#endif // _DEBUG
			}
		}

		void Reset()
		{
			entities.clear();

			Entity water;
			water.type = Type::DANGER;
			water.pathType = PathType::STATIC;
			water.pos = { global::screenWidth / 2.0f,global::screenHeight / 3.0f };
			water.size = { global::screenWidth,60.0f };
			water.coll = water.size;
			entities.push_back(water);

			Entity log;
			log.type = Type::PLATFORM;
			log.pathType = PathType::OPEN_PATH;
			log.pos = { global::screenWidth / 2.0f,global::screenHeight / 3.0f };
			log.size = { 240.0f,60.0f };
			log.coll = log.size;

			log.path = { {global::screenWidth,global::screenHeight / 3.0f},{0.0f,global::screenHeight / 3.0f} };

			entities.push_back(log);
		}

		static void Move()
		{
			entities[currentEntity].pos += entities[currentEntity].dir;
		}

		static void BordersUpdate()
		{
			float speedMultiplier = 0.4f;

			if (entities[currentEntity].pos.x < 0.0f && entities[currentEntity].dir.x < 0.0f)
			{
				entities[currentEntity].dir.x *= -speedMultiplier;
				entities[currentEntity].pos.x = 0.0f;
			}

			if (entities[currentEntity].pos.x + (entities[currentEntity].size.x / 2.0f) > global::screenWidth && entities[currentEntity].dir.x > 0.0f)
			{
				entities[currentEntity].dir.x *= -speedMultiplier;
				entities[currentEntity].pos.x = entities[currentEntity].pos.x + (entities[currentEntity].size.x / 2.0f);
			}

			if (entities[currentEntity].pos.y < 0.0f && entities[currentEntity].dir.y < 0.0f)
			{
				entities[currentEntity].dir.y *= -speedMultiplier;
				entities[currentEntity].pos.y = 0.0f;
			}

			if (entities[currentEntity].pos.y + (entities[currentEntity].size.y / 2.0f) > global::screenHeight && entities[currentEntity].dir.y > 0.0f)
			{
				entities[currentEntity].dir.y *= -speedMultiplier;
				entities[currentEntity].pos.y = entities[currentEntity].pos.y + (entities[currentEntity].size.y / 2.0f);
			}
		}

		static void PathUpdate()
		{
		}
	}
}