//#include "test/spread_exploration/spread_exploration_tests.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "game/game.hpp"
#include <iostream>
#include <cstdlib>

int main()
{
    Game game(std::cin, std::cout);
    game.init();

    game.play_start_actions();
    while (true)
        game.play_turn();

    return EXIT_SUCCESS;
}
