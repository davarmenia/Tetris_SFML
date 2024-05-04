#include "SETTINGS.h"
#include "WINDOW.h"
#include "FIGURE.h"
#include "MESSAGE.h"
#pragma once
class ENGINE
{
public:
	ENGINE();
	void run_game();

	sf::RenderWindow* get_window() { return game_window->window_; }
private:

	void start_game();
	void generate_figure();
	void next_step(int key);
	void increment_tmp_x();
	void decrement_tmp_x();
	void increment_tmp_y();
	void fix_tmp_figure();

	void check_line_fill();
	void remove_lines();
	void update_text();

	SETTINGS* game_settings;
	WINDOW* game_window;
	FIGURE* game_figure;
	MESSAGE* game_text;


	sf::Clock clock;
	int broken_lines = 0;
	int score = 0;
	void init_map(std::vector<std::vector<int>>& draw_map);
	void init_new_figure();
	std::vector<sf::Vector2i> tmp_figure;
	std::vector<int> removed_lines;

	int tmp_figure_id = 0;

	bool isValid(int row, int col);
	bool generate_new_figure = true;
	int figure_1_1 = 1;
	bool game_started = false;
	int text_index = 0;
};

