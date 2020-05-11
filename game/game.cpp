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
    assign_actions_();

    Action_sequence action_sequence;
    for (const Pacman& pacman : avatar_.active_pacmans())
        if (Action_sptr action_sptr = pacman.action_todo(); action_sptr)
            action_sequence.add_action(std::move(action_sptr));
    output_ << action_sequence << std::endl;
}

void Game::assign_actions_()
{
    std::size_t count = 0;
    std::size_t pacman_count = avatar_.active_pacmans().size();

    count += assign_speed_action_();
    debug() << "Assign speed: " << count << std::endl;
    if (count == pacman_count)
        return;

    count += assign_move_action_(world_.big_pellets_iters());
    debug() << "Assign move to big pellet: " << count << std::endl;
    if (count == pacman_count)
        return;

    count += assign_move_action_(world_.small_pellets_iters());
    debug() << "Assign move to small pellet: " << count << std::endl;
    if (count == pacman_count)
        return;

    count += assign_move_action_(find_all_if(world_, &square_is_place));
    debug() << "Assign move to square: " << count << std::endl;
}

std::size_t Game::assign_speed_action_()
{
    std::size_t count = 0;

    for (Pacman& pacman : avatar_.active_pacmans())
    {
        if (pacman.has_action_todo())
            continue;

        if (pacman.is_ability_available())
        {
            pacman.set_action_todo<Speed>(pacman) << pacman.destination();
            ++count;
        }
    }

    return count;
}

std::size_t Game::assign_move_action_(std::vector<World::Iterator> square_iters)
{
    trace();
    std::size_t count = 0;

    std::shuffle(square_iters.begin(), square_iters.end(), rand_int_engine());

    auto square_iter = square_iters.begin();
    for (Pacman& pacman : avatar_.active_pacmans())
    {
        debug() << "pacman: " << pacman.char_id() << std::endl;
        if (pacman.has_action_todo())
            continue;

        if (square_iter == square_iters.end())
            break;

        if (!pacman.has_destination())
        {
            pacman.set_destination(square_iter->position());
            ++square_iter;
        }
        assert(pacman.has_destination());
        pacman.set_action_todo<Move>(pacman, pacman.destination()) << pacman.destination();
        ++count;
    }

    return count;
}
