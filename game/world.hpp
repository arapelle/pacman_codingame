#pragma once

#include "square.hpp"
#include "grid/grid.hpp"
#include "direction/neighbourhood.hpp"
#include <istream>

class Game;
class Pacman;
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
    inline const std::vector<Iterator>& big_pellets_iters() const { return big_pellets_iters_; }
    inline const std::vector<Iterator>& small_pellets_iters() const { return small_pellets_iters_; }

    void update_from_turn_info(const Turn_info& turn_info);

    template <class Predicate>
    bool any_neighbour_square_if(const Position& position, Predicate predicate) const
    {
        for (const Position& npos : neighbours4(position))
        {
            if (contains(npos))
            {
                const Square& nsquare = get(npos);
                if (predicate(nsquare))
                    return true;
            }
        }
        return false;
    }

private:
    void remove_all_pellet_();
    void remove_all_big_pellet_();
    void remove_all_pellet_around_pacman_(const Pacman& pacman);

public:
    void print(std::ostream& stream);

private:
    Game* game_ = nullptr;
    std::vector<Iterator> small_pellets_iters_;
    std::vector<Iterator> big_pellets_iters_;
};
