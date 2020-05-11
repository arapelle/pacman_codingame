#pragma once

#include <vector>
#include <istream>

class Pacman_info
{
public:
    void read_from_stream(std::istream& stream);

    int pac_id; // pac number (unique within a team)
    bool is_mine; // true if this pac is yours
    int x; // position in the grid
    int y; // position in the grid
    std::string type_id; // unused in wood leagues
    int speed_turns_left; // unused in wood leagues
    int ability_cooldown; // unused in wood leagues
};

class Pellet_info
{
public:
    void read_from_stream(std::istream& stream);

    int x;
    int y;
    int value; // amount of points this pellet is worth
};

class Turn_info
{
public:
    inline constexpr static unsigned first_turn_turn = 1;

    explicit Turn_info(unsigned turn_number);
    inline bool is_first_turn() const { return turn_number == first_turn_turn; }
    void read_from_stream(std::istream& stream);

    unsigned turn_number;
    int my_score;
    int opponent_score;
    std::vector<Pacman_info> pacman_infos;
    std::vector<Pellet_info> pellet_infos;
};
