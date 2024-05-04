#include "ENGINE.h"

int main()
{
    ENGINE Game_engine;
    sf::RenderWindow* window = Game_engine.get_window();

    Game_engine.run_game();



    return 0;
}