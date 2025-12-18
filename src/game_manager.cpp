#include "game_manager.h"

#include "SFML/Graphics.hpp"

#include "globals.h"
#include "label.h"
#include "scene_manager.h"
#include "main_menu_loop.h"
#include "credit_loop.h"
#include "help_loop.h"
#include "gameplay_loop.h"

#include <iostream>

#include "texture_manager.h"

namespace frogger
{
	static sf::Sprite menuBackground{ textures::temp };
	static label::Label mainTitleLabel;

	static void MainLoop();

	static void Init();

	static void	Input();
	static void Update();
	static void Draw();
}

namespace frogger
{
	void PlayGame()
	{
		MainLoop();
	}

	static void MainLoop()
	{
		Init();

		while (global::window.isOpen())
		{
			if (!global::isRunning)
			{
				global::window.close();
			}
			while (const std::optional event = global::window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					global::window.close();
				}
			}
			Input();
			Update();
			Draw();
		}
	}

	static void Init()
	{
		textures::Init();

		menuBackground.setTexture(textures::backgrounds::menuBackground, true);
		mainTitleLabel = label::Init({global::screenWidth/8.0f,global::screenWidth / 4.0f},"Frogger!",80,sf::Color::Black);

		main_menu::Init();
		credits::Init();
		help::Init();
		gameplay::Init();
	}

	static void Input()
	{
		switch (scene::currentScene)
		{
		case scene::Scene::MAIN_MENU:
		{
			main_menu::Input();
			break;
		}
		case scene::Scene::CREDITS:
		{
			credits::Input();
			break;
		}
		case scene::Scene::HELP:
		{
			help::Input();
			break;
		}
		case scene::Scene::GAMEPLAY:
		{
			gameplay::Input();
			break;
		}
		default:
		{

			break;
		}
		}
	}
	static void Update()
	{
		global::Update();

		switch (scene::currentScene)
		{
		case scene::Scene::MAIN_MENU:
		{
			main_menu::Update();
			if (scene::currentScene == scene::Scene::GAMEPLAY)
			{
				gameplay::Reset();
			}
			break;
		}
		case scene::Scene::CREDITS:
		{
			credits::Update();
			break;
		}
		case scene::Scene::HELP:
		{
			help::Update();
			break;
		}
		case scene::Scene::GAMEPLAY:
		{
			gameplay::Update();
			break;
		}
		default:
		{

			break;
		}
		}
	}
	static void Draw()
	{
		global::window.clear(sf::Color(255, 255, 255));

		global::window.draw(menuBackground);
		label::Draw(mainTitleLabel,global::window);

		switch (scene::currentScene)
		{
		case scene::Scene::MAIN_MENU:
		{
			main_menu::Draw();
			break;
		}
		case scene::Scene::CREDITS:
		{
			credits::Draw();
			break;
		}
		case scene::Scene::HELP:
		{
			help::Draw();
			break;
		}
		case scene::Scene::GAMEPLAY:
		{
			gameplay::Draw();
			break;
		}
		default:
		{

			break;
		}
		}
		global::window.display();
	}
}