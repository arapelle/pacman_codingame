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
    Action_sequence action_sequence;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // output_ << "MOVE 0 15 10" << std::endl; // MOVE <pacId> <x> <y>

    for (const Pacman& pacman : avatar_.active_pacmans())
        if (pacman.is_ability_available())
            action_sequence.add_action<Speed>(pacman) << pacman.destination();
    if (action_sequence.actions().size() > 0)
    {
        output_ << action_sequence << std::endl;
        return;
    }

    debug() << "go to big!" << std::endl;

    Position_set pos_set = find_all_positions_if(world_, &square_has_big_pellet);
    unsigned number_of_moves_to_big_pellet = std::min<unsigned>(avatar_.active_pacmans().size(), pos_set.size());
    auto pacman_iter = avatar_.active_pacmans().begin();
    auto pos_iter = pos_set.begin();

    for (auto pacman_end_iter = std::next(pacman_iter, number_of_moves_to_big_pellet);
         pacman_iter != pacman_end_iter;
         ++pacman_iter)
    {
        Pacman& pacman = *pacman_iter;
        if (!pacman.has_destination())
        {
            pacman.set_destination(*pos_iter);
            ++pos_iter;
        }
        assert(pacman.has_destination());
        action_sequence.add_action<Move>(pacman, pacman.destination()) << pacman.destination();
    }

    debug() << "go to small!" << std::endl;

//    debug() << "find_all_if()" << std::endl;
    auto viter = find_all_if(world_, &square_has_pellet);
//    debug() << "shuffle()" << std::endl;
    std::shuffle(viter.begin(), viter.end(), rand_int_engine());
    auto sqiter_iter = viter.begin();
//    debug() << "start loop" << std::endl;
    for (auto pacman_end_iter = avatar_.active_pacmans().end();
         pacman_iter != pacman_end_iter;
         ++pacman_iter)
    {
        Pacman& pacman = *pacman_iter;
        info() << pacman.id() << ",";
        if (pacman.has_destination())
        {
            action_sequence.add_action<Move>(*pacman_iter, pacman.destination()) << pacman.destination();
            continue;
        }

        Position destination(-1,-1);
        if (sqiter_iter != viter.end())
        {
            destination = sqiter_iter->position();
            action_sequence.add_action<Move>(*pacman_iter, destination) << pacman.destination();
            ++sqiter_iter;
        }
        else
        {
            auto iter = std::find_if(world_.begin(), world_.end(), &square_is_place);
            if (iter == world_.end())
            {
                error() << "oO: Whut?! No more free square?!" << std::endl;
                break;
            }
            destination = iter.position();
            action_sequence.add_action<Move>(*pacman_iter, destination) << pacman.destination();
        }
        pacman.set_destination(destination);
    }

    output_ << action_sequence << std::endl;
}
