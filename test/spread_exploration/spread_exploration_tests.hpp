#pragma once

#include "grid/grid.hpp"
#include "grid/exploration/mark.hpp"
#include "grid/exploration/mark_grid.hpp"
#include "grid/exploration/stop_condition/positions_treated.hpp"
#include "grid/exploration/exploration_rules/directions4_exploration_rules.hpp"
#include "grid/exploration/exploration_rules/torus_directions4_exploration_rules.hpp"

namespace test
{
// world types:

class Square
{
public:
    explicit Square(bool value = true)
        : value_(value)
    {}

    bool is_space() const { return value_; }
    void set_value(bool value) { value_ = value; }

private:
    bool value_;
};

using Grid_world = Grid<Square>;

// exploration types:

struct Square_is_space
{
    template <class Mark>
    bool operator()(const Grid_world& world, const Position& position, const Mark& )
    {
        const Square& square = world.get(position);
        return square.is_space();
    }
};

class Game_mark : public Distance_mark<Link_mark<Action_mark<Direction4>>>
{
    using Base = Distance_mark<Link_mark<Action_mark<Direction4>>>;

public:
    enum class Print_context
    {
        Direction,
        Link_position,
        Distance,
    };

    using Base::Base;

    void print(std::ostream& stream, Print_context context = Print_context::Direction) const;

private:
};

class Game_mark_grid : public Mark_grid<Game_mark>
{
public:
    void print(std::ostream& stream, Game_mark::Print_context context = Game_mark::Print_context::Direction) const;

private:
};

// tests:

void backward_test();
void forward_test();
void torus_backward_test();
void torus_forward_test();
void positions_treated_test();
}
