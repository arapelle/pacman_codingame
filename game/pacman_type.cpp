#include "pacman_type.hpp"
#include "log/log.hpp"

std::string_view to_string(const Pacman_type& type)
{
    switch (type)
    {
    case Pacman_type::Rock: return "ROCK";
    case Pacman_type::Paper: return "PAPER";
    case Pacman_type::Scissors: return "SCISSORS";
    }
    error() << "Unknown type!" << std::endl;
    return "Unknown";
}

Pacman_type stronger(const Pacman_type& type)
{
    switch (type)
    {
    case Pacman_type::Rock: return Pacman_type::Paper;
    case Pacman_type::Paper: return Pacman_type::Scissors;
    case Pacman_type::Scissors: return Pacman_type::Rock;
    }
    error() << "Unknown type!" << std::endl;
    return Pacman_type();
}

Pacman_type weaker(const Pacman_type& type)
{
    switch (type)
    {
    case Pacman_type::Rock: return Pacman_type::Scissors;
    case Pacman_type::Paper: return Pacman_type::Rock;
    case Pacman_type::Scissors: return Pacman_type::Paper;
    }
    error() << "Unknown type!" << std::endl;
    return Pacman_type();
}
