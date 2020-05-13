#include "test/spread_exploration/spread_exploration_tests.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "game/game.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc > 1 && std::string(argv[1]) == "test")
    {
        test::backward_test();
        test::forward_test();
        test::torus_backward_test();
        test::torus_forward_test();
        std::cerr << "EXIT SUCCESS" << std::endl;
    }
    else
    {
        Game game(std::cin, std::cout);
        game.init();

        game.play_start_actions();
        while (true)
            game.play_turn();
    }

    return EXIT_SUCCESS;
}
