#pragma once

#include <ostream>
#include <cstddef>

enum Pellet : int
{
    No_pellet = 0,
    Small_pellet = 1,
    Big_pellet = 10,
};

class Pacman;

class Square
{
public:
    enum class Type : char
    {
        Place = ' ',
        Wall = '#',
        Undefined = '?',
    };

public:
    Square();
    void set_type_from_char(char ch);
    inline bool is_place() const { return type_ == Type::Place; }
    inline bool is_wall() const { return type_ == Type::Wall; }

    inline Pellet pellet() const { return pellet_; }
    inline bool has_pellet() const { return pellet_ > 0; }
    inline void set_pellet(Pellet pellet) { pellet_ = pellet; }

    inline const Pacman* pacman() const { return pacman_; }
    inline Pacman* pacman() { return pacman_; }

private:
    friend class World;
    void set_pacman(std::nullptr_t) { pacman_ = nullptr; }
    void set_pacman(Pacman& pacman) { pacman_ = &pacman; }

public:
    void print(std::ostream& stream);

private:
    Type type_;
    Pellet pellet_;
    Pacman* pacman_ = nullptr;
};

inline bool square_is_place(const Square& square) { return square.is_place(); }
inline bool square_is_wall(const Square& square) { return square.is_wall(); }
inline bool square_has_big_pellet(const Square& square) { return square.pellet() == Big_pellet; }
inline bool square_has_small_pellet(const Square& square) { return square.pellet() == Small_pellet; }
inline bool square_has_pellet(const Square& square) { return square.has_pellet(); }
