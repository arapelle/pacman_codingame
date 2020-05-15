#include "mark.hpp"
#include <iomanip>

void Game_mark::print(std::ostream& stream, Print_context context) const
{
    switch (context)
    {
    case Print_context::Exploration_square_status:
    {
        char ch = '?';
        switch (status())
        {
        case Exploration_square_status::Unvisited: ch = 'U'; break;
        case Exploration_square_status::Visited: ch = 'V'; break;
        case Exploration_square_status::Treated: ch = 'T'; break;
        }
        stream << "[  " << ch << "  ]";
        break;
    }
    case Print_context::Link_position:
        stream << "[" << std::setw(2) << link_position().x << " " << std::setw(2) << link_position().y << "]";
        break;
    case Print_context::Direction:
        stream << Directions4::to_arrow_char(action());
        break;
    case Print_context::Distance:
        stream << "[" << std::setw(2) << distance() << "]";
        break;
    default:
        stream << '?';
    }
}
