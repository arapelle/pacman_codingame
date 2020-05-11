#pragma once

#include "pacman.hpp"
#include "grid/grid_types.hpp"
#include <sstream>
#include <ostream>
#include <vector>
#include <memory>

class Action
{
    inline static std::size_t max_buffer_size = 7;

public:
    Action() {}
    virtual ~Action();
    virtual std::ostream& write_to_stream(std::ostream& stream) const = 0;

    template <typename Type>
    Action& operator<<(const Type& arg)
    {
        msg_stream_ << arg;
        return *this;
    }

    std::string message() const;

private:
    std::ostringstream msg_stream_;
};

class Pacman_action : public Action
{
public:
    explicit Pacman_action(const Pacman& pacman);
    virtual ~Pacman_action() override;
    int pacman_id() const;

private:
    const Pacman* pacman_;
};

class Move : public Pacman_action
{
public:
    inline constexpr static std::string_view label = "MOVE";

    Move(const Pacman& pacman, const Position& destination);
    virtual ~Move() override;
    virtual std::ostream& write_to_stream(std::ostream& stream) const override;

private:
    Position destination_;
};

class Speed : public Pacman_action
{
public:
    inline constexpr static std::string_view label = "SPEED";

    explicit Speed(const Pacman& pacman);
    virtual ~Speed() override;
    virtual std::ostream& write_to_stream(std::ostream& stream) const override;
};

class Switch : public Pacman_action
{
public:
    inline constexpr static std::string_view label = "SWITCH";

    explicit Switch(const Pacman& pacman, Pacman::Type new_type);
    virtual ~Switch() override;
    virtual std::ostream& write_to_stream(std::ostream& stream) const override;

private:
    Pacman::Type new_type_;
};

class Action_sequence : public Action
{
public:
    virtual ~Action_sequence();

    Action& add_action(std::unique_ptr<Action> action_uptr);

    template <typename Action, typename... Args>
    Action& add_action(Args&&... args)
    {
        auto action_uptr = std::make_unique<Action>(std::forward<Args>(args)...);
        Action& action_ref = *action_uptr;
        actions_.push_back(std::move(action_uptr));
        return action_ref;
    }

    inline const auto& actions() const { return actions_; }

    virtual std::ostream& write_to_stream(std::ostream& stream) const override;

private:
    std::vector<std::unique_ptr<Action>> actions_;
};

std::ostream& operator<<(std::ostream& stream, const Action_sequence& action_sequence);
