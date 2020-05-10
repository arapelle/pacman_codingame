#include "game.hpp"
#include "action.hpp"
#include "turn_info.hpp"
#include "grid/grid_algo.hpp"

Game::Game(std::istream &input, std::ostream &output)
    : input_(input), output_(output), world_(*this), avatar_(*this), opponent_(*this)
{}

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

    update_from_turn_info_(turn_info);

    send_actions_();
}

void Game::update_from_turn_info_(const Turn_info& turn_info)
{
    world_.update_from_turn_info(turn_info);
    avatar_.update_from_turn_info(turn_info);
    opponent_.update_from_turn_info(turn_info);
}

void Game::send_actions_()
{
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // output_ << "MOVE 0 15 10" << std::endl; // MOVE <pacId> <x> <y>

    Action_sequence action_sequence;
    Position_set pset = find_all_positions_if(world_, &square_has_big_pellet);
    if (pset.size())
    {
        action_sequence.add_action<Move>(avatar_.pacmans().front(), *pset.begin());
    }
    else
    {
        auto iter = std::find_if(world_.begin(), world_.end(), &square_has_pellet);
        if (iter != world_.end())
            action_sequence.add_action<Move>(avatar_.pacmans().front(), iter.position());
    }
    output_ << action_sequence << std::endl;
}
