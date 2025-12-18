#include "button.h"

#include "globals.h"

namespace frogger
{
	namespace button
	{
		static bool IsMouseOnButton(sf::RenderWindow& window, Button& button);
	}

	namespace button
	{
		static sf::Color normalColor = sf::Color(235, 235, 235,164);
		static sf::Color hoverColor = sf::Color(200, 200, 200,164);
		static sf::Color pressedColor = sf::Color(164, 164, 164,164);

		Button Init(vec::Vector2 pos, vec::Vector2 size, std::string text)
		{
			Button button;
			button.pos = pos;
			button.size = size;
			button.text = text;
			button.state = State::Normal;
			button.clicked = false;

			return button;
		}

		static bool IsMouseOnButton(sf::RenderWindow& window, Button& button)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, window.getDefaultView());

			return (worldPos.x >= button.pos.x &&
				worldPos.x <= button.pos.x + button.size.x &&
				worldPos.y >= button.pos.y &&
				worldPos.y <= button.pos.y + button.size.y);
		}

		void Update(Button& button)
		{
			button.clicked = false;

			if (IsMouseOnButton(global::window, button))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					button.state = State::Pressed;
				}
				else
				{
					if (button.state == State::Pressed)
					{
						button.clicked = true;
					}
					button.state = State::Hover;
				}
			}
			else
			{
				button.state = State::Normal;
			}
		}

		void Draw(Button& button)
		{
			sf::RectangleShape rect;
			rect.setPosition({ button.pos.x, button.pos.y });
			rect.setSize(sf::Vector2f(button.size.x, button.size.y));

			switch (button.state)
			{
			case State::Normal:
				rect.setFillColor(normalColor);
				break;
			case State::Hover:
				rect.setFillColor(hoverColor);
				break;
			case State::Pressed:
				rect.setFillColor(pressedColor);
				break;
			}

			global::window.draw(rect);

			sf::Text textObj = { global::font, "Default", 20 };

			textObj.setString(button.text);
			textObj.setCharacterSize(20);

			textObj.setFillColor(sf::Color::White);

			sf::FloatRect textRect = textObj.getLocalBounds();

			textObj.setOrigin({ textRect.pos.x + textRect.size.x / 2.0f, textRect.size.y + textRect.pos.y / 2.0f });

			textObj.setPosition({ button.pos.x + button.size.x / 2.0f,button.pos.y + button.size.y / 2.0f + 9.5f });

			global::window.draw(textObj);
		}
	}
}