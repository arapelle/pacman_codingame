#pragma once

#include "no_stop_condition.hpp"
#include "grid/grid_types.hpp"
#include <vector>

template <class StopConditionBase = No_stop_condition>
class Positions_treated : public StopConditionBase
{
public:
    Positions_treated()
        : number_of_wanted_positions_(std::numeric_limits<std::size_t>::max())
    {}

    explicit Positions_treated(const Position& position)
        : positions_to_treat_{ position }
        , number_of_wanted_positions_(std::numeric_limits<std::size_t>::max())
    {}

    explicit Positions_treated(const std::vector<Position>& positions)
        : positions_to_treat_(positions)
        , number_of_wanted_positions_(std::numeric_limits<std::size_t>::max())
    {}

    explicit Positions_treated(const std::initializer_list<Position>& positions)
        : positions_to_treat_(positions)
        , number_of_wanted_positions_(std::numeric_limits<std::size_t>::max())
    {}

    template <typename MarkGrid>
    inline bool operator()(const MarkGrid& mark_grid)
    {
        for (auto iter = positions_to_treat_.begin(); iter != positions_to_treat_.end(); )
        {
            Position position = *iter;
            if (mark_grid.is_treated(mark_grid.get(position)))
            {
                positions_to_treat_.erase(iter);
                treated_positions_.push_back(position);
            }
            else
            {
                ++iter;
            }
        }

        return positions_to_treat_.empty()
                || treated_positions_.size() == number_of_wanted_positions_
                || static_cast<const StopConditionBase&>(*this)(mark_grid);
    }

    inline const std::vector<Position>& positions_to_treat() const { return positions_to_treat_; }
    inline std::vector<Position>& positions_to_treat() { return positions_to_treat_; }
    inline const std::vector<Position>& treated_positions() const { return treated_positions_; }
    inline std::size_t number_of_wanted_positions() const { return number_of_wanted_positions_; }
    inline void set_number_of_wanted_positions(std::size_t count) { number_of_wanted_positions_ = count; }

private:
    std::vector<Position> positions_to_treat_;
    std::vector<Position> treated_positions_;
    std::size_t number_of_wanted_positions_;
};
