#pragma once

#include "world.hpp"
#include <iostream>

class Turn_info;

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
    void update_data_(const Turn_info& turn_info);
    void send_actions_();

private:
    std::istream& input_;
    std::ostream& output_;
    World world_;
};
