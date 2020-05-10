#pragma once

#include <random>

std::mt19937_64& rand_int_engine();

template <class NT>
NT randint (NT a, NT b)
{
    using Dist = std::uniform_int_distribution<NT>;
    static thread_local Dist dist;
    return dist(rand_int_engine(), typename Dist::param_type{a, b});
}


