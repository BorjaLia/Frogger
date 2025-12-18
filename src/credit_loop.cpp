#include "main_menu_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"
#include "label.h"

namespace frogger
{
	namespace credits
	{
		static const vec::Vector2 defaultSize = { 200.0f,100.0f };
		static vec::Vector2 defaultPos = { (global::screenWidth / 2.0f) - defaultSize.x / 2.0f, (global::screenHeight / 2.0f) - defaultSize.y / 2.0f };

		static button::Button returnButton;
		static label::Label titleLabel;
		static label::Label creditsLabel;
		static label::Label programmerLabel;

		void Init()
		{
			defaultPos.y += 3.0f * (defaultSize.y * 1.5f);
			returnButton = button::Init(defaultPos, defaultSize, "Return");

			titleLabel = label::Init({defaultPos.x,global::screenHeight/15.0f},"Credits",25,sf::Color::Black);
			creditsLabel = label::Init({defaultPos.x,global::screenHeight/5.0f},"Made by",15,sf::Color::Black);
			programmerLabel = label::Init({defaultPos.x,global::screenHeight/4.0f},"Borja Lia",30,sf::Color::Black);
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
			label::Draw(creditsLabel,global::window);
			label::Draw(programmerLabel,global::window);
			label::Draw(titleLabel,global::window);
		}
	}
}