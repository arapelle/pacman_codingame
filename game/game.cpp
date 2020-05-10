#include "game.hpp"
#include "action.hpp"
#include "turn_info.hpp"
#include "grid/grid_algo.hpp"
#include "core/random.hpp"
#include "log/log.hpp"
#include <chrono>

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

    auto start_time = std::chrono::steady_clock::now();
    info() << "---------------------------------------------" << std::endl;

    update_from_turn_info_(turn_info);

    send_actions_();

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> turn_duration = end_time - start_time;
    info() << "Turn Duration: " << turn_duration.count() << "ms" << std::endl;
}

void Game::update_from_turn_info_(const Turn_info& turn_info)
{
    world_.update_from_turn_info(turn_info);
    avatar_.update_from_turn_info(turn_info);
    opponent_.update_from_turn_info(turn_info);
}

void Game::send_actions_()
{
    Action_sequence action_sequence;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // output_ << "MOVE 0 15 10" << std::endl; // MOVE <pacId> <x> <y>

    info() << "go to big!" << std::endl;

    Position_set pos_set = find_all_positions_if(world_, &square_has_big_pellet);
    unsigned number_of_moves_to_big_pellet = std::min<unsigned>(avatar_.pacmans().size(), pos_set.size());
    auto pacman_iter = avatar_.pacmans().begin();
    auto pos_iter = pos_set.begin();

    for (auto pacman_end_iter = std::next(pacman_iter, number_of_moves_to_big_pellet);
         pacman_iter != pacman_end_iter;
         ++pacman_iter, ++pos_iter)
    {
        action_sequence.add_action<Move>(*pacman_iter, *pos_iter);
    }

    info() << "go to small!" << std::endl;

    info() << "find_all_if(world_, &square_has_pellet)" << std::endl;
    auto viter = find_all_if(world_, &square_has_pellet);
    std::shuffle(viter.begin(), viter.end(), rand_int_engine());
    info() << "start loop" << std::endl;
    auto sqiter_iter = viter.begin();
    for (auto pacman_end_iter = avatar_.pacmans().end();
         pacman_iter != pacman_end_iter;
         ++pacman_iter, ++sqiter_iter)
    {
        info() << pacman_iter->id() << ",";
        if (sqiter_iter != viter.end())
            action_sequence.add_action<Move>(*pacman_iter, sqiter_iter->position());
    }
    info() << "\nend loop" << std::endl;

    output_ << action_sequence << std::endl;
}
