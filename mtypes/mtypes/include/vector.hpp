#pragma once

#ifndef MTYPES_VECTOR_INCLUDE_HPP
#define MTYPES_VECTOR_INCLUDE_HPP

//#define LOG_MODE
#include "debug_internal.hpp"

#include <initializer_list>
#include <utility>
#include "allocator.hpp"
#include "function.hpp"
#include "growpolicy.hpp"

namespace lib
{
    /** Vector class to store a sequence of elements
    * This class is a container to store sequences of Ts. It can be resized.
    * Other use cases include search, replacement, etc...
    */
    template <typename T, typename Allocator = AllocatorMallocFree<T>, typename GrowPolicy = GrowPolicyUnary>
    class  vector final
    {
    public:
        using iterator = T * ;
        using const_iterator = const T*;
        using reference = T & ;
        using const_reference = const T&;
        using value_type = T;
        using pointer = T * ;
        using const_pointer = const T*;

        // Constructors. ////////////////////////////////////////////////////////////

        /// Default constructor.
        /// Sets all members to 0 nullptr or empty.
        constexpr vector() noexcept {}

        /// Constructor for empty container with reserved memory.
        /// The memory for the vector is allocated, but no construction
        /// is done.
        /// @param size Number of elements to reserve memory for.
        explicit constexpr vector(const size_type size) : m_capacity{ size }, m_size{ },
            m_buffer{ size > 0U ? Allocator::allocate(size) : nullptr } {}

        /**
         * @brief Constructor.
         * This constructor takes a pointer and a number of elements
         * and constructs a vector from it.
         * @param source Pointer to the first element of the
         *  memory to copy.
         * @param count Number of elements to copy.
         */
        constexpr vector(const T*const source, const size_type count)
            : vector(count)
        {
            assert(m_capacity >= count);

            for (auto iterator = source; iterator != (source + count); ++iterator)
            {
                // Construct by copy.
                push_back(*iterator);
            }
        }

        constexpr vector(std::initializer_list<value_type> ilist) noexcept
            : vector(ilist.begin(), ilist.size()) { }

        constexpr vector(const_iterator _begin, const_iterator _end)
            : vector{ _begin, static_cast<size_type>(std::distance(_begin, _end)) } { }

        // Big five. ////////////////////////////////////////////////////

        /**
         * @brief Copy constructor.
         * This constructor constructs a vector from another one.
         * The capacity of the resultant vector might be different
         * from the capacity of the source. The size will be the same.
         * @param other Source vector to copy.
         */
        constexpr vector(const vector&other)
            : vector(other.m_buffer, other.m_size) { }

        // Move constructor.
        constexpr vector(vector&&other) noexcept
            : m_capacity{ std::exchange(other.m_capacity, 0U) },
            m_size{ std::exchange(other.m_size, 0U) },
            m_buffer{ std::exchange(other.m_buffer, nullptr) } { }

        /// Copy assignment.
        constexpr vector& operator=(const vector&other)
        {
            if (this != &other)
            {
                // TODO: Optimize. Do not allocate memory if not necessary.
                *this = vector(other);
            }
            return *this;
        }

        /// Move assignment
        constexpr vector& operator=(vector&&other) noexcept
        {
            swap(other);
            return *this;
        }

        /// Destructor.
        inline ~vector() noexcept
        {
            if (m_buffer)
            {
                clear();
                Allocator::deallocate(m_buffer);
				m_buffer = nullptr;
				m_size = 0U;
				m_capacity = 0U;
            }
        }

        constexpr reference operator[](const size_type index) noexcept
        {
            assert(index < m_size);
            return *(m_buffer + index);
        }
        constexpr const_reference operator[](const size_type index) const noexcept
        {
            assert(index < m_size);
            return *(m_buffer + index);
        }

        constexpr size_type capacity() const noexcept { return m_capacity; }
        constexpr size_type size() const noexcept { return m_size; }
        constexpr bool empty() const noexcept { return m_size == 0U; }
        constexpr iterator begin() noexcept { return m_buffer; }
        constexpr const_iterator begin() const noexcept { return m_buffer; }
        constexpr const_iterator cbegin() const noexcept { return begin(); }
        constexpr iterator end() noexcept { return m_buffer + m_size; }
        constexpr const_iterator end() const noexcept { return m_buffer + m_size; }
        constexpr const_iterator cend() const noexcept { return end(); }

        constexpr T& back() noexcept
        {
            assert(m_size > 0U);
            return *(end() - 1U);
        }

        constexpr const T& back() const noexcept
        {
            assert(m_size > 0U);
            return *(end() - 1U);
        }

        constexpr const T& cback() const noexcept
        {
            assert(m_size > 0U);
            return *(cend() - 1U);
        }

        constexpr void for_each(const function<void(const T&)> f)
        {
            if (!empty())
            {
                iterator current{ begin() };
                do
                {
                    f(*current);
                } while (++current != end());
            }
        }

        constexpr void swap(vector& other) noexcept
        {
            std::swap(m_buffer, other.m_buffer);
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
        }

        constexpr size_type index_from_iterator(const const_iterator it_) const noexcept
        {
            size_type i{0U};
            for (const_iterator it(cbegin()); it != cend(); ++it, ++i)
            {
                if (it == it_)
                {
                    return i;
                }
            }
            return m_size;
        }

        //TO DO: Optimize
        constexpr iterator erase_values(const T&value, iterator start) 
        {
            iterator result { start };
            checkRange(result);

            do
            {
                result = start;
                start = erase_one(value, start);
            } while (start != end());

            return result;
        }

        constexpr iterator erase_values(const T&value)
        {
            return erase_values(value, begin());
        }

        constexpr iterator erase_if(function<bool(const T&)> condition, iterator start) 
        {
            // Find a node where the condition is true.
            iterator where_it_was{ find_if(start, end(), condition) };

            // If such a node is found erase it, if not,
            // return end() (result from find_if(...)).
            if (where_it_was != end())
            {
                // If the element to delete is not the last one
                if (where_it_was < end() - 1U)
                {
                    // swap the element to delete with the last one
                    std::swap(*where_it_was, back());
                }
                pop_back();
            }
            return where_it_was;
        }

        /**
         * @brief Erase one element (the first one containing a specified)
         * value.
         * @param value [in] Value to search for in the vector.
         * @param value [in] start iterator pointing to the first element
         *  to look for.
         * @return iterator Pointing to the element in the position where the
         * deleted element was. If the element was the last one or no element
         * with this value found, the iterator will be end().
         */
        constexpr iterator erase_one(const T& value, iterator start)
        {
            checkRange(start);
            if (begin() != end())
            {
                // Find a node with the specified value
                iterator where_it_was{ find(start, end(), value) };

                // If such a node is found erase it, if not,
                // return end() (result from find(...)).
                if (where_it_was != end())
                {
                    // If the element to delete is not the last one
                    if (where_it_was < end() - 1U)
                    {
                        // swap the element to delete with the last one
                        std::swap(*where_it_was, back());
                    }
                    pop_back();
                }
                return where_it_was;
            }
            return end();
        }

        constexpr iterator erase_one(const T& value)
        {
            return erase_one(value, begin());
        }

        constexpr iterator erase_if(function<bool(const T&)> condition) 
        {
            return erase_if(std::move(condition), begin());
        }

        constexpr iterator erase_all_if(function<bool(const T&)> condition, iterator start) 
        {
            iterator result { start };
            do
            {
                result = start;
                start = erase_if(condition, start);
            } while (start != end());

            return result;
        }

        constexpr iterator erase_all_if(function<bool(const T&)> condition) 
        {
            return erase_all_if(condition, begin());
        }

        constexpr const_iterator find_first_of(const vector& other) const noexcept
        {
            for (auto it(begin()); it != end(); ++it)
            {
                if (other.find(*it) != other.end())
                {
                    return it;
                }
            }
            return end();
        }

        constexpr iterator find(iterator begin,
            const iterator end, const T&element) const noexcept 
        {
            checkRange(begin);
            checkRange(end);

            for (;(begin != end && !(*begin == element)); ++begin);
            return begin;
        }

        constexpr iterator find_if(iterator begin,
            const iterator end, function<bool(const T&)> f) const noexcept
        {
            checkRange(begin);
            checkRange(end);

            for (;(begin != end && !(f(*begin))); ++begin);
            return begin;
        }

        constexpr const_iterator cfind(const_iterator begin,
            const const_iterator end, const T&element) const noexcept 
        {
            checkRange(begin);
            checkRange(end);

            for (;(begin != end && !(*begin == element)); ++begin);
            return begin;
        }

        constexpr const_iterator cfind(const T&element) const noexcept
        {
            return cfind(cbegin(), cend(), element);
        }

        constexpr const_iterator find(const T&element) const noexcept
        {
            return cfind(element);
        }

        constexpr void shrink_to_fit() 
        {
            if (m_size < m_capacity) 
            {
                auto tmp_buffer = m_buffer;
                m_capacity = m_size;

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
			LOG("vector::push_back(const T&) --- m_size before: " << m_size);

            reserve(GrowPolicy::growSize(m_size));
            Allocator::construct(m_buffer + m_size, value);
            ++m_size;

			LOG("vector::push_back(const T&) --- m_size after: " << m_size);
		}

        constexpr void push_back(T&& value) 
        {
            LOG("vector::push_back(T&&) --- m_size before: " << m_size);

            reserve(GrowPolicy::growSize(m_size));
            Allocator::construct(m_buffer + m_size, std::move(value));
            ++m_size;

            LOG("vector::push_back(T&&) --- m_size after: " << m_size);
        }

        template<typename ...Args>
        constexpr void emplace_back(Args&&... args)
        {
            LOG("vector::emplace_back() --- m_size before: " << m_size);

            reserve(GrowPolicy::growSize(m_size));
            Allocator::construct(m_buffer + m_size, std::forward<Args>(args)...);
            m_size++;
            LOG("vector::emplace_back() --- m_size before: " << m_size);
        }

        constexpr void insert(const vector &other)
        {
            //TODO: Optimize
            if (!other.empty())
            {
                reserve(m_size + other.m_size);
                for (const auto& element : other)
                {
                    push_back(element);
                }
            }
        }

        constexpr void insert(vector &&other)
        {
            //TODO: Optimize
            reserve(m_size + other.m_size);
            for (auto&& element : other)
            {
                push_back(std::move(element));
            }
        }

        constexpr vector& operator+=(const vector &other)
        {
            insert(other);
            return *this;
        }

        constexpr vector& operator+=(vector &&other)
        {
            insert(std::move(other));
            return *this;
        }

        constexpr void pop_back() noexcept
        {
            LOG("vector::pop_back() --- m_size before: " << m_size);
            if (m_size > 0U)
            {
                Allocator::destruct(end()-1U);
                --m_size;
            }
            LOG("vector::pop_back() --- m_size after: " << m_size);
        }

        constexpr void reserve(const size_type capacity)
        {
            if (m_capacity < capacity) 
            {
                vector new_vector = vector(static_cast<size_type>(capacity));
                
                for (auto iterator = begin(); iterator != end(); ++iterator)
                {
                    new_vector.push_back(std::move(*iterator));
                }

                std::swap(*this, new_vector);
            }
        }

        constexpr void resize(const size_type size)
        {
            if (size != m_size)
            {
                // Delete to shrink
                while (m_size > size)
                {
                    pop_back();
                }

                // Append the necessary
                while (m_size < size)
                {
                    emplace_back();
                }
            }
        }

        constexpr void clear() noexcept
        {
            while (m_size > 0U)
            {
                pop_back();
            }
        }

        constexpr void checkRange(const iterator it) const
        {
            assert(it >= begin());
            assert(it <= end());
        }

        constexpr void checkRange(const const_iterator it) const
        {
            assert(it >= cbegin());
            assert(it <= cend());
        }

	private:
        size_type m_capacity{0U};
        size_type m_size{0U};
        T* m_buffer{nullptr};
    };

    template <class A>
    constexpr bool operator==(const vector<A>& lhs, const vector<A>& rhs) noexcept 
    {
        // Comparing agains yourself is true.
        if (&lhs == &rhs)
        {
            return true;
        }
        else if (lhs.size() != rhs.size())
        {
            return false;
        }
        else 
        {
            for (auto lhs_iterator = lhs.cbegin(), rhs_iterator = rhs.cbegin();
                lhs_iterator != lhs.cend() && rhs_iterator != rhs.cend();
                ++lhs_iterator, ++rhs_iterator) 
            {
                if (*lhs_iterator != *rhs_iterator)
                {
                    return false;
                }
            }
            return true;
        }
    }

    template <class A>
    constexpr bool operator!=(const vector<A>& lhs, const vector<A>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    class str;
    template <typename T>
    str &operator<<(str &str_in, const vector<T>& data)
    {
        str_in << "[";
        for (auto it = data.cbegin(); it != data.cend(); ++it)
        {
            str_in << *it;
            if (data.size() > 1U && it != data.cend() - 1U)
            {
                str_in << ",";
            }
        }
        str_in << "]";
        return str_in;
    }

    template <typename T>
    using vector_shared_pointers = vector<sptr<T>>;

    template <typename T>
    using vector_unique_pointers = vector<uptr<T>>;

    template <typename T>
    using vector_weak_pointers = vector<wptr<T>>;
}

#endif
