#include "pacman.hpp"
#include "turn_info.hpp"
#include "player.hpp"
#include "game.hpp"
#include "world.hpp"
#include "log/log.hpp"

Pacman::Pacman(Player& owner)
    : owner_(&owner),
      id_(-1),
      position_(-1,-1),
      previous_position_(-1,-1),
      type_(Type::Rock),
      speed_turns_left_(0),
      ability_cooldown_(0),
      destination_(-1,-1)
{}

const Game& Pacman::game() const { return owner().game(); }

Game& Pacman::game() { return owner().game(); }

bool Pacman::is_mine() const { return owner().is_mine(); }

bool Pacman::is_stronger(const Pacman& pacman) const
{
    if (type_ != Type::Rock)
        return pacman.type() == Type::Scissors;
    return static_cast<uint8_t>(type_) > static_cast<uint8_t>(pacman.type());
}

bool Pacman::has_destination() const
{
    const World& world = owner().game().world();
    return world.contains(destination_) && world.get(destination_).has_pellet();
}

void Pacman::update_from_pacman_info(const Pacman_info& pacman_info)
{
    id_ = pacman_info.pac_id;
    previous_position_ = position_;
    position_ = Position(pacman_info.x, pacman_info.y);
    if (is_mine() && position_ == previous_position_)
        destination_ = bad_position;
    if (pacman_info.type_id == "ROCK")
        type_ = Type::Rock;
    else if (pacman_info.type_id == "PAPER")
        type_ = Type::Paper;
    else if (pacman_info.type_id == "SCISSORS")
        type_ = Type::Scissors;
    else
    {
        error() << "Unknown type!" << std::endl;
        exit(-1);
    }
    speed_turns_left_ = pacman_info.speed_turns_left;
    ability_cooldown_ = pacman_info.ability_cooldown;
}

//-----

std::string_view to_string(const Pacman::Type& type)
{
    switch (type)
    {
    case Pacman::Type::Rock: return "ROCK";
    case Pacman::Type::Paper: return "PAPER";
    case Pacman::Type::Scissors: return "SCISSORS";
    }
    error() << "Unknown type!" << std::endl;
    return "Unknown";
}
