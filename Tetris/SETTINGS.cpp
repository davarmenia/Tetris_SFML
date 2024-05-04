#include "SETTINGS.h"

SETTINGS::SETTINGS() {
	game_name = "Tetris game by DavArmenia";
	game_heigth = 825;
	game_width = 400;
	init_game_array();
}

void SETTINGS::init_game_array() {
	game_array.clear();
	for (int m = 0; m < vertical_count; m++) {
		std::vector<int> tmp;
		for (int n = 0; n < horizonical_count; n++) {
			tmp.push_back(0);
		}
		game_array.push_back(tmp);
	}
}