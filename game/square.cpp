#include "square.hpp"
#include "pacman.hpp"

Square::Square()
    : type_(Type::Undefined), pellet_(No_pellet), pacman_(nullptr)
{}

void Square::set_type_from_char(char ch)
{
    type_ = static_cast<Type>(ch);
}

void Square::print(std::ostream& stream)
{
    switch (type_)
    {
    case Type::Place:
    {
        if (pacman_)
            stream << pacman_->char_id();
        else
            switch (pellet_)
            {
            case No_pellet:
                stream << ' ';
                break;
            case Small_pellet:
                stream << '.';
                break;
            case Big_pellet:
                stream << '*';
                break;
            }
        break;
    }
    case Type::Wall:
        stream << '#';
        break;
    case Type::Undefined:
        stream << '?';
        break;
    }
}
