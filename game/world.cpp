#include "world.hpp"

void World::read_from_stream(std::istream& stream)
{
    int width; // size of the grid
    int height; // top left corner is (x=0, y=0)
    stream >> width >> height; stream.ignore();

    resize(width, height);

    for (int j = 0; j < height; j++)
    {
        std::string row;
        std::getline(stream, row); // one line of the grid: space " " is floor, pound "#" is wall
        int i = 0;
        for (char ch : row)
        {
            get(i,j).set_type_from_char(ch);
            ++i;
        }
    }
}
