#ifndef HTYPES_STACK_INCLUDE_HPP
#define HTYPES_STACK_INCLUDE_HPP

#include "types.hpp"
#include "vector.hpp"

namespace htps
{
template <typename T>
class stack
{
    vector<T> data_;

public:
    using iterator        = T*;
    using const_iterator  = const T*;
    using reference       = T&;
    using const_reference = const T&;

    constexpr stack() noexcept = default;
    explicit constexpr stack(const size_type size) : data_(size) {}
    constexpr stack(const stack& other)     = default;
    constexpr stack(stack&& other) noexcept = default;
    constexpr stack& operator=(const stack& other) = default;
    constexpr stack& operator=(stack&& other) noexcept = default;
    ~stack() noexcept                                  = default;

    constexpr size_type capacity() const noexcept { return data_.capacity(); }
    constexpr size_type size() const noexcept { return data_.size(); }
    constexpr bool empty() const noexcept { return data_.empty(); }
    constexpr T& back() noexcept { return data_.back(); }
    constexpr const T& cback() const noexcept { return data_.cback(); }

    constexpr void swap(stack& other) { std::swap(data_, other.data_); }

    template <typename... Args>
    constexpr void emplace_back(Args&&... args)
    {
        data_.emplace_back(std::forward<Args>(args)...);
    }

    constexpr void shrink_to_fit() { data_.shrink_to_fit(); }

    constexpr void push_back(const T& value) { data_.push_back(value); }

    constexpr void push_back(T&& value) { data_.push_back(std::move(value)); }

    constexpr void pop_back() noexcept { data_.pop_back(); }

    constexpr void clear() noexcept { data_.clear(); }

    template <class A>
    friend constexpr bool operator==(const stack<A>& lhs,
                                     const stack<A>& rhs) noexcept;

    template <class A>
    friend constexpr bool operator!=(const stack<A>& lhs,
                                     const stack<A>& rhs) noexcept;
};

template <class A>
constexpr bool operator==(const stack<A>& lhs, const stack<A>& rhs) noexcept
{
    return lhs.data_ == rhs.data_;
}

template <class A>
constexpr bool operator!=(const stack<A>& lhs, const stack<A>& rhs) noexcept
{
    return lhs.data_ != rhs.data_;
}
}  // namespace htps

#endif
