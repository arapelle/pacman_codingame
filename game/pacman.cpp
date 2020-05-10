#include "pacman.hpp"
#include "turn_info.hpp"
#include "player.hpp"

Pacman::Pacman(Player& owner)
    : owner_(&owner),
      id_(-1),
      position_(-1,-1),
      type_id_("@_@"),
      speed_turns_left_(0),
      ability_cooldown_(0)
{}

const Game& Pacman::game() const { return owner().game(); }

Game& Pacman::game() { return owner().game(); }

void Pacman::update_from_pacman_info(const Pacman_info& pacman_info)
{
    id_ = pacman_info.pac_id;
    position_ = Position(pacman_info.x, pacman_info.y);
    type_id_ = pacman_info.type_id;
    speed_turns_left_ = pacman_info.speed_turns_left;
    ability_cooldown_ = pacman_info.ability_cooldown;
}
