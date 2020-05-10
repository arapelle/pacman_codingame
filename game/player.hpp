#pragma once

#include "pacman.hpp"
#include <vector>
#include <cassert>

class Game;
class Turn_info;

class Player
{
protected:
    explicit Player(Game& game, bool is_mine);

public:
    inline const Game& game() const { assert(game_); return *game_; }
    inline Game& game() { assert(game_); return *game_; }
    inline void set_game(Game& game) { game_ = &game; }

    inline const std::vector<Pacman>& pacmans() const { return pacmans_; }
    inline std::vector<Pacman>& pacmans() { return pacmans_; }

protected:
    void update_from_turn_info(const Turn_info& turn_info);

private:
    Game* game_ = nullptr;
    bool is_mine_;
    int score_;
    std::vector<Pacman> pacmans_;
};

class Avatar : public Player
{
public:
    explicit Avatar(Game& game);

    void update_from_turn_info(const Turn_info& turn_info);

private:
};

class Opponent : public Player
{
public:
    explicit Opponent(Game& game);

    void update_from_turn_info(const Turn_info& turn_info);

private:
};
