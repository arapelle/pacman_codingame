#include "game.hpp"
#include "action.hpp"
#include "turn_info.hpp"
#include "grid/grid_algo.hpp"
#include "core/random.hpp"
#include "log/log.hpp"
#include <chrono>

Game::Game(std::istream &input, std::ostream &output)
    : input_(input), output_(output), world_(*this), avatar_(*this), opponent_(*this), turn_number_(Turn_info::first_turn_turn)
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
    Turn_info turn_info(turn_number_);
    turn_info.read_from_stream(input_);

    auto start_time = std::chrono::steady_clock::now();
    info() << "---------------------------------------------" << std::endl;
    info() << "TURN: " << turn_number_ << std::endl;

    update_from_turn_info_(turn_info);

    send_actions_();

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> turn_duration = end_time - start_time;
    info() << "Turn Duration: " << turn_duration.count() << "ms" << std::endl;
    ++turn_number_;
}

void Game::update_from_turn_info_(const Turn_info& turn_info)
{
    trace();
    // Update avatar,
    avatar_.update_from_turn_info(turn_info);
    // THEN update opponent.
    opponent_.update_from_turn_info(turn_info);
    // THEN update world.
    world_.update_from_turn_info(turn_info);
}

void Game::send_actions_()
{
    trace();
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // output_ << "MOVE 0 15 10" << std::endl; // MOVE <pacId> <x> <y>
//    avatar_.manage_pacmans();
    avatar_.manage_pacmans_2();

    Action_sequence action_sequence;
    for (const Pacman& pacman : avatar_.active_pacmans())
        if (Action_sptr action_sptr = pacman.action_todo(); action_sptr)
            action_sequence.add_action(std::move(action_sptr));
    output_ << action_sequence << std::endl;
}
