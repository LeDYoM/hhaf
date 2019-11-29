#pragma once

#ifndef MTYPES_ARRAY_INCLUDE_HPP
#define MTYPES_ARRAY_INCLUDE_HPP

#include <initializer_list>
#include "types.hpp"

#include <cassert>

namespace lib
{
template <class T, size_type array_size>
class array final
{
public:
    using iterator = T *;
    using const_iterator = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_t = size_type;
    using value_type = T;
    using const_value_type = const T;

    array() = default;
    array(const array &) = default;
    array(array &&) = default;
    array &operator=(const array &) = default;
    array &operator=(array &&) = default;

    constexpr array(std::initializer_list<value_type> iList) noexcept
    {
        for (decltype(iList.size()) i{0U}; i < iList.size() && i < array_size; ++i)
        {
            m_buffer[i] = std::move(*(iList.begin() + i));
        }
    }

    constexpr array(const T *const source, const size_type count) : array()
    {
        assert(array_size >= count);
        size_type index{ 0U };

        for (auto iterator = source; 
            iterator != (source + count);
            ++iterator)
        {
            m_buffer[index++] = *iterator;
        }
    }

    constexpr array(const const_iterator _begin, const const_iterator _end)
        : array{_begin, static_cast<size_type>(std::distance(_begin, _end))} {}

    constexpr void insert(const size_type index, value_type element) noexcept
    {
        if (index < array_size)
        {
            for (size_type i{array_size - 2U}; 
                i >= index && (i < static_cast<size_type>(-1));
                --i)
            {
                m_buffer[i + 1] = std::move(m_buffer[i]);
            }
            m_buffer[index] = std::move(element);
        }
    }

    constexpr reference operator[](const size_t index) noexcept { return m_buffer[index]; }
    constexpr const_reference operator[](const size_t index) const noexcept { return m_buffer[index]; }
    constexpr size_t size() const noexcept { return array_size; }
    constexpr bool empty() const noexcept { return array_size == 0U; }
    constexpr iterator begin() noexcept { return m_buffer; }
    constexpr const_iterator begin() const noexcept { return m_buffer; }
    constexpr iterator end() noexcept { return m_buffer + array_size; }
    constexpr const_iterator end() const noexcept { return m_buffer + array_size; }
    constexpr const_iterator cbegin() const noexcept { return begin(); }
    constexpr const_iterator cend() const noexcept { return end(); }
    constexpr reference front() noexcept { return *begin(); }
    constexpr reference back() noexcept { return m_buffer[array_size - 1U]; }
    constexpr const_reference front() const noexcept { return cbegin(); }
    constexpr const_reference back() const noexcept { return m_buffer[array_size > 0 ? (array_size - 1) : 0]; }
    constexpr const_reference cfront() const noexcept { return cbegin(); }
    constexpr const_reference cback() const noexcept { return back(); }

    constexpr bool operator==(const array& other) const
    {
        return std::equal(cbegin(), cend(), other.cbegin());
    }

private:
    T m_buffer[array_size];
};

template <typename T, size_type S>
using array_shared_pointers = array<sptr<T>, S>;

template <typename T, size_type S>
using array_unique_pointers = array<uptr<T>, S>;

template <typename T, size_type S>
using array_weak_pointers = array<wptr<T>, S>;

} // namespace lib

#endif
