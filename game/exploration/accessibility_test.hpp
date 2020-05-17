#pragma once

#include "game/pacman.hpp"
#include "game/world.hpp"
#include "grid/grid_types.hpp"

struct Square_is_place
{
    template <class Mark>
    bool operator()(const World& world, const Position& position, const Mark& ) const
    {
        return is_place(world.get(position));
    }

protected:
    inline bool is_place(const Square& square) const
    {
        return square.is_place();
    }
};


struct Square_is_accessible_for_pacman : public Square_is_place
{
    Square_is_accessible_for_pacman()
        : pacman_(nullptr)
    {}

    void set_explorer_pacman(const Pacman& pacman) { pacman_ = &pacman; }

    template <class Mark>
    bool operator()(const World& world, const Position& position, const Mark& ) const
    {
        const Square& square = world.get(position);
        if (!this->is_place(square))
            return false;
        if (std::find(forbidden_pos_.begin(), forbidden_pos_.end(), position) != forbidden_pos_.end())
            return false;
        const Pacman* other_pacman = square.pacman();
        if (other_pacman == nullptr)
        {
            return !world.any_neighbour_square_if(position, [this](const Square& square)
            {
                const Pacman* pacman = square.pacman();
                return pacman && pacman->is_mine() != pacman_->is_mine() && pacman->is_stronger(*pacman_);
            });
        }
        if (other_pacman == pacman_) // Oo whut?
            return true;
        if (other_pacman->is_mine() != pacman_->is_mine())
            return pacman_->is_stronger(*other_pacman);
        return false;
    }

    inline const std::vector<Position>& forbidden_positions() const { return forbidden_pos_; }
    inline std::vector<Position>& forbidden_positions() { return forbidden_pos_; }

private:
    const Pacman* pacman_;
    std::vector<Position> forbidden_pos_;
};

template <class AccessibilityTestBase>
struct Max_distance : public AccessibilityTestBase
{
    Max_distance()
        : max_distance_(std::numeric_limits<unsigned>::max())
    {}

    void set_max_distance(unsigned max_distance) { max_distance_ = max_distance; }

    template <class Mark>
    bool operator()(const World& world, const Position& position, const Mark& mark)
    {
        return mark.distance() <= max_distance_
            && static_cast<const AccessibilityTestBase&>(*this)(world, position, mark);
    }

private:
    unsigned max_distance_;
};
