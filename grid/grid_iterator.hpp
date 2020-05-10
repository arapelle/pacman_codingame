#pragma once

#include "grid_types.hpp"
#include <iterator>
#include <type_traits>

template <typename GridPointer>
class Grid_iterator
{
public:
    using Grid_type = std::remove_reference_t<decltype(*std::declval<GridPointer>())>;
    using Value_type = typename Grid_type::Value_type;
    // standard compliance:
    using difference_type = int;
    using value_type = Value_type;
    using pointer = std::add_pointer_t<value_type>;
    using reference = std::add_lvalue_reference_t<value_type>;
    using iterator_category = std::bidirectional_iterator_tag;

    Grid_iterator(GridPointer grid_ptr, const Position& pos)
        : grid_ptr_(grid_ptr), pos_(pos)
    {}

    Grid_iterator& operator++()
    {
        grid_ptr_->advance(pos_);
        return *this;
    }

    Grid_iterator operator++(int)
    {
        Grid_iterator iter(*this);
        grid_ptr_->advance(pos_);
        return iter;
    }

    Grid_iterator& operator--()
    {
        grid_ptr_->advance_backward(pos_);
        return *this;
    }

    Grid_iterator operator--(int)
    {
        Grid_iterator iter(*this);
        grid_ptr_->advance_backward(pos_);
        return iter;
    }

    const auto& operator*() const { return value(); }
    auto& operator*() { return value(); }

    const auto* operator->() const { return &value(); }
    auto* operator->() { return &value(); }

    inline const auto& value() const { return grid_ptr_->get(pos_); }
    inline auto& value() { return grid_ptr_->get(pos_); }

    const Position& position() const { return pos_; }

    bool operator==(const Grid_iterator& rhs) const
    {
        return grid_ptr_ == rhs.grid_ptr_ && pos_ == rhs.pos_;
    }

    bool operator!=(const Grid_iterator& rhs) const { return !(*this == rhs); }

private:
    GridPointer grid_ptr_;
    Position pos_;
};
