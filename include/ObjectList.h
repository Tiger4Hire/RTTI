#pragma once
#include "Button.h"
#include "TextLabel.h"
#include <memory>
#include <list>
#include <vector>
#include <gsl/gsl>

/**************************************************************************
 * While Object interface may be bad, this is where the real damage is done.
 * We "cast" away all knowledge of what the object is, just to make iteration
 * through the objects a "tiny-bit" easy. A very poor swap. Generally, you
 * should never "own" polymorphically. If this list was "non-owning" it would
 * fine.
 **************************************************************************/
template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>>
{
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>>
{
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

template <class Fn, class Tuple, size_t nth>
std::enable_if_t<!nth> apply_iterator(std::size_t idx, Fn&& fn, Tuple& t)
{
    Expects(idx == 0);
    fn(*std::get<nth>(t)++);
}

template <class Fn, class Tuple, size_t nth>
std::enable_if_t<nth> apply_iterator(std::size_t idx, Fn&& fn, Tuple& t)
{
    if (idx == nth)
        fn(*std::get<nth>(t)++);
    else if (nth > 0)
        apply_iterator<Fn, Tuple, nth - 1>(idx, std::forward<Fn>(fn), t);
}

template <class T, std::size_t... I>
auto make_begin(T& t, std::index_sequence<I...>)
{
    return std::make_tuple(std::begin(std::get<I>(t))...);
}

template <class... Args>
class VectorList
{
    using Storage = std::tuple<std::vector<Args>...>;
    using StorageIters = std::tuple<typename std::vector<Args>::iterator...>;
    static constexpr auto idxs = std::make_index_sequence<std::tuple_size_v<Storage>>{};
    Storage lists;
    std::vector<std::size_t> typeOrder;

public:
    template <class T>
    void emplace_back(T&& t)
    {
        using vectorT = std::vector<T>;
        static constexpr size_t index = Index<vectorT, Storage>::value;
        std::get<index>(lists).emplace_back(std::move(t));
        typeOrder.push_back(index);
    }
    void erase(int);

    template <class Fn>
    void visit(Fn&& fn)
    {
        StorageIters iters = make_begin(lists, idxs);
        constexpr auto size = std::tuple_size_v<StorageIters>;
        for (const auto idx : typeOrder)
            apply_iterator<Fn, StorageIters, size - 1>(idx, std::forward<Fn>(fn), iters);
    }
};

/*
template <class Fn>
void ObjectList::visit_unordered(Fn&& fn)
{
    for (auto& obj : buttons)
        fn(obj);
    for (auto& obj : labels)
        fn(obj);
}
*/
using ObjectList = VectorList<Button, TextLabel>;