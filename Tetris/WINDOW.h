#include <SFML/Graphics.hpp>

#pragma once
class WINDOW
{
public:
	WINDOW(int win_h, int win_w, std::string win_name, int fream_rate);
	sf::RenderWindow* window_;
private:

};

