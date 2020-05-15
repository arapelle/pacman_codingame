#pragma once

#include "grid/exploration/mark.hpp"

class Game_mark : public Root_mark<Distance_mark<Link_mark<Action_mark<Direction4>>>>
{
    using Base = Root_mark<Distance_mark<Link_mark<Action_mark<Direction4>>>>;

public:
    enum class Print_context
    {
        Exploration_square_status,
        Direction,
        Link_position,
        Distance,
    };

    using Base::Base;

    void print(std::ostream& stream, Print_context context = Print_context::Direction) const;

private:
};
