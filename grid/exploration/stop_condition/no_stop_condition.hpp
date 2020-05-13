#pragma once

struct No_stop_condition
{
    template <typename MarkGrid>
    inline constexpr bool operator()(const MarkGrid&) const { return false; }
};
