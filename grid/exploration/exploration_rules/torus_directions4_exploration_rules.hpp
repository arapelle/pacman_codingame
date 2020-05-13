#pragma once

#include "directions4_exploration_rules.hpp"
#include "decorator/torus.hpp"

template <class GridType, typename Directions4ExplorationRules = Directions4_exploration_rules>
using Torus_directions4_exploration_rules = Torus<GridType, Directions4ExplorationRules>;
