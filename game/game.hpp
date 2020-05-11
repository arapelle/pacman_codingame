#pragma once

#include "player.hpp"
#include "world.hpp"
#include <iostream>

class Turn_info;
class Action_sequence;

class Game
{
public:
    Game(std::istream& input = std::cin, std::ostream& output = std::cout);

    const World& world() const { return world_; }
    World& world() { return world_; }
    const Avatar& avatar() const { return avatar_; };
    Avatar& avatar() { return avatar_; };
    const Opponent& opponent() const { return opponent_; }
    Opponent& opponent() { return opponent_; }

    // Start:
    void init();
    void play_start_actions();

    // Turn:
    void play_turn();

private:
    void update_from_turn_info_(const Turn_info& turn_info);
    void send_actions_();
    void assign_actions_();
    std::size_t assign_speed_action_();
    std::size_t assign_move_action_(std::vector<World::Iterator> square_iters);

private:
    std::istream& input_;
    std::ostream& output_;
    World world_;
    Avatar avatar_;
    Opponent opponent_;
    unsigned turn_number_;
};
