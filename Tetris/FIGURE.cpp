#include "FIGURE.h"

#include <windows.h>
#include <string>

FIGURE::FIGURE() {
	figure.setSize(sf::Vector2f(40, 40));
	figure.setPosition(sf::Vector2f(10, 10));

	init_texure();
	figure.setTexture(&texture);
	figure.setTextureRect(sf::IntRect(0 * 50, 0, 50, 50));
}

sf::RectangleShape& FIGURE::get_object(sf::Vector2f position, int index) {
	figure.setPosition(position);
	figure.setTextureRect(sf::IntRect(index * 50, 0, 50, 50));
	return figure;
}


void FIGURE::init_texure() {
	if (!texture.loadFromFile("Images/blocks.png"))
	{
		// error...
	}
	return;
}