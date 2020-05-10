#pragma once

#include <iostream>

class Game
{
public:
    Game(std::istream& input = std::cin, std::ostream& output = std::cout);

    // Start:
    void init();
    void play_start_actions();

    // Turn:
    void play_turn();

private:
    std::istream& input_;
    std::ostream& output_;
};
