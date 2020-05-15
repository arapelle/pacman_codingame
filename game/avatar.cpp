#include "avatar.hpp"
#include "exploration/mark.hpp"
#include "exploration/mark_grid.hpp"
#include "exploration/accessibility_test.hpp"
#include "action.hpp"
#include "game.hpp"
#include "turn_info.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "grid/exploration/stop_condition/positions_treated.hpp"
#include "grid/exploration/exploration_rules/torus_directions4_exploration_rules.hpp"
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

// manage pacmans #1:

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

// manage pacmans #2:

void Avatar::manage_pacmans_2()
{
    trace();
    Duration_trace();

    World& world = game().world();
    Square_is_place accessibility_test;
    Torus_directions4_exploration_rules<World> exploration_rules(world);
    Game_mark_grid marks;
    std::vector<Position> start_positions;
    for (const Pacman& pacman : active_pacmans())
        start_positions.push_back(pacman.position());
    std::vector<Position> destination_positions;
    for (const auto& iter : world.big_pellets_iters())
        destination_positions.push_back(iter.position());
    Positions_treated destinations_treated(destination_positions);
    destinations_treated.set_number_of_wanted_positions(start_positions.size());

    spread_from_starts(marks, world, start_positions.begin(), start_positions.end(),
                       exploration_rules, accessibility_test, default_square_visitor, std::ref(destinations_treated));

    for (const Position& position : destinations_treated.treated_positions())
        debug() << "Pacman(" << marks.get(position).root_position() << ") go to (" << position << ")" << std::endl;

//    print_mark_grid_(marks);
}

void Avatar::print_mark_grid_(const Game_mark_grid& mark_grid)
{
    const World& world = game().world();
    for (unsigned j = 0, endj = mark_grid.height(); j != endj; ++j)
    {
        for (unsigned i = 0, endi = mark_grid.width(); i != endi; ++i)
        {
            const Square& square = world.get(i,j);
            if (const Pacman* pacman = square.pacman(); pacman)
                info() << "[=_" << pacman->char_id() << "_=]";
            else if (square.is_wall())
                info() << "[#####]";
            else
                mark_grid.get(i,j).print(info(), Game_mark::Print_context::Link_position);
        }
        info() << std::endl;
    }
}
