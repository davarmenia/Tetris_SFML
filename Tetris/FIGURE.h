#include "SFML/Graphics.hpp"
#pragma once
class FIGURE
{
public:
	FIGURE();
	sf::RectangleShape& get_object(sf::Vector2f position, int index);
private:
	sf::RectangleShape figure;
	sf::Texture texture;

	void init_texure();
};