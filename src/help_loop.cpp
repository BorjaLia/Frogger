#include "main_menu_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"

namespace frogger
{
	namespace help
	{
		static const vec::Vector2 defaultSize = { 200.0f,100.0f };
		static vec::Vector2 defaultPos = { (global::screenWidth / 2.0f) - defaultSize.x / 2.0f, (global::screenHeight / 2.0f) - defaultSize.y / 2.0f };

		static button::Button returnButton;

		void Init()
		{
			defaultPos.y += 3.0f * (defaultSize.y * 1.5f);
			returnButton = button::Init(defaultPos, defaultSize, "Return");
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
		}
	}
}