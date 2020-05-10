#pragma once

#include "square.hpp"
#include "grid/grid.hpp"
#include <istream>

class World : public Grid<Square>
{
    using Base = Grid<Square>;

public:
    using Base::Base;
    void read_from_stream(std::istream& stream);

private:
};
