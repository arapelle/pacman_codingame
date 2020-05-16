#pragma once

#include "mark.hpp"
#include "game/world.hpp"
#include "grid/grid_types.hpp"
#include "direction/direction.hpp"
#include "direction/neighbourhood.hpp"

class Pacman;

class Pacman_exploration_rules
{
public:
    explicit Pacman_exploration_rules(const Pacman& pacman);

    std::vector<Position> move_actions(const World& world, const Position& position, const Game_mark& mark) const;

    inline Position next_position(const Position&, const Position& next_position) const
    {
        return next_position;
    }

    inline Position previous_position(const Position&, const Position& previous_position) const
    {
        return previous_position;
    }

private:
    const Pacman* pacman_;
};
