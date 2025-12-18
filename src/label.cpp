#include "label.h"

#include "globals.h"

namespace frogger
{
	namespace label
	{
		Label Init(vec::Vector2 pos, std::string text, int fontSize, sf::Color color)
		{
			Label label;

			label.pos = pos;
			label.text = text;
			label.fontSize = fontSize;
			label.color = sf::Color(static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), static_cast<uint8_t>(color.a));

			return label;
		}

		Label Init(vec::Vector2 pos, char text, int fontSize, sf::Color color)
		{
			Label label;

			label.pos = pos;
			label.text = text;
			label.fontSize = fontSize;
			label.color = sf::Color(static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), static_cast<uint8_t>(color.a));

			return label;
		}

		void Draw(Label& label, sf::RenderWindow& window)
		{
			sf::Text text = sf::Text(global::font);

			text.setString(label.text.c_str());

			sf::Vector2 textPos = sf::Vector2(0.f, 0.f);

			textPos.x = label.pos.x;
			textPos.y = label.pos.y;

			text.setPosition(textPos);
			text.setCharacterSize(label.fontSize);
			text.setFillColor(sf::Color(label.color));
			text.setStyle(sf::Text::Bold);

			window.draw(text);
		}
	}
}