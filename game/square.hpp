#pragma once

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

private:
    Type type_;
};
