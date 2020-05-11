#pragma once

#include "grid/grid_types.hpp"
#include <cassert>

class Game;
class Player;
class Pacman_info;

class Pacman
{
public:
    enum class Type : uint8_t
    {
        Rock,
        Paper,
        Scissors,
    };

public:
    explicit Pacman(Player& owner);

    const Game& game() const;
    Game& game();

    inline const Player& owner() const { assert(owner_); return *owner_; }
    inline Player& owner() { assert(owner_); return *owner_; }
    inline void set_owner(Player& owner) { owner_ = &owner; }
    bool is_mine() const;

    // id:
    inline int id() const { return id_; }
    inline char char_id() const { return (is_mine() ? '0' : 'A') + id_; }
    // pos:
    inline const Position& position() const { return position_; }
    // type:
    inline Type type() const { return type_; }
    bool is_stronger(const Pacman& pacman) const;
    // ability:
    inline bool is_fast() const { return speed_turns_left_ > 0; }
    inline bool is_ability_available() const { return ability_cooldown_ == 0; }
    inline int ability_cooldown() const { return ability_cooldown_; }

    void update_from_pacman_info(const Pacman_info& pacman_info);

private:
    Player* owner_ = nullptr;
    int id_; // pac number (unique within a team)
    Position position_; // position in the grid
    Type type_; // unused in wood leagues
    int speed_turns_left_; // unused in wood leagues
    int ability_cooldown_; // unused in wood leagues
};

std::string_view to_string(const Pacman::Type& type);
