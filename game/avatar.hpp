#pragma once

#include "player.hpp"
#include "world.hpp"

class Avatar : public Player
{
public:
    explicit Avatar(Game& game);

    void update_from_turn_info(const Turn_info& turn_info);
    void manage_pacmans();

private:
    std::size_t assign_speed_action_();
    std::size_t assign_move_action_(std::vector<World::Iterator> square_iters);
};
