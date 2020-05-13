#include "avatar.hpp"
#include "action.hpp"
#include "game.hpp"
#include "turn_info.hpp"
#include "grid/grid_algo.hpp"
#include "core/random.hpp"
#include "log/log.hpp"

// Avatar:

Avatar::Avatar(Game& game)
    : Player(game, true)
{}

void Avatar::update_from_turn_info(const Turn_info& turn_info)
{
    if (turn_info.is_first_turn())
    {
        pacmans_.clear();
        for (const Pacman_info& pacman_info : turn_info.pacman_infos)
        {
            if (pacman_info.is_mine == is_mine())
            {
                Pacman pacman(*this);
                pacmans_.push_back(std::move(pacman));
            }
        }
    }

    Player::update_from_turn_info(turn_info);
}

void Avatar::manage_pacmans()
{
    std::size_t count = 0;
    std::size_t pacman_count = active_pacmans().size();

    World& world_ = game().world();

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

std::size_t Avatar::assign_speed_action_()
{
    std::size_t count = 0;

    for (Pacman& pacman : active_pacmans())
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

std::size_t Avatar::assign_move_action_(std::vector<World::Iterator> square_iters)
{
    std::size_t count = 0;

    std::shuffle(square_iters.begin(), square_iters.end(), rand_int_engine());

    auto square_iter = square_iters.begin();
    for (Pacman& pacman : active_pacmans())
    {
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
