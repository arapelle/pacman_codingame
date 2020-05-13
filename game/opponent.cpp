#include "opponent.hpp"
#include "turn_info.hpp"

// Opponent:

Opponent::Opponent(Game& game)
    : Player(game, false)
{}

void Opponent::update_from_turn_info(const Turn_info& turn_info)
{
    if (turn_info.is_first_turn())
    {
        pacmans_.clear();
        for (const Pacman_info& pacman_info : turn_info.pacman_infos)
        {
            if (pacman_info.is_mine != is_mine())
            {
                Pacman pacman(*this);
                pacmans_.push_back(std::move(pacman));
            }
        }
    }

    Player::update_from_turn_info(turn_info);
}
