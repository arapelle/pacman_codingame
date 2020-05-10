#include "action.hpp"
#include "pacman.hpp"

// Action:

Action::~Action()
{
}

// Pacman_action:

Pacman_action::Pacman_action(const Pacman& pacman)
    : pacman_(&pacman)
{}

Pacman_action::~Pacman_action() {}

int Pacman_action::pacman_id() const { return pacman_->id(); }

// Goto:

Move::Move(const Pacman& pacman, const Position& destination)
    : Pacman_action(pacman), destination_(destination)
{}

Move::~Move() {}

std::ostream& Move::write_to_stream(std::ostream& stream) const
{
    return stream << "MOVE " << pacman_id() << " " << destination_;
}

// Action_sequence:

Action_sequence::~Action_sequence() {}

void Action_sequence::add_action(std::unique_ptr<Action> action_uptr)
{
    actions_.push_back(std::move(action_uptr));
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
