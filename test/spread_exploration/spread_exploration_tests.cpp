#include "spread_exploration_tests.hpp"
#include "grid/exploration/spread_exploration.hpp"
#include "log/log.hpp"
#include <iomanip>
#include <iostream>

namespace test
{
void Game_mark::print(std::ostream& stream, Print_context context) const
{
    switch (context)
    {
    case Print_context::Link_position:
        stream << "[" << std::setw(2) << link_position().x << " " << std::setw(2) << link_position().y << "]";
        break;
    case Print_context::Direction:
        stream << Directions4::to_arrow_char(action());
        break;
    case Print_context::Distance:
        stream << "[" << std::setw(2) << distance() << "]";
        break;
    default:
        stream << '?';
    }
}

void Game_mark_grid::print(std::ostream& stream, Game_mark::Print_context context) const
{
    for (unsigned j = 0, endj = height(); j != endj; ++j)
    {
        for (unsigned i = 0, endi = width(); i != endi; ++i)
        {
            get(i,j).print(stream, context);
        }
        stream << std::endl;
    }
}

// tests:

void backward_test()
{
    trace();
    Grid_world world(8, 6, Square(true));
    Square_is_space accessibility_test;
    Directions4_exploration_rules exploration_rules;
    Position start(2,1);
    Position dest(5,3);
    Game_mark_grid marks;
    spread_from_destination(marks, world, dest, exploration_rules, accessibility_test);
    marks.print(std::cout, Game_mark::Print_context::Link_position);
    marks.print(std::cout, Game_mark::Print_context::Direction);
    marks.print(std::cout, Game_mark::Print_context::Distance);
}

void forward_test()
{
    trace();
    Grid_world world(8, 6, Square(true));
    Square_is_space accessibility_test;
    Directions4_exploration_rules exploration_rules;
    Position start(2,1);
    Position dest(5,3);
    Game_mark_grid marks;
    spread_from_start(marks, world, dest, exploration_rules, accessibility_test);
    marks.print(std::cout, Game_mark::Print_context::Link_position);
    marks.print(std::cout, Game_mark::Print_context::Direction);
    marks.print(std::cout, Game_mark::Print_context::Distance);
}

void torus_backward_test()
{
    trace();
    Grid_world world(8, 6, Square(true));
    Square_is_space accessibility_test;
    Torus_directions4_exploration_rules<Grid_world> exploration_rules(world);
    Position start(2,1);
    Position dest(5,3);
    Game_mark_grid marks;
    spread_from_destination(marks, world, dest, exploration_rules, accessibility_test);
    marks.print(std::cout, Game_mark::Print_context::Link_position);
    marks.print(std::cout, Game_mark::Print_context::Direction);
    marks.print(std::cout, Game_mark::Print_context::Distance);
}

void torus_forward_test()
{
    trace();
    Grid_world world(8, 6, Square(true));
    Square_is_space accessibility_test;
    Torus_directions4_exploration_rules<Grid_world> exploration_rules(world);
    Position start(2,1);
    Position dest(5,3);
    Game_mark_grid marks;
    spread_from_start(marks, world, dest, exploration_rules, accessibility_test);
    marks.print(std::cout, Game_mark::Print_context::Link_position);
    marks.print(std::cout, Game_mark::Print_context::Direction);
    marks.print(std::cout, Game_mark::Print_context::Distance);
}

}
