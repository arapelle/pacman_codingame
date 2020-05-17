#pragma once

#include <algorithm>

template <typename FunctorA, typename FunctorB>
class Associative_functor
{
public:
    inline Associative_functor(FunctorA first_fn, FunctorB second_fn)
        : first_functor(std::move(first_fn)), second_functor(std::move(second_fn))
    {}

    FunctorA first_functor;
    FunctorB second_functor;
};

template <typename FunctorA, typename FunctorB>
class Logical_or_functor : public Associative_functor<FunctorA, FunctorB>
{
    using Base = Associative_functor<FunctorA, FunctorB>;

public:
    using Base::Base;

    template<class... Args>
    inline bool operator()(Args&&... args)
    {
        return this->first_functor(std::forward<Args>(args)...) || this->second_functor(std::forward<Args>(args)...);
    }
};

template <typename FunctorA, typename FunctorB>
inline auto or_join(FunctorA&& first_fn, FunctorB&& second_fn)
{
    return Logical_or_functor<FunctorA, FunctorB>(std::forward<FunctorA>(first_fn), std::forward<FunctorB>(second_fn));
}

template <typename FunctorA, typename FunctorB>
class Logical_and_functor : public Associative_functor<FunctorA, FunctorB>
{
    using Base = Associative_functor<FunctorA, FunctorB>;

public:
    using Base::Base;

    template<class... Args>
    inline bool operator()(Args&&... args)
    {
        return this->first_functor(std::forward<Args>(args)...) && this->second_functor(std::forward<Args>(args)...);
    }
};

template <typename FunctorA, typename FunctorB>
inline auto and_join(FunctorA&& first_fn, FunctorB&& second_fn)
{
    return Logical_and_functor<FunctorA, FunctorB>(std::forward<FunctorA>(first_fn), std::forward<FunctorB>(second_fn));
}

template <typename FunctorA, typename FunctorB>
class Sequence_functor : public Associative_functor<FunctorA, FunctorB>
{
    using Base = Associative_functor<FunctorA, FunctorB>;

public:
    using Base::Base;

    template<class... Args>
    inline void operator()(Args&&... args)
    {
        this->first_functor(std::forward<Args>(args)...);
        this->second_functor(std::forward<Args>(args)...);
    }
};

template <typename FunctorA, typename FunctorB>
inline auto seq_join(FunctorA&& first_fn, FunctorB&& second_fn)
{
    return Sequence_functor<FunctorA, FunctorB>(std::forward<FunctorA>(first_fn), std::forward<FunctorB>(second_fn));
}
