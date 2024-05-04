#include "ENGINE.h"
#include <cstdlib>
#include <iostream>

ENGINE::ENGINE() {
	game_settings = new SETTINGS();
	sf::Image icon;
	icon.loadFromFile("Images/icon.png");
	game_window = new WINDOW(game_settings->get_game_heigth(), game_settings->get_game_width(), game_settings->get_game_name(), game_settings->get_game_freamrate());
	game_window->window_->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	game_figure = new FIGURE();
	game_text = new MESSAGE(sf::Vector2f(15, game_settings->get_game_heigth() - 24));

	for (int i = 0; i < 4; i++)
		tmp_figure.push_back(sf::Vector2i());
}

void ENGINE::init_map(std::vector<std::vector<int>>& draw_map) {
	for (int m = 0; m < draw_map.size(); m++) {
		for (int n = 0; n < draw_map[m].size(); n++) {
			game_window->window_->draw(game_figure->get_object(sf::Vector2f(m * game_settings->get_figure_cube_size_h(), n * game_settings->get_figure_cube_size_w()), draw_map[m][n]));
		}
	}
	for (int i = 0; i < 4; i++)
		game_window->window_->draw(game_figure->get_object(sf::Vector2f(tmp_figure[i].x * game_settings->get_figure_cube_size_w(), tmp_figure[i].y * game_settings->get_figure_cube_size_h()), tmp_figure_id));
}

bool ENGINE::isValid(int row, int col)
{
	return (row >= 0) && (row < game_settings->get_vrt_count()) && (col >= 0) && (col < game_settings->get_hrz_count());
}

void ENGINE::check_line_fill() {
	for (int r = 0; r < game_settings->get_hrz_count(); r++) {
		bool remove_line = true;
		for (int c = 0; c < game_settings->get_vrt_count(); c++) {
			if (game_settings->get_game_map()[c][r] == 0) {
				remove_line = false;
				break;
			}
		}
		if (remove_line)
			removed_lines.push_back(r);
		continue;
	}
}

void ENGINE::remove_lines() {
	for (auto& it : removed_lines) {
		for (int c = 0; c < game_settings->get_vrt_count(); c++) {
			game_settings->set_game_map(c, it, 0);
		}
		for (int r = it; r > 0; r--) {
			for (int c = 0; c < game_settings->get_vrt_count(); c++) {
				game_settings->set_game_map(c, r, game_settings->get_game_map()[c][r - 1]);
			}
		}
		broken_lines++;
		score += 50;
	}
	removed_lines.clear();
}

void ENGINE::decrement_tmp_x() {
	tmp_figure[0].x -= 1;
	tmp_figure[1].x -= 1;
	tmp_figure[2].x -= 1;
	tmp_figure[3].x -= 1;
}

void ENGINE::increment_tmp_x() {
	tmp_figure[0].x += 1;
	tmp_figure[1].x += 1;
	tmp_figure[2].x += 1;
	tmp_figure[3].x += 1;
}

void ENGINE::increment_tmp_y() {
	tmp_figure[0].y += 1;
	tmp_figure[1].y += 1;
	tmp_figure[2].y += 1;
	tmp_figure[3].y += 1;
}

void ENGINE::fix_tmp_figure() {
	game_settings->set_game_map(tmp_figure[0].x, tmp_figure[0].y, tmp_figure_id);
	game_settings->set_game_map(tmp_figure[1].x, tmp_figure[1].y, tmp_figure_id);
	game_settings->set_game_map(tmp_figure[2].x, tmp_figure[2].y, tmp_figure_id);
	game_settings->set_game_map(tmp_figure[3].x, tmp_figure[3].y, tmp_figure_id);
	generate_new_figure = true;
}

void ENGINE::next_step(int key) {
	if (generate_new_figure) {
		generate_new_figure = false;
		generate_figure();
		if (game_settings->get_game_map()[tmp_figure[0].x][tmp_figure[0].y] != 0 && game_settings->get_game_map()[tmp_figure[1].x][tmp_figure[1].y] != 0 && game_settings->get_game_map()[tmp_figure[2].x][tmp_figure[2].y] != 0 && game_settings->get_game_map()[tmp_figure[3].x][tmp_figure[3].y] != 0) {
			text_index = 2;
			game_started = false;
		}
	}
	switch (key)
	{
	case 1: //left
		switch (tmp_figure_id)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			if (isValid(tmp_figure[0].x - 1, tmp_figure[0].y) && isValid(tmp_figure[1].x - 1, tmp_figure[1].y) && isValid(tmp_figure[2].x - 1, tmp_figure[2].y) && isValid(tmp_figure[3].x - 1, tmp_figure[3].y))
				if (game_settings->get_game_map()[tmp_figure[0].x - 1][tmp_figure[0].y] == 0 && game_settings->get_game_map()[tmp_figure[1].x - 1][tmp_figure[1].y] == 0 && game_settings->get_game_map()[tmp_figure[2].x - 1][tmp_figure[2].y] == 0 && game_settings->get_game_map()[tmp_figure[3].x - 1][tmp_figure[3].y] == 0) {
					decrement_tmp_x();
				}
			break;
		default:
			break;
		}
		break;
	case 2: // right
		switch (tmp_figure_id)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			if (isValid(tmp_figure[0].x + 1, tmp_figure[0].y) && isValid(tmp_figure[1].x + 1, tmp_figure[1].y) && isValid(tmp_figure[2].x + 1, tmp_figure[2].y) && isValid(tmp_figure[3].x + 1, tmp_figure[3].y))
				if (game_settings->get_game_map()[tmp_figure[0].x + 1][tmp_figure[0].y] == 0 && game_settings->get_game_map()[tmp_figure[1].x + 1][tmp_figure[1].y] == 0 && game_settings->get_game_map()[tmp_figure[2].x + 1][tmp_figure[2].y] == 0 && game_settings->get_game_map()[tmp_figure[3].x + 1][tmp_figure[3].y] == 0) {
					increment_tmp_x();
				}
			break;
		default:
			break;
		}
		break;
	case 3: // down
		switch (tmp_figure_id)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			if (isValid(tmp_figure[0].x, tmp_figure[0].y + 1) && isValid(tmp_figure[1].x, tmp_figure[1].y + 1) && isValid(tmp_figure[2].x, tmp_figure[2].y + 1) && isValid(tmp_figure[3].x, tmp_figure[3].y + 1))
				if (game_settings->get_game_map()[tmp_figure[0].x][tmp_figure[0].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[1].x][tmp_figure[1].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[2].x][tmp_figure[2].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x][tmp_figure[3].y + 1] == 0) {
					increment_tmp_y();
					break;
				}
			fix_tmp_figure();
			next_step(1);
			break;
		default:
			break;
		}
		break;
	case 4: // up
		switch (tmp_figure_id)
		{
		case 1:
			if (figure_1_1 == 1) {
				if (isValid(tmp_figure[0].x + 2, tmp_figure[0].y - 1) && isValid(tmp_figure[2].x, tmp_figure[2].y + 1) && isValid(tmp_figure[3].x - 1, tmp_figure[3].y + 2)) {
					if (game_settings->get_game_map()[tmp_figure[0].x + 2][tmp_figure[0].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[2].x][tmp_figure[2].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x - 1][tmp_figure[3].y + 2] == 0) {
						tmp_figure[0].x += 2; tmp_figure[0].y -= 1;
						tmp_figure[1].x += 1; tmp_figure[1].y;
						tmp_figure[2].x;      tmp_figure[2].y += 1;
						tmp_figure[3].x -= 1; tmp_figure[3].y += 2;
						tmp_figure_id = 2;
						figure_1_1 = 3;
					}
				}
				break;
			}
			else if (figure_1_1 == 4) {
				if (isValid(tmp_figure[0].x + 1, tmp_figure[0].y - 2) && isValid(tmp_figure[1].x, tmp_figure[1].y - 1) && isValid(tmp_figure[3].x - 2, tmp_figure[3].y + 1)) {
					if (game_settings->get_game_map()[tmp_figure[0].x + 1][tmp_figure[0].y - 2] == 0 && game_settings->get_game_map()[tmp_figure[1].x][tmp_figure[1].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x - 2][tmp_figure[3].y + 1] == 0) {
						tmp_figure[0].x += 1; tmp_figure[0].y -= 2;
						tmp_figure[1].x;      tmp_figure[1].y -= 1;
						tmp_figure[2].x -= 1; tmp_figure[2].y;
						tmp_figure[3].x -= 2; tmp_figure[3].y += 1;
						tmp_figure_id = 2;
						figure_1_1 = 2;
					}
				}
				break;
			}
		case 2:
			if (figure_1_1 == 2) {
				if (isValid(tmp_figure[0].x - 1, tmp_figure[0].y + 1) && isValid(tmp_figure[2].x + 1, tmp_figure[2].y - 1) && isValid(tmp_figure[3].x + 2, tmp_figure[3].y - 2)) {
					if (game_settings->get_game_map()[tmp_figure[0].x - 1][tmp_figure[0].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[2].x + 1][tmp_figure[2].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x + 2][tmp_figure[3].y - 2] == 0) {
						tmp_figure[0].x -= 1; tmp_figure[0].y += 1;
						tmp_figure[2].x += 1; tmp_figure[2].y -= 1;
						tmp_figure[3].x += 2; tmp_figure[3].y -= 2;
						tmp_figure_id = 1;
						figure_1_1 = 1;
					}
				}
				break;
			}
			else if (figure_1_1 == 3) {
				if (isValid(tmp_figure[0].x - 2, tmp_figure[0].y + 2) && isValid(tmp_figure[1].x - 1, tmp_figure[1].y + 1) && isValid(tmp_figure[3].x + 1, tmp_figure[3].y - 1)) {
					if (game_settings->get_game_map()[tmp_figure[0].x - 2][tmp_figure[0].y + 2] == 0 && game_settings->get_game_map()[tmp_figure[1].x - 1][tmp_figure[1].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x + 1][tmp_figure[3].y - 1] == 0) {
						tmp_figure[0].x -= 2; tmp_figure[0].y += 2;
						tmp_figure[1].x -= 1; tmp_figure[1].y += 1;
						tmp_figure[3].x += 1; tmp_figure[3].y -= 1;
						tmp_figure_id = 1;
						figure_1_1 = 4;
					}
				}
				break;
			}
		case 4:
			if (isValid(tmp_figure[0].x - 1, tmp_figure[0].y - 1) && isValid(tmp_figure[1].x - 2, tmp_figure[1].y) && isValid(tmp_figure[2].x + 1, tmp_figure[2].y - 1)) {
				if (game_settings->get_game_map()[tmp_figure[0].x - 1][tmp_figure[0].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[1].x - 2][tmp_figure[1].y] == 0 && game_settings->get_game_map()[tmp_figure[2].x + 1][tmp_figure[2].y - 1] == 0) {
					tmp_figure[0].x -= 1; tmp_figure[0].y -= 1;
					tmp_figure[1].x -= 2; tmp_figure[1].y;
					tmp_figure[2].x += 1; tmp_figure[2].y -= 1;
					tmp_figure_id = 7;
				}
			}
			break;
		case 5:
			if (isValid(tmp_figure[0].x + 2, tmp_figure[0].y - 1) && isValid(tmp_figure[2].x + 1, tmp_figure[2].y - 1) && isValid(tmp_figure[3].x - 1, tmp_figure[3].y)) {
				if (game_settings->get_game_map()[tmp_figure[0].x + 2][tmp_figure[0].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[2].x + 1][tmp_figure[2].y - 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x - 1][tmp_figure[3].y] == 0) {
					tmp_figure[0].x += 2; tmp_figure[0].y -= 1;
					tmp_figure[2].x += 1; tmp_figure[2].y -= 1;
					tmp_figure[3].x -= 1; tmp_figure[3].y;
					tmp_figure_id = 6;
				}
			}
			break;
		case 6:
			if (isValid(tmp_figure[0].x - 2, tmp_figure[0].y + 1) && isValid(tmp_figure[2].x - 1, tmp_figure[2].y + 1) && isValid(tmp_figure[3].x + 1, tmp_figure[3].y)) {
				if (game_settings->get_game_map()[tmp_figure[0].x - 2][tmp_figure[0].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[2].x - 1][tmp_figure[2].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x + 1][tmp_figure[3].y] == 0) {
					tmp_figure[0].x -= 2; tmp_figure[0].y += 1;
					tmp_figure[2].x -= 1; tmp_figure[2].y += 1;
					tmp_figure[3].x += 1; tmp_figure[3].y;
					tmp_figure_id = 5;
				}
			}
			break;
		case 7:
			if (isValid(tmp_figure[0].x + 1, tmp_figure[0].y + 1) && isValid(tmp_figure[1].x + 2, tmp_figure[1].y) && isValid(tmp_figure[2].x - 1, tmp_figure[2].y + 1 && isValid(tmp_figure[3].x - 1, tmp_figure[3].y))) {
				if (game_settings->get_game_map()[tmp_figure[0].x + 1][tmp_figure[0].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[1].x + 2][tmp_figure[1].y] == 0 && game_settings->get_game_map()[tmp_figure[2].x - 1][tmp_figure[2].y + 1] == 0 && game_settings->get_game_map()[tmp_figure[3].x - 1][tmp_figure[3].y] == 0) {
					tmp_figure[0].x += 1; tmp_figure[0].y += 1;
					tmp_figure[1].x += 2; tmp_figure[1].y;
					tmp_figure[2].x -= 1; tmp_figure[2].y += 1;
					tmp_figure_id = 4;
				}
			}
			break;
		case 8:
			if (isValid(tmp_figure[3].x - 1, tmp_figure[3].y + 1)) {
				if (game_settings->get_game_map()[tmp_figure[1].x + 1][tmp_figure[1].y + 1] == 0) {
					tmp_figure[1].x += 1; tmp_figure[1].y;
					tmp_figure[2].x += 1; tmp_figure[2].y;
					tmp_figure[3].x -= 1; tmp_figure[3].y += 1;
					tmp_figure_id = 10;
				}
			}
			break;
		case 9:
			if (isValid(tmp_figure[0].x + 1, tmp_figure[0].y - 1)) {
				if (game_settings->get_game_map()[tmp_figure[0].x + 1][tmp_figure[0].y - 1] == 0) {
					tmp_figure[0].x += 1; tmp_figure[0].y -= 1;
					tmp_figure[1].x -= 1; tmp_figure[1].y;
					tmp_figure[2].x -= 1; tmp_figure[2].y;
					tmp_figure_id = 11;
				}
			}
			break;
		case 10:
			if (isValid(tmp_figure[0].x - 1, tmp_figure[0].y + 1)) {
				if (game_settings->get_game_map()[tmp_figure[0].x - 1][tmp_figure[0].y + 1] == 0) {
					tmp_figure[0].x -= 1; tmp_figure[0].y += 1;
					tmp_figure_id = 9;
				}
			}
			break;
		case 11:
			if (isValid(tmp_figure[3].x + 1, tmp_figure[3].y - 1)) {
				if (game_settings->get_game_map()[tmp_figure[0].x - 1][tmp_figure[0].y + 1] == 0) {
					tmp_figure[3].x += 1; tmp_figure[3].y -= 1;
					tmp_figure_id = 8;
				}
			}
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ENGINE::update_text() {
	std::string msg = "";
	switch (text_index) {
	case 0:
		game_text->set_text("Press N to start game");
		break;
	case 1:
		msg = "Lines ";
		msg += std::to_string(broken_lines);
		msg += "\t Score ";
		msg += std::to_string(score);
		game_text->set_text(msg);
		break;
	case 2:
		msg = "Game Over. Your score is ";
		msg += std::to_string(score);
		game_text->set_text(msg);
		break;
	case 3:
		break;
		{
	default:
		break;
		}
	}
}

void ENGINE::generate_figure() {
	srand((unsigned)time(NULL));
	tmp_figure_id = 1 + (rand() % 11);
	switch (tmp_figure_id)
	{
	case 1:
		// * * * *
		tmp_figure[0] = sf::Vector2i(3, 0);
		tmp_figure[1] = sf::Vector2i(4, 0);
		tmp_figure[2] = sf::Vector2i(5, 0);
		tmp_figure[3] = sf::Vector2i(6, 0);
		figure_1_1 = 1;
		break;
	case 2:
		// *
		// *
		// *
		// *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(4, 2);
		tmp_figure[3] = sf::Vector2i(4, 3);
		figure_1_1 = 2;
		break;
	case 3:
		// * *
		// * *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(4, 1);
		tmp_figure[3] = sf::Vector2i(5, 1);
		break;
	case 4:
		//   * *
		// * *
		tmp_figure[0] = sf::Vector2i(5, 0);
		tmp_figure[1] = sf::Vector2i(6, 0);
		tmp_figure[2] = sf::Vector2i(4, 1);
		tmp_figure[3] = sf::Vector2i(5, 1);
		break;
	case 5:
		// * *
		//   * *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(6, 1);
		break;
	case 6:
		//   *
		// * *
		// *
		tmp_figure[0] = sf::Vector2i(5, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(4, 2);
		break;
	case 7:
		// *
		// * *
		//   *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(5, 2);
		break;
	case 8:
		//   *
		// * * *
		tmp_figure[0] = sf::Vector2i(5, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(6, 1);
		break;
	case 9:
		// * * *
		//   *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(6, 0);
		tmp_figure[3] = sf::Vector2i(5, 1);
		break;
	case 10:
		// *
		// * *
		// *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(4, 2);
		break;
	case 11:
		//   *
		// * *
		//   *
		tmp_figure[0] = sf::Vector2i(5, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(5, 2);
		break;
	case 12:
		// * *
		//   *
		//   *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(5, 2);
		break;
	case 13:
		//     *
		// * * *
		tmp_figure[0] = sf::Vector2i(6, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(6, 1);
		break;
	case 14:
		// *
		// *
		// * *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 2);
		tmp_figure[3] = sf::Vector2i(6, 2);
		break;
	case 15:
		// * * *
		// *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(6, 0);
		tmp_figure[3] = sf::Vector2i(4, 1);
		break;
	case 16:
		// * * 
		// *
		// *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(4, 1);
		tmp_figure[3] = sf::Vector2i(4, 2);
		break;
	case 17:
		// * * *
		//     *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(5, 0);
		tmp_figure[2] = sf::Vector2i(6, 0);
		tmp_figure[3] = sf::Vector2i(6, 1);
		break;
	case 18:
		//   *
		//   *
		// * *
		tmp_figure[0] = sf::Vector2i(5, 0);
		tmp_figure[1] = sf::Vector2i(5, 1);
		tmp_figure[2] = sf::Vector2i(4, 2);
		tmp_figure[3] = sf::Vector2i(5, 2);
		break;
	case 19:
		// * 
		// * * *
		tmp_figure[0] = sf::Vector2i(4, 0);
		tmp_figure[1] = sf::Vector2i(4, 1);
		tmp_figure[2] = sf::Vector2i(5, 1);
		tmp_figure[3] = sf::Vector2i(6, 1);
		break;
	default:
		break;
	}
}

void ENGINE::start_game() {
	game_settings->reset();
	broken_lines = 0;
	score = 0;
	next_step(3);
}

void ENGINE::run_game() {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (game_window->window_->isOpen())
	{
		sf::Event event;
		while (game_window->window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game_window->window_->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (game_started) {
					if (event.key.code == sf::Keyboard::Left)
					{
						next_step(1);
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						next_step(2);
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						next_step(3);
						check_line_fill();
						remove_lines();
						score += 1;
					}
					if (event.key.code == sf::Keyboard::Up)
					{
						next_step(4);
					}
				}
				if (event.key.code == sf::Keyboard::N)
				{
					if (game_started) {

					}
					else {
						game_started = true;
						text_index = 1;
						start_game();
					}
				}
			}
		}

		game_window->window_->clear();
		init_map(game_settings->get_game_map());
		game_window->window_->draw(game_text->get_text());
		update_text();
		if (game_started) {
			if (clock.getElapsedTime().asMilliseconds() >= (500 - score / 100)) {
				next_step(3);
				check_line_fill();
				remove_lines();
				clock.restart();
			}
		}
		game_window->window_->display();
	}
}
