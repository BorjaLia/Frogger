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
		static label::Label programmerLabel;
		static label::Label programmerLabel2;
		static label::Label artistLabel;
		static label::Label artistLabel2;
		static label::Label artistLabel3;

		void Init()
		{
			defaultPos.y += 3.0f * (defaultSize.y * 1.5f);
			returnButton = button::Init(defaultPos, defaultSize, "Return");

			titleLabel = label::Init({defaultPos.x,global::screenHeight/15.0f},"Credits",25,sf::Color::Black);

			programmerLabel = label::Init({defaultPos.x,global::screenHeight/5.0f},"Programmer",20,sf::Color::Black);
			programmerLabel2 = label::Init({defaultPos.x - 10.0f,global::screenHeight/4.0f},"Borja Lia",30,sf::Color::Black);
			
			artistLabel = label::Init({defaultPos.x,global::screenHeight/2.0f},"Artists",20,sf::Color::Black);
			artistLabel2 = label::Init({defaultPos.x / 2.0f,global::screenHeight/1.8f},"Facundo Arrastua",30,sf::Color::Black);
			artistLabel3 = label::Init({defaultPos.x / 1.5f,global::screenHeight/1.7f},"Celeste Bassi",30,sf::Color::Black);
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

			label::Draw(programmerLabel,global::window);
			label::Draw(programmerLabel2,global::window);

			label::Draw(artistLabel,global::window);
			label::Draw(artistLabel2,global::window);
			label::Draw(artistLabel3,global::window);
		}
	}
}