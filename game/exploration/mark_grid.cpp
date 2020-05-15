#include "mark_grid.hpp"

void Game_mark_grid::print(std::ostream& stream, Game_mark::Print_context context) const
{
    for (unsigned j = 0, endj = height(); j != endj; ++j)
    {
        for (unsigned i = 0, endi = width(); i != endi; ++i)
        {
            get(i,j).print(stream, context);
        }
        stream << std::endl;
    }
}
