#include "SFML/Graphics.hpp"
#pragma once
class MESSAGE
{
public:
	MESSAGE(sf::Vector2f pos);
	sf::Text& get_text();
	void set_text(std::string);

private:
	sf::Text text;
	sf::Font font;
};