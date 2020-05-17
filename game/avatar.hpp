#pragma once

#include "player.hpp"
#include "world.hpp"

class Game_mark_grid;
class Pacman_exploration;

class Avatar : public Player
{
public:
    explicit Avatar(Game& game);

    void update_from_turn_info(const Turn_info& turn_info);
    void manage_pacmans();
    void manage_pacmans_2();

private:
    void pacman_exploration_(Pacman& pacman, Pacman_exploration &mark_grid, World &world,
                             const std::vector<Position>& destination_positions, const std::vector<Position> &forbidden_positions);
    void print_mark_grid_(const Game_mark_grid& mark_grid);

private:
    std::size_t assign_speed_action_();
    std::size_t assign_move_action_(std::vector<World::Iterator> square_iters);
};
