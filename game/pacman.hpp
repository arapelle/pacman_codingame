#pragma once

#include "grid/grid_types.hpp"
#include <cassert>

class Game;
class Player;
class Pacman_info;

class Pacman
{
public:
    explicit Pacman(Player& owner);

    const Game& game() const;
    Game& game();

    inline const Player& owner() const { assert(owner_); return *owner_; }
    inline Player& owner() { assert(owner_); return *owner_; }
    inline void set_owner(Player& owner) { owner_ = &owner; }

    inline int id() const { return id_; }
    inline void set_id(int id) { id_ = id; }
    inline const Position& position() const { return position_; }
    inline Position& position() { return position_; }

    void update_from_pacman_info(const Pacman_info& pacman_info);

private:
    Player* owner_ = nullptr;
    int id_; // pac number (unique within a team)
    Position position_; // position in the grid
    std::string type_id_; // unused in wood leagues
    int speed_turns_left_; // unused in wood leagues
    int ability_cooldown_; // unused in wood leagues
};
