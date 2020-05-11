#include "turn_info.hpp"

// Pacman_info:

void Pacman_info::read_from_stream(std::istream& stream)
{
    stream >> pac_id >> is_mine >> x >> y >> type_id >> speed_turns_left >> ability_cooldown; stream.ignore();
}

// Pellet_info:

void Pellet_info::read_from_stream(std::istream& stream)
{
    stream >> x >> y >> value; stream.ignore();
}

// Turn_info:

Turn_info::Turn_info(unsigned turn_number)
    : turn_number(turn_number)
{
}

void Turn_info::read_from_stream(std::istream& stream)
{
    stream >> my_score >> opponent_score; stream.ignore();

    int visiblePacCount; // all your pacs and enemy pacs in sight
    stream >> visiblePacCount; stream.ignore();
    pacman_infos.resize(visiblePacCount);

    for (Pacman_info& pacman_info : pacman_infos)
        pacman_info.read_from_stream(stream);

    int visiblePelletCount; // all pellets in sight
    stream >> visiblePelletCount; stream.ignore();
    pellet_infos.resize(visiblePelletCount);

    for (Pellet_info& pellet_info : pellet_infos)
        pellet_info.read_from_stream(stream);
}
