#include "pacman_exploration_rules.hpp"
#include "game/pacman.hpp"
#include "accessibility_test.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "grid/exploration/mark_grid.hpp"
#include "grid/exploration/exploration_rules/torus_directions4_exploration_rules.hpp"

Pacman_exploration_rules::Pacman_exploration_rules(const Pacman& pacman)
    : pacman_(&pacman)
{
}

std::vector<Position> Pacman_exploration_rules::move_actions(const World& world, const Position& position,
                                                             const Game_mark& ) const
{
    std::vector<Position> npos;

    unsigned max_distance = pacman_->is_fast() ? 2 : 1;
    Max_distance<Square_is_accessible_for_pacman> accessibility_test;
    accessibility_test.set_max_distance(max_distance);
    accessibility_test.set_explorer_pacman(*pacman_);
    Torus_directions4_exploration_rules<const World> exploration_rules(world);
    using Mark = Distance_mark<>;
    Mark_grid<Mark> marks;

    auto square_visitor = [&](const World&, const Position& position, Mark&)
    {
        npos.push_back(position);
    };
    spread_from_start(marks, world, position, exploration_rules, accessibility_test, square_visitor);

    //TODO

    return npos;
}
