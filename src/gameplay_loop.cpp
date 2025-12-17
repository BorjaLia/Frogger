#include "gameplay_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"
#include "frog.h"

namespace frogger
{
	namespace gameplay
	{
		static bool isPaused = false;

		static void NormalInput();
		static void PauseInput();
		static void NormalUpdate();
		static void PauseUpdate();
		static void NormalDraw();
		static void PauseDraw();
	}

	namespace gameplay
	{
		static const vec::Vector2 defaultSize = { 200.0f,100.0f };
		static vec::Vector2 defaultPos = { (global::screenWidth / 2.0f) - defaultSize.x / 2.0f, (global::screenHeight / 2.0f) - defaultSize.y / 2.0f };

		static button::Button pauseButton;
		static button::Button resumeButton;
		static button::Button retryButton;
		static button::Button menuButton;

		void Init()
		{
			frog::Init();

			pauseButton = button::Init({ (global::screenWidth / 2.0f) - defaultSize.y / 2.0f ,0.0f}, { defaultSize.y,defaultSize.y }, "||");
			defaultPos.y += defaultSize.y * 1.5f;
			resumeButton = button::Init(defaultPos, defaultSize, "Resume");
			defaultPos.y += defaultSize.y * 1.5f;
			retryButton = button::Init(defaultPos, defaultSize, "Retry");
			defaultPos.y += defaultSize.y * 1.5f;
			menuButton = button::Init(defaultPos, defaultSize, "Menu");

			Reset();
		}

		void Input()
		{
			if (!isPaused)
			{
				NormalInput();
			}
			else
			{
				PauseInput();
			}
		}
		void Update()
		{
			if (!isPaused)
			{
				NormalUpdate();
			}
			else
			{
				PauseUpdate();
			}
		}
		void Draw()
		{
			if (!isPaused)
			{
				NormalDraw();
			}
			else
			{
				PauseDraw();
			}
		}

		void Reset()
		{
			frog::Reset();
			isPaused = false;
		}

		static void NormalInput()
		{
			frog::Input();

			button::Update(pauseButton);
		}

		static void PauseInput()
		{
			button::Update(resumeButton);
			button::Update(retryButton);
			button::Update(menuButton);
		}

		static void NormalUpdate()
		{
			frog::Update();

			if (pauseButton.clicked)
			{
				isPaused = true;
			}
		}

		static void PauseUpdate()
		{
			if (resumeButton.clicked)
			{
				isPaused = false;
			}
			else if (retryButton.clicked)
			{
				Reset();
			}
			else if (menuButton.clicked)
			{
				scene::ChangeScene(scene::Scene::MAIN_MENU);
			}
		}

		static void NormalDraw()
		{
			frog::Draw();
			button::Draw(pauseButton);
		}

		static void PauseDraw()
		{
			button::Draw(resumeButton);
			button::Draw(retryButton);
			button::Draw(menuButton);
		}
	}
}