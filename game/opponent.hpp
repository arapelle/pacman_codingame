#pragma once

#include "player.hpp"

class Opponent : public Player
{
public:
    explicit Opponent(Game& game);

    void update_from_turn_info(const Turn_info& turn_info);

private:
};
