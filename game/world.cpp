#include "world.hpp"
#include "player.hpp"
#include "turn_info.hpp"
#include "game.hpp"
#include "direction/neighbourhood.hpp"
#include "direction/direction.hpp"
#include "grid/grid_algo.hpp"
#include "log/log.hpp"

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
    remove_all_big_pellet_();
    for (auto& square : *this)
        square.set_pacman(nullptr);

    Opponent& opponent = game().opponent();
    for (Pacman& pacman : opponent.pacmans())
    {
        if (contains(pacman.position()))
            get(pacman.position()).set_pacman(pacman);
    }

    Avatar& avatar = game().avatar();
    for (Pacman& pacman : avatar.active_pacmans())
    {
        get(pacman.position()).set_pacman(pacman);
        remove_all_pellet_around_pacman_(pacman);
    }

    big_pellets_iters_.clear();
    for (const Pellet_info& pellet_info : turn_info.pellet_infos)
    {
        Iterator iter = make_iterator(Position(pellet_info.x, pellet_info.y));
        Pellet pellet = static_cast<Pellet>(pellet_info.value);
        if (pellet == Big_pellet)
            big_pellets_iters_.push_back(iter);
        iter->set_pellet(pellet);
    }
    small_pellets_iters_ = find_all_if(*this, &square_has_small_pellet);
}

void World::remove_all_pellet_()
{
    for_each_if(*this, &square_is_place, [](Square& square){ square.set_pellet(No_pellet); });
}

void World::remove_all_big_pellet_()
{
    for_each_if(*this, &square_has_big_pellet, [](Square& square){ square.set_pellet(No_pellet); });
}

void World::remove_all_pellet_around_pacman_(const Pacman& pacman)
{
    get(pacman.position()).set_pellet(No_pellet);
    for (Direction4 dir : Directions4::directions)
    {
        Position position = pacman.position();
        for (;;)
        {
            position = neighbour(position, dir);
            if (contains(position))
            {
                if (Square& square = get(position); square.is_place())
                {
                    square.set_pellet(No_pellet);
                    continue;
                }
            }
            break;
        }
    }
}

void World::print(std::ostream& stream)
{
    stream << std::endl;
    for (unsigned j = 0; j < height(); ++j)
    {
        for (unsigned i = 0; i < width(); ++i)
            get(i,j).print(stream);
        stream << std::endl;
    }
}
