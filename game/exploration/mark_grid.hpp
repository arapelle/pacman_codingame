#pragma once

#include "mark.hpp"
#include "grid/exploration/mark_grid.hpp"

class Game_mark_grid : public Mark_grid<Game_mark>
{
public:
    void print(std::ostream& stream, Game_mark::Print_context context = Game_mark::Print_context::Exploration_square_status) const;

private:
};
