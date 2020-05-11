#pragma once

#include "square.hpp"
#include "grid/grid.hpp"
#include <istream>

class Game;
class Turn_info;

class World : public Grid<Square>
{
    using Base = Grid<Square>;

public:
    explicit World(Game& game, unsigned width = 0, unsigned height = 0);

    void read_from_stream(std::istream& stream);

    inline const Game& game() const { assert(game_); return *game_; }
    inline Game& game() { assert(game_); return *game_; }
    inline void set_game(Game& game) { game_ = &game; }

    void update_from_turn_info(const Turn_info& turn_info);

private:
    void remove_all_pellet_();

private:
    Game* game_ = nullptr;
};
