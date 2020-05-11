#include "world.hpp"
#include "turn_info.hpp"
#include "grid/grid_algo.hpp"

World::World(Game& game, unsigned width, unsigned height)
    : Base(width, height), game_(&game)
{}

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

void World::update_from_turn_info(const Turn_info& turn_info)
{
    remove_all_pellet_();
    for (Pellet_info pellet_info : turn_info.pellet_infos)
        get(pellet_info.x, pellet_info.y).set_pellet(static_cast<Pellet>(pellet_info.value));
}

void World::remove_all_pellet_()
{
    for_each_if(*this, &square_is_free, [](Square& square){ square.set_pellet(No_pellet); });
}
