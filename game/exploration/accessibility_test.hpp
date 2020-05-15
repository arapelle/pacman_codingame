#pragma once

#include "game/world.hpp"
#include "grid/grid_types.hpp"

struct Square_is_place
{
    template <class Mark>
    bool operator()(const World& world, const Position& position, const Mark& )
    {
        const Square& square = world.get(position);
        return square.is_place();
    }
};
