#pragma once

#include "action.hpp"
#include "pacman_type.hpp"
#include "grid/grid_types.hpp"
#include <cassert>

class Game;
class Player;
class Pacman_info;

class Pacman
{
public:
    using Type = Pacman_type;
    inline static Position bad_position = Position(-1,-1);

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
    // strategy:
    bool has_destination() const;
    inline const Position& destination() const { return destination_; }
    inline void set_destination(const Position& position) { destination_ = position; }
    inline bool has_action_todo() const { return action_todo_ != nullptr; }
    inline Action_sptr action_todo() const { return action_todo_; }
    template <typename Action, typename... Args>
    Action& set_action_todo(Args&&... args)
    {
        auto action_sptr = std::make_shared<Action>(std::forward<Args>(args)...);
        Action& action_ref = *(action_sptr.get());
        action_todo_ = std::move(action_sptr);
        return action_ref;
    }

    void update_from_pacman_info(const Pacman_info& pacman_info);

private:
    Player* owner_ = nullptr;
    int id_; // pac number (unique within a team)
    Position position_; // position in the grid
    Position previous_position_; // previous position in the grid
    Type type_; // unused in wood leagues
    int speed_turns_left_; // unused in wood leagues
    int ability_cooldown_; // unused in wood leagues

    Position destination_;
    Action_sptr action_todo_;
};
