#pragma once

#include "grid/grid_types.hpp"
#include <ostream>
#include <vector>
#include <memory>

class Pacman;

class Action
{
public:
    Action() {}
    virtual ~Action();
    virtual std::ostream& write_to_stream(std::ostream& stream) const = 0;
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
    Move(const Pacman& pacman, const Position& destination);
    virtual ~Move() override;
    virtual std::ostream& write_to_stream(std::ostream& stream) const override;

private:
    Position destination_;
};

class Action_sequence : public Action
{
public:
    virtual ~Action_sequence();

    void add_action(std::unique_ptr<Action> action_uptr);

    template <typename Action, typename... Args>
    void add_action(Args&&... args)
    {
        actions_.push_back(std::make_unique<Action>(std::forward<Args>(args)...));
    }

    inline const auto& actions() const { return actions_; }

    virtual std::ostream& write_to_stream(std::ostream& stream) const override;

private:
    std::vector<std::unique_ptr<Action>> actions_;
};

std::ostream& operator<<(std::ostream& stream, const Action_sequence& action_sequence);
