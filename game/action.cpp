#include "action.hpp"
#include "pacman.hpp"

// Action:

Action::~Action()
{
}

std::string Action::message() const
{
    std::string msg = msg_stream_.str();
    msg.resize(max_buffer_size, ' ');
    return msg;
}

// Pacman_action:

Pacman_action::Pacman_action(const Pacman& pacman)
    : pacman_(&pacman)
{}

Pacman_action::~Pacman_action() {}

int Pacman_action::pacman_id() const { return pacman_->id(); }

// Move:

Move::Move(const Pacman& pacman, const Position& destination)
    : Pacman_action(pacman), destination_(destination)
{}

Move::~Move() {}

std::ostream& Move::write_to_stream(std::ostream& stream) const
{
    return stream << label << " " << pacman_id() << " " << destination_ << " " << std::string_view(message().c_str(), 7);
}

// Speed:

Speed::Speed(const Pacman& pacman)
    : Pacman_action(pacman)
{}

Speed::~Speed() {}

std::ostream& Speed::write_to_stream(std::ostream& stream) const
{
    return stream << label << " " << pacman_id() << " " << message();
}

// Switch:

Switch::Switch(const Pacman& pacman, Pacman_type new_type)
    : Pacman_action(pacman), new_type_(new_type)
{}

Switch::~Switch() {}

std::ostream& Switch::write_to_stream(std::ostream& stream) const
{
    return stream << label << " " << pacman_id() << " " << to_string(new_type_) << " " << message();
}

// Action_sequence:

Action_sequence::~Action_sequence() {}

Action& Action_sequence::add_action(std::shared_ptr<Action> action_sptr)
{
    actions_.push_back(std::move(action_sptr));
    return *actions_.back();
}

std::ostream& Action_sequence::write_to_stream(std::ostream& stream) const
{
    if (!actions_.empty())
    {
        if (actions_.size() > 1)
        {
            for (auto iter = actions_.begin(), end_iter = std::prev(actions_.end()); iter != end_iter; ++iter)
            {
                (*iter)->write_to_stream(stream);
                stream << " | ";
            }
        }
        actions_.back()->write_to_stream(stream);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Action_sequence& action_sequence)
{
    return action_sequence.write_to_stream(stream);
}
