#pragma once

namespace frogger
{
	namespace scene
	{
		enum class Scene
		{
			MAIN_MENU,
			CREDITS,
			HELP,
			GAMEPLAY
		};

		extern Scene currentScene;

		void ChangeScene(Scene newScene);
	}
}