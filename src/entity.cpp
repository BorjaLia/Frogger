#include "entity.h"

#include "globals.h"
#include "texture_manager.h"
#include "frog.h"

namespace frogger
{
	namespace object
	{
		static void Move();
		static void BordersUpdate();
		static void PathUpdate();
		static void SpriteUpdate();
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
				SpriteUpdate();
			}
		}

		void Draw()
		{
			for (currentEntity = 0; currentEntity < entities.size(); currentEntity++)
			{

				if (!entities[currentEntity].isAnimated)
				{
					entities[currentEntity].sprite.setOrigin(sf::Vector2f(entities[currentEntity].pos.x, entities[currentEntity].pos.y));
					global::window.draw(entities[currentEntity].sprite);
				}

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

			Entity waterT;
			waterT.type = Type::DANGER;
			waterT.pathType = PathType::STATIC;
			waterT.pos = { global::screenWidth / 2.0f,(global::screenHeight / 4.0f) - 60.0f };
			waterT.size = { global::screenWidth,40.0f };
			waterT.coll = waterT.size;

			waterT.sprite.setTexture(textures::entities::water, true);

			entities.push_back(waterT);

			Entity logT;
			logT.type = Type::PLATFORM;
			logT.pathType = PathType::OPEN_PATH;
			logT.pos = { global::screenWidth / 2.0f,(global::screenHeight / 4.0f) - 60.0f };
			logT.size = { 100.0f,100.0f };
			logT.coll = logT.size;

			logT.speed *= 6;

			logT.path = { {(global::screenWidth + logT.size.x),((global::screenHeight / 4.0f) - 60.0f)},{-logT.size.x,(global::screenHeight / 4.0f) - 60.0f} };
			logT.objective = 1;

			logT.sprite.setTexture(textures::entities::log, true);

			entities.push_back(logT);

			Entity waterM;
			waterM.type = Type::DANGER;
			waterM.pathType = PathType::STATIC;
			waterM.pos = { global::screenWidth / 2.0f,(global::screenHeight / 2.0f) - 60.0f };
			waterM.size = { global::screenWidth,40.0f };
			waterM.coll = waterM.size;

			waterM.sprite.setTexture(textures::entities::water, true);

			entities.push_back(waterM);

			Entity logM;
			logM.type = Type::PLATFORM;
			logM.pathType = PathType::OPEN_PATH;
			logM.pos = { global::screenWidth / 2.0f,(global::screenHeight / 2.0f) - 60.0f };
			logM.size = { 100.0f,100.0f };
			logM.coll = logM.size;

			logM.speed *= 4;

			logM.path = { {-logM.size.x,(global::screenHeight / 2.0f) - 60.0f},{(global::screenWidth + logM.size.x),(global::screenHeight / 2.0f) - 60.0f} };
			logM.objective = 1;

			logM.sprite.setTexture(textures::entities::log, true);

			entities.push_back(logM);

			Entity waterB;
			waterB.type = Type::DANGER;
			waterB.pathType = PathType::STATIC;
			waterB.pos = { global::screenWidth / 2.0f,(global::screenHeight * 0.75f) - 60.0f };
			waterB.size = { global::screenWidth,40.0f };
			waterB.coll = waterB.size;

			waterB.sprite.setTexture(textures::entities::water, true);

			entities.push_back(waterB);

			Entity logB;
			logB.type = Type::PLATFORM;
			logB.pathType = PathType::OPEN_PATH;
			logB.pos = { global::screenWidth / 2.0f,(global::screenHeight * 0.75f) - 60.0f };
			logB.size = { 100.0f,100.0f };
			logB.coll = logB.size;

			logB.speed *= 3;

			logB.path = { {(global::screenWidth + logB.size.x),(global::screenHeight * 0.75f) - 60.0f},{-logB.size.x,(global::screenHeight * 0.75f) - 60.0f} };
			logB.objective = 1;

			logB.sprite.setTexture(textures::entities::log, true);

			entities.push_back(logB);

			Entity bee;
			bee.type = Type::DANGER;
			bee.pathType = PathType::FOLLOW;
			bee.pos = { global::screenWidth / 2.0f,(global::screenHeight) + bee.size.y };
			bee.size = { 30.0f,30.0f };
			bee.coll = bee.size;

			bee.speed *= 1.1f;

			bee.sprite.setTexture(textures::entities::bee, true);

			entities.push_back(bee);
		}

		static void Move()
		{
			entities[currentEntity].pos += entities[currentEntity].dir * entities[currentEntity].speed * global::deltaTime;
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
			switch (entities[currentEntity].pathType)
			{
			case frogger::object::STATIC:
			{
				break;
			}
			case frogger::object::OPEN_PATH:
			{
				entities[currentEntity].dir = (entities[currentEntity].path[entities[currentEntity].objective] - entities[currentEntity].pos).normalized();

				if ((entities[currentEntity].pos - entities[currentEntity].path[entities[currentEntity].objective]).magnitude() <= entities[currentEntity].speed * global::deltaTime)
				{
					entities[currentEntity].objective = 0;
					entities[currentEntity].pos = entities[currentEntity].path[entities[currentEntity].objective];
					entities[currentEntity].objective++;
				}
				break;
			}
			case frogger::object::CLOSED_PATH:
			{
				break;
			}
			case frogger::object::FOLLOW:
			{
				entities[currentEntity].dir = (frog::player.pos - entities[currentEntity].pos).normalized();
				break;
			}
			default:
				break;
			}
		}

		static void SpriteUpdate()
		{
			entities[currentEntity].sprite.setPosition(sf::Vector2f(entities[currentEntity].pos.x - entities[currentEntity].size.x / 2.0f, entities[currentEntity].pos.y - entities[currentEntity].size.y / 2.0f));
			entities[currentEntity].sprite.setScale(sf::Vector2f(entities[currentEntity].size.x / entities[currentEntity].sprite.getTexture().getSize().x, entities[currentEntity].size.y / entities[currentEntity].sprite.getTexture().getSize().y));
		}
	}
}