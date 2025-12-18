#include "main_menu_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"
#include "label.h"

namespace frogger
{
	namespace main_menu
	{
		static const vec::Vector2 defaultSize = { 200.0f,100.0f };
		static vec::Vector2 defaultPos = { (global::screenWidth / 2.0f) - defaultSize.x / 2.0f, (global::screenHeight / 2.0f) - defaultSize.y / 2.0f };

		static button::Button playButton;
		static button::Button creditsButton;
		static button::Button instructionsButton;
		static button::Button exitButton;

		static label::Label mainTitleLabel;
		static label::Label versionLabel;

		void Init()
		{
			playButton = button::Init(defaultPos, defaultSize, "Play");
			defaultPos.y += defaultSize.y * 1.5f;
			creditsButton = button::Init(defaultPos, defaultSize, "Credits");
			defaultPos.y += defaultSize.y * 1.5f;
			instructionsButton = button::Init(defaultPos, defaultSize, "Help");
			defaultPos.y += defaultSize.y * 1.5f;
			exitButton = button::Init(defaultPos, defaultSize, "Exit");

			mainTitleLabel = label::Init({ global::screenWidth / 8.0f,global::screenWidth / 4.0f }, "Frogger!", 80, sf::Color::Black);
			versionLabel = label::Init({ 10.0f,global::screenHeight - 30.0f }, "v1.0", 20, sf::Color(128, 128, 128));
		}

		void Input()
		{
			button::Update(playButton);
			button::Update(creditsButton);
			button::Update(instructionsButton);
			button::Update(exitButton);
		}
		void Update()
		{
			if (playButton.clicked)
			{
				scene::ChangeScene(scene::Scene::GAMEPLAY);
			}
			else if (creditsButton.clicked)
			{
				scene::ChangeScene(scene::Scene::CREDITS);
			}
			else if (instructionsButton.clicked)
			{
				scene::ChangeScene(scene::Scene::HELP);
			}
			else if (exitButton.clicked)
			{
				global::isRunning = false;
			}
		}
		void Draw()
		{
			button::Draw(playButton);
			button::Draw(creditsButton);
			button::Draw(instructionsButton);
			button::Draw(exitButton);

			label::Draw(mainTitleLabel, global::window);
			label::Draw(versionLabel, global::window);
		}
	}
}