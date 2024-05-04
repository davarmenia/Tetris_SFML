#include "MESSAGE.h"

MESSAGE::MESSAGE(sf::Vector2f pos) {

	if (!font.loadFromFile("LED Dot-Matrix.ttf"))
	{
		// error...
	}
	text.setFont(font); // font is a sf::Font
	text.setString("Press N to start game");
	text.setCharacterSize(18); // in pixels, not points!
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(pos);
}

sf::Text& MESSAGE::get_text() {
	return text;
}

void MESSAGE::set_text(std::string new_text) {
	text.setString(new_text);
}