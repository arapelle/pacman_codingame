#include "grid/exploration/spread_exploration.hpp"
#include "game/game.hpp"
#include <iostream>
#include <cstdlib>

//TODO command.hpp: class Command; class Command_vector : vector<unique_ptr<Command>>; string_to_commands(string) -> Command_vector

//TODO strategy multi

int main()
{
    Game game(std::cin, std::cout);
    game.init();

    game.play_start_actions();
    while (true)
        game.play_turn();

    return EXIT_SUCCESS;
}
