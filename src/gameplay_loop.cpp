#include "gameplay_loop.h"

#include "globals.h"
#include "scene_manager.h"
#include "button.h"
#include "frog.h"
#include "danger.h"

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

		static bool CheckCollision(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2);
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
			danger::Init();

			pauseButton = button::Init({ (global::screenWidth / 2.0f) - defaultSize.y / 2.0f ,0.0f }, { defaultSize.y,defaultSize.y }, "||");
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
			danger::Reset();
			isPaused = false;
		}

		static void NormalInput()
		{
			frog::Input();

			button::Update(pauseButton);
		}

		static void PauseInput()
		{
			if (frog::player.isAlive)
			{
				button::Update(resumeButton);
			}
			button::Update(retryButton);
			button::Update(menuButton);
		}

		static void NormalUpdate()
		{
			if (!frog::player.isAlive)
			{
				isPaused = true;
				resumeButton.clicked = false;
			}

			frog::Update();
			danger::Update();

			if (pauseButton.clicked)
			{
				isPaused = true;
				resumeButton.clicked = false;
			}

			for (int d = 0; d < danger::dangers.size(); d++)
			{
				if (CheckCollision(frog::player.pos, frog::player.coll, danger::dangers[d].pos, danger::dangers[d].coll))
				{
					frog::TakeHit();
				}
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
			danger::Draw();
			frog::Draw();
			button::Draw(pauseButton);
		}

		static void PauseDraw()
		{
			NormalDraw();

			sf::RectangleShape shade({ global::screenWidth,global::screenHeight });
			shade.setFillColor(sf::Color(128,128,128,128));
			global::window.draw(shade);

			if (frog::player.isAlive)
			{
				button::Draw(resumeButton);
			}
			button::Draw(retryButton);
			button::Draw(menuButton);
		}

		static bool CheckCollision(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2)
		{
			vec::Vector2 half1 = { size1.x * 0.5f, size1.y * 0.5f };
			vec::Vector2 half2 = { size2.x * 0.5f, size2.y * 0.5f };

			float left1 = pos1.x - half1.x;
			float right1 = pos1.x + half1.x;
			float top1 = pos1.y - half1.y;
			float bottom1 = pos1.y + half1.y;

			float left2 = pos2.x - half2.x;
			float right2 = pos2.x + half2.x;
			float top2 = pos2.y - half2.y;
			float bottom2 = pos2.y + half2.y;

			float overlapLeft = mth::Max(left1, left2);
			float overlapRight = mth::Min(right1, right2);
			float overlapTop = mth::Max(top1, top2);
			float overlapBottom = mth::Min(bottom1, bottom2);

			if (overlapLeft >= overlapRight || overlapTop >= overlapBottom)
			{
				return false;
			}

			return true;
		}
	}
}