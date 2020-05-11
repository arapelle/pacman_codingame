#pragma once

#include <string_view>
#include <cstdint>

enum class Pacman_type : uint8_t
{
    Rock,
    Paper,
    Scissors,
};

std::string_view to_string(const Pacman_type& type);
Pacman_type stronger(const Pacman_type& type);
Pacman_type weaker(const Pacman_type& type);
