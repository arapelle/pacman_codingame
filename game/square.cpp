#include "square.hpp"

Square::Square()
    : type_(Type::Undefined), pellet_(-1)
{}

void Square::set_type_from_char(char ch)
{
    type_ = static_cast<Type>(ch);
}
