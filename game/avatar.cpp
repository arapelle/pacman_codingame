#include "avatar.hpp"
#include "exploration/mark.hpp"
#include "exploration/associative_functor.hpp"
#include "exploration/mark_grid.hpp"
#include "exploration/accessibility_test.hpp"
#include "exploration/pacman_exploration_rules.hpp"
#include "exploration/pacman_exploration.hpp"
#include "action.hpp"
#include "game.hpp"
#include "turn_info.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "grid/exploration/stop_condition/positions_treated.hpp"
#include "grid/exploration/stop_condition/first_square_found.hpp"
#include "grid/exploration/exploration_rules/torus_directions4_exploration_rules.hpp"
#include "grid/grid_algo.hpp"
#include "core/random.hpp"
#include "core/algo.hpp"
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
    std::vector<Position> big_pellet_positions;
    for (const auto& iter : world.big_pellets_iters())
        big_pellet_positions.push_back(iter.position());
    std::vector<Position> forbidden_positions;

    std::vector<Pacman_exploration> explorations;
    explorations.resize(pacmans().size());

    for (Pacman& pacman : active_pacmans())
    {
        Pacman_exploration& exploration = explorations.at(pacman.id());
        pacman_exploration_(pacman, exploration, world, big_pellet_positions, forbidden_positions);

        Position goal_position(-1,-1);
        if (!exploration.reachable_big_pellet_positions.empty())
        {
            goal_position = exploration.reachable_big_pellet_positions.front();
            erase(big_pellet_positions, goal_position);
        }
        else if (world.contains(exploration.first_reachable_small_pellet_position))
        {
            goal_position = exploration.first_reachable_small_pellet_position;
        }

        if (world.contains(goal_position))
        {
            if (pacman.is_ability_available())
            {
                pacman.set_action_todo<Speed>(pacman) << "S." << goal_position;
            }
            else
            {
                Position step_position = goal_position;
                while (exploration.marks.get(step_position).link_position() != pacman.position())
                    step_position = exploration.marks.get(step_position).link_position();
                debug() << pacman.position() << ": Step position: " << step_position << std::endl;
                forbidden_positions.push_back(step_position);
                pacman.set_action_todo<Move>(pacman, step_position) << "M." << goal_position;
            }
        }
        else if (pacman.is_ability_available())
        {
            pacman.set_action_todo<Switch>(pacman, stronger(pacman.type()));
        }
    }

//    print_mark_grid_(marks);
}

void Avatar::pacman_exploration_(Pacman& pacman, Pacman_exploration& exploration, World& world,
                                 const std::vector<Position>& destination_positions,
                                 const std::vector<Position>& forbidden_positions)
{
    Square_is_accessible_for_pacman accessibility_test;
    accessibility_test.set_explorer_pacman(pacman);
    Pacman_exploration_rules exploration_rules(pacman);
    exploration_rules.forbidden_positions() = forbidden_positions;
    Position start_position = pacman.position();
    Positions_treated destinations_treated(destination_positions);
    auto first_pellet_found = make_first_square_found([](const World& world, const Position& position, const Game_mark&)
    {
        return square_has_small_pellet(world.get(position));
    });
    auto visitor = seq_join(std::ref(destinations_treated), std::ref(first_pellet_found));
    auto stop_condition = and_join(std::ref(destinations_treated), std::ref(first_pellet_found));

    destinations_treated.set_number_of_wanted_positions(active_pacmans().size());

    spread_from_start(exploration.marks, world, start_position,
                      exploration_rules, accessibility_test, std::ref(visitor), std::ref(stop_condition));

    if (first_pellet_found.position_is_found())
        exploration.first_reachable_small_pellet_position = first_pellet_found.found_position();
    exploration.reachable_big_pellet_positions = std::move(destinations_treated.treated_positions());
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
