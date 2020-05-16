#pragma once

#include "grid/exploration/mark.hpp"

class Game_mark : public Root_mark<Distance_mark<Link_mark<Action_mark<Position>>>>
{
    using Base = Root_mark<Distance_mark<Link_mark<Action_mark<Position>>>>;

public:
    enum class Print_context
    {
        Exploration_square_status,
        Link_position,
        Distance,
    };

    using Base::Base;

    void print(std::ostream& stream, Print_context context = Print_context::Exploration_square_status) const;

private:
};
