#pragma once

#include "no_stop_condition.hpp"
#include "grid/grid_types.hpp"

template <class Predicate, class StopConditionBase = No_stop_condition>
class First_square_found : public StopConditionBase
{
public:
    explicit First_square_found(Predicate predicate)
        : found_position_(-1,-1), predicate_(std::move(predicate))
    {}

    template <typename GridWorld, typename Mark>
    void operator()(GridWorld& world, const Position& position, Mark& mark)
    {
        if (!position_is_found() && predicate_(world, position, mark))
            found_position_ = position;
    }

    template <typename MarkGrid>
    inline bool operator()(const MarkGrid&)
    {
        return position_is_found();
    }

    inline bool position_is_found() const { return found_position_ != Position(-1,-1); }
    inline Position found_position() const { return found_position_; }

private:
    Position found_position_;
    Predicate predicate_;
};

template <class Predicate, class StopConditionBase = No_stop_condition>
auto make_first_square_found(Predicate&& predicate)
{
    return First_square_found<Predicate, StopConditionBase>(std::forward<Predicate>(predicate));
}
