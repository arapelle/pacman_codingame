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

    inline const std::vector<Position>& forbidden_positions() const { return forbidden_pos_; }
    inline std::vector<Position>& forbidden_positions() { return forbidden_pos_; }

private:
    const Pacman* pacman_;
    std::vector<Position> forbidden_pos_;
};
