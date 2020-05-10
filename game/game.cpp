#include "game.hpp"
#include "turn_info.hpp"

Game::Game(std::istream &input, std::ostream &output)
    : input_(input), output_(output)
{
}

// Start:
void Game::init()
{
    world_.read_from_stream(input_);
}

void Game::play_start_actions()
{
}

// Turn:
void Game::play_turn()
{
    Turn_info turn_info;
    turn_info.read_from_stream(input_);

    update_data_(turn_info);

    send_actions_();
}

void Game::update_data_(const Turn_info& /*turn_info*/)
{
//    turn_info;
}

void Game::send_actions_()
{
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    output_ << "MOVE 0 15 10" << std::endl; // MOVE <pacId> <x> <y>
}
