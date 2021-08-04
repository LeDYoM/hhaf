#ifndef HTYPES_VECTOR_STORAGE_INCLUDE_HPP
#define HTYPES_VECTOR_STORAGE_INCLUDE_HPP

#include <initializer_list>
#include <utility>
#include "memory/allocator.hpp"
#include "function.hpp"
#include "growpolicy.hpp"

namespace htps
{
/** Vector class to store a sequence of elements
 * This class is a container to store sequences of Ts. It can be resized.
 * Other use cases include search, replacement, etc...
 */
template <typename T, typename Allocator, typename GrowPolicy>
class vector_storage
{
private:
    size_type m_capacity{0U};
    size_type m_size{0U};
    T* m_buffer{nullptr};

public:
    using iterator        = T*;
    using const_iterator  = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;

    /**
     * @brief Default constructor
     */
    constexpr vector_storage() noexcept = default;

    /**
     * @brief Construct a new vector storage object with reserved memory.
     * The memory for the vector is allocated, but no construction is done
     * @param size Number of elements to reserve memory for
     */
    explicit vector_storage(size_type const size) :
        m_capacity{size},
        m_buffer{size > 0U ? Allocator::allocate(size) : nullptr}
    {}

    constexpr vector_storage(vector_storage const& other) = delete;
    constexpr vector_storage& operator=(vector_storage const& other) = delete;

    // Move constructor.
    constexpr vector_storage(vector_storage&& other) noexcept :
        m_capacity{std::exchange(other.m_capacity, 0U)},
        m_size{std::exchange(other.m_size, 0U)},
        m_buffer{std::exchange(other.m_buffer, nullptr)}
    {}

    /// Move assignment
    constexpr vector_storage& operator=(vector_storage&& other) noexcept
    {
        swap(other);
        return *this;
    }

    /// Destructor.
    inline ~vector_storage() noexcept
    {
        if (m_buffer)
        {
            Allocator::deallocate(m_buffer);
            m_buffer   = nullptr;
            m_size     = 0U;
            m_capacity = 0U;
        }
    }

    constexpr pointer at(const size_type index) noexcept
    {
        return (m_buffer + index);
    }

    constexpr const_pointer at(const size_type index) const noexcept
    {
        return (m_buffer + index);
    }

    constexpr const_pointer cat(const size_type index) const noexcept
    {
        return (m_buffer + index);
    }

    constexpr size_type capacity() const noexcept { return m_capacity; }
    constexpr size_type size() const noexcept { return m_size; }
    constexpr bool empty() const noexcept { return m_size == 0U; }
    constexpr iterator begin() noexcept { return m_buffer; }
    constexpr const_iterator begin() const noexcept { return m_buffer; }
    constexpr const_iterator cbegin() const noexcept { return m_buffer; }
    constexpr iterator end() noexcept { return m_buffer + m_size; }
    constexpr const_iterator end() const noexcept { return m_buffer + m_size; }
    constexpr const_iterator cend() const noexcept { return m_buffer + m_size; }

    constexpr void swap(vector_storage& other) noexcept
    {
        std::swap(m_buffer, other.m_buffer);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    constexpr void shrink_to_fit()
    {
        if (m_size < m_capacity)
        {
            auto tmp_buffer = m_buffer;
            m_capacity      = m_size;

            m_buffer = m_size > 0U ? Allocator::allocate(m_size) : nullptr;
            auto m_buffer_iterator = m_buffer;

            for (auto it = tmp_buffer; it != (tmp_buffer + m_size); ++it)
            {
                Allocator::construct(m_buffer_iterator, std::move(*it));
                Allocator::destruct(it);
                ++m_buffer_iterator;
            }
            Allocator::deallocate(tmp_buffer);
        }
    }

    constexpr void push_back(const T& value)
    {
        reserve(GrowPolicy::growSize(m_size));
        Allocator::construct(m_buffer + m_size, value);
        ++m_size;
    }

    constexpr void push_back(T&& value)
    {
        reserve(GrowPolicy::growSize(m_size));
        Allocator::construct(static_cast<T*>(m_buffer + m_size),
                             std::move(value));
        ++m_size;
    }

    template <typename... Args>
    constexpr void emplace_back(Args&&... args)
    {
        reserve(GrowPolicy::growSize(m_size));
        Allocator::construct(static_cast<T*>(m_buffer + m_size),
                             std::forward<Args>(args)...);
        m_size++;
    }

    constexpr void pop_back() noexcept
    {
        if (m_size > 0U)
        {
            Allocator::destruct(end() - 1U);
            --m_size;
        }
    }

    constexpr void reserve(const size_type capacity)
    {
        if (m_capacity < capacity)
        {
            vector_storage new_vector =
                vector_storage(static_cast<size_type>(capacity));

            for (auto iterator = begin(); iterator != end(); ++iterator)
            {
                new_vector.push_back(std::move(*iterator));
            }

            std::swap(*this, new_vector);
        }
    }
};

}  // namespace htps

#endif
