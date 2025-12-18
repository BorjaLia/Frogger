#include "main_menu_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"
#include "label.h"

namespace frogger
{
	namespace help
	{
		static const vec::Vector2 defaultSize = { 200.0f,100.0f };
		static vec::Vector2 defaultPos = { (global::screenWidth / 2.0f) - defaultSize.x / 2.0f, (global::screenHeight / 2.0f) - defaultSize.y / 2.0f };

		static button::Button returnButton;

		static label::Label titleLabel;
		static label::Label controlsLabel;
		static label::Label controlsLabel2;
		static label::Label controlsLabel3;

		static label::Label instructionsLabel;
		static label::Label instructionsLabel2;
		static label::Label instructionsLabel3;

		void Init()
		{
			defaultPos.y += 3.0f * (defaultSize.y * 1.5f);
			returnButton = button::Init(defaultPos, defaultSize, "Return");
		
			titleLabel = label::Init({ defaultPos.x,global::screenHeight / 15.0f }, "   How To", 25, sf::Color::Black);
		
			controlsLabel = label::Init({ defaultPos.x,global::screenHeight / 5.0f }, "Controls", 30, sf::Color::Black);
			controlsLabel2 = label::Init({ defaultPos.x,global::screenHeight / 4.0f }, "WASD or keys", 20, sf::Color::Black);
			controlsLabel3 = label::Init({ defaultPos.x,global::screenHeight / 3.6f }, "    to move", 20, sf::Color::Black);

			instructionsLabel = label::Init({ defaultPos.x,global::screenHeight / 2.0f }, "Gameplay", 30, sf::Color::Black);
			instructionsLabel2 = label::Init({ defaultPos.x,global::screenHeight / 1.8f }, "Get to the end!", 20, sf::Color::Black);
			instructionsLabel3 = label::Init({ defaultPos.x/1.5f,global::screenHeight / 1.7f }, "avoid the water and bees", 20, sf::Color::Black);
		}

		void Input()
		{
			button::Update(returnButton);
		}
		void Update()
		{
			if (returnButton.clicked)
			{
				scene::ChangeScene(scene::Scene::MAIN_MENU);
			}
		}
		void Draw()
		{
			button::Draw(returnButton);

			label::Draw(titleLabel,global::window);

			label::Draw(controlsLabel, global::window);
			label::Draw(controlsLabel2, global::window);
			label::Draw(controlsLabel3, global::window);

			label::Draw(instructionsLabel, global::window);
			label::Draw(instructionsLabel2, global::window);
			label::Draw(instructionsLabel3, global::window);
		}
	}
}