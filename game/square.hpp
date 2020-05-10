#pragma once

using Pellet = int;
inline constexpr Pellet big_pellet = 10;
inline constexpr Pellet small_pellet = 1;
inline constexpr Pellet no_pellet = 0;

class Square
{
public:
    enum class Type : char
    {
        Empty = ' ',
        Wall = '#',
        Undefined = '?',
    };

public:
    Square();
    void set_type_from_char(char ch);
    inline bool is_free() const { return type_ == Type::Empty; }

    inline Pellet pellet() const { return pellet_; }
    inline bool has_pellet() const { return pellet_ > 0; }
    inline void set_pellet(Pellet pellet) { pellet_ = pellet; }

private:
    Type type_;
    Pellet pellet_;
};

inline bool square_is_free(const Square& square) { return square.is_free(); }
inline bool square_has_big_pellet(const Square& square) { return square.pellet() == big_pellet; }
inline bool square_has_small_pellet(const Square& square) { return square.pellet() == small_pellet; }
inline bool square_has_pellet(const Square& square) { return square.has_pellet(); }
