#pragma once

#include "mark_grid.hpp"

struct Pacman_exploration
{
    Game_mark_grid marks;
    std::vector<Position> reachable_big_pellet_positions;
    Position first_reachable_small_pellet_position = Position(-1,-1);
};
