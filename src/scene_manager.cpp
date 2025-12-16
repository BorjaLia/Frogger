#include "scene_manager.h"

namespace frogger
{
	namespace scene
	{
		
		Scene currentScene = Scene::MAIN_MENU;

		void ChangeScene(Scene newScene)
		{
			currentScene = newScene;
		}
	}
}