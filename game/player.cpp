#include "player.hpp"
#include "turn_info.hpp"

// Player:

Player::Player(Game& game, bool is_mine)
    : game_(&game), is_mine_(is_mine), score_(-1)
{}

void Player::update_from_turn_info(const Turn_info& turn_info)
{
    score_ = is_mine_ ? turn_info.my_score : turn_info.opponent_score;
    active_pacmans_.clear();
    for (const Pacman_info& pacman_info : turn_info.pacman_infos)
    {
        if (pacman_info.is_mine == is_mine_)
        {
            Pacman& pacman = pacmans_.at(pacman_info.pac_id);
            pacman.update_from_pacman_info(pacman_info);
            active_pacmans_.push_back(std::ref(pacman));
        }
    }
}
