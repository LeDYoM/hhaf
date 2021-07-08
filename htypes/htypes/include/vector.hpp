#ifndef HTYPES_VECTOR_INCLUDE_HPP
#define HTYPES_VECTOR_INCLUDE_HPP

//#define LOG_MODE
#include "debug_internal.hpp"

#include <initializer_list>
#include <utility>
#include "function.hpp"
#include "growpolicy.hpp"
#include "vector_storage.hpp"
#include "memory/allocator.hpp"

namespace htps
{
/**
 * @brief Vector class to store a sequence of elements.
 * This class is a container to store sequences of Ts. It can be resized.
 * Other use cases include search, replacement, etc...
 *
 * @tparam T Type of the contained element.
 * @tparam Allocator Allocator to be used by the vector
 * @tparam GrowPolicy Policy class to dinamically increment the capacity
 */
template <typename T,
          typename Allocator  = AllocatorType<T>,
          typename GrowPolicy = GrowPolicyUnary>
class vector final
{
    vector_storage<T, Allocator, GrowPolicy> base_;

public:
    using iterator        = T*;       /**< Iterator for the values */
    using const_iterator  = T const*; /**< Iterator pointing to const values */
    using reference       = T&;       /**< Reference to member */
    using const_reference = const T&; /**< Const reference to members */
    using value_type      = T;        /** Value of the contained member */
    using pointer         = T*;       /** Pointer to the contained member */
    using const_pointer   = T const*; /**< Pointer to constant value */

    /**
     * @brief Default constructor.
     * Sets all members to 0, nullptr or empty.
     */
    constexpr vector() noexcept = default;

    /**
     * @brief Construct a new vector object empty with reserved memory.
     * The memory for the vector is allocated, but no construction
     * of the elements is performed.
     *
     * @param size Expected size of the inner container
     */
    explicit constexpr vector(const size_type size) : base_(size) {}

    /**
     * @brief Constructor with reserved memory and copy from source.
     * This constructor takes a pointer and a number of elements
     * and constructs a vector from it.
     *
     * @param source Pointer to the first element of the
     * @param count Number of elements to copy.
     */
    constexpr vector(T const* const source, size_type const count) :
        base_(count)
    {
        reserve(count);
        for (auto iterator = source; iterator != (source + count); ++iterator)
        {
            // Construct by copy.
            emplace_back(*iterator);
        }
    }

    constexpr vector(std::initializer_list<value_type> ilist) noexcept :
        vector(ilist.begin(), ilist.size())
    {}

    constexpr vector(const const_iterator _begin, const const_iterator _end) :
        vector{_begin, static_cast<size_type>(std::distance(_begin, _end))}
    {}

    /**
     * @brief Copy constructor.
     * This constructor constructs a vector from another one.
     * The capacity of the resultant vector might be different
     * from the capacity of the source. The size will be the same.
     *
     * @param other Source vector to copy.
     */
    constexpr vector(const vector& other) :
        vector(other.begin(), other.begin() + other.size())
    {}

    // Move constructor.
    constexpr vector(vector&& other) noexcept : base_{std::move(other.base_)} {}

    /// Copy assignment.
    constexpr vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            clear();
            insert(other);
        }
        return *this;
    }

    /// Move assignment
    constexpr vector& operator=(vector&& other) noexcept
    {
        base_.swap(other.base_);
        return *this;
    }

    /// Destructor.
    inline ~vector() noexcept { clear(); }

    constexpr reference operator[](const size_type index) noexcept
    {
        assert(index < size());
        return *(base_.at(index));
    }

    constexpr const_reference operator[](const size_type index) const noexcept
    {
        assert(index < size());
        return *(base_.at(index));
    }

    constexpr size_type capacity() const noexcept { return base_.capacity(); }
    constexpr size_type size() const noexcept { return base_.size(); }
    constexpr bool empty() const noexcept { return base_.empty(); }
    constexpr iterator begin() noexcept { return base_.begin(); }
    constexpr const_iterator begin() const noexcept { return base_.begin(); }
    constexpr const_iterator cbegin() const noexcept { return base_.cbegin(); }
    constexpr iterator end() noexcept { return base_.end(); }
    constexpr const_iterator end() const noexcept { return base_.end(); }
    constexpr const_iterator cend() const noexcept { return base_.cend(); }

    constexpr T& back() noexcept
    {
        assert(size() > 0U);
        return *(base_.at(size() - 1U));
    }

    constexpr const T& back() const noexcept
    {
        assert(size() > 0U);
        return *(base_.at(size() - 1U));
    }

    constexpr const T& cback() const noexcept
    {
        assert(size() > 0U);
        return *(base_.cat(size() - 1U));
    }

    template <typename F>
    constexpr void for_each(F f)
    {
        if (!empty())
        {
            iterator current{begin()};
            do
            {
                f(*current);
            } while (++current != end());
        }
    }

    constexpr void swap(vector& other) noexcept { base_.swap(other.base_); }

    template <bool discard_order = true>
    constexpr iterator erase_values(const T& value, iterator start)
    {
        iterator result{start};
        checkRange(result);

        do
        {
            result = start;
            start  = erase_one<discard_order>(value, start);
        } while (start != end());

        return result;
    }

    template <bool discard_order = true>
    constexpr iterator erase_values(const T& value)
    {
        return erase_values<discard_order>(value, begin());
    }

    template <typename U, bool discard_order = true>
    constexpr iterator erase_one_imp(U&& v, iterator const start) noexcept
    {
        checkRange(start);

        if (cbegin() != cend())
        {
            // Find a node with the specified value
            iterator where_it_was{find(start, end(), std::forward<U>(v))};

            // If such a node is found erase it, if not,
            // return end() (result from find(...)).
            if (where_it_was != end())
            {
                // If the element to delete is not the last one
                if (where_it_was < end() - 1U)
                {
                    remove_iterator<discard_order>(where_it_was, end());
                }
                pop_back();
            }
            return where_it_was;
        }
        return end();
    }

    template <bool discard_order = true>
    constexpr iterator erase_iterator(iterator const where,
                                      iterator const _end) noexcept
    {
        // If such a node is found erase it, if not,
        // return end() (result from find(...)).
        if (where != _end)
        {
            // If the element to delete is not the last one
            if (std::distance(where, _end) > 0)
            {
                remove_element<discard_order>(where, _end);
            }
            pop_back();
        }
        return where;
    }

    using Predicate_t = function<bool(const T&)>;

    template <bool discard_order = true>
    constexpr iterator erase_if(Predicate_t condition, iterator start)
    {
        checkRange(start);

        if (cbegin() != cend())
        {
            // Find a node with the specified value
            return erase_iterator<discard_order>(
                find_if(start, end(), std::move(condition)), end());
        }
        return end();
    }

    /**
     * @brief Erase one element (the first one containing a specified)
     * value.
     *
     * @param value Value to search for in the vector.
     * @param start start iterator pointing to the first element
     * to look for.
     * @param discard_order If true, relative order after deleting will not
     * be taken into accound. If false, the order will remain the same.
     * Note that using true will keep iterators pointing to other elements,
     * except the deleted one and to the last one valid. Using false, only
     * the iterators to the one previous the one deleted will still be valid.
     * @return iterator Pointing to the element in the position where the
     * deleted element was. If the element was the last one or no element
     * with this value found, the iterator will be end().
     * @warning This method does not allocate or deallocate memory. And it
     * des not preserve the order. Actually, the deleted element will now
     * contain the previous last element.
     */
    template <bool discard_order = true>
    constexpr iterator erase_one(const T& value, iterator const start) noexcept
    {
        checkRange(start);

        if (begin() != end())
        {
            // Find a node with the specified value and erase it
            return erase_iterator<discard_order>(find(start, end(), value),
                                                 end());
        }
        return end();
    }

    template <bool discard_order = true>
    constexpr void remove_element(iterator const element,
                                  iterator const end) noexcept
    {
        if constexpr (discard_order)
        {
            // swap the element to delete with the last one
            std::swap(*element, *std::prev(end));
        }
        else
        {
            for (iterator it{element}; it != std::prev(end); ++it)
            {
                std::swap(*it, *(std::next(it)));
            }
        }
    }

    template <bool discard_order = true>
    constexpr iterator erase_one_index(size_type const index) noexcept
    {
        if (index < size())
        {
            return erase_one<discard_order>(*(begin() + index),
                                            (begin() + index));
        }

        return end();
    }

    template <bool discard_order = true>
    constexpr iterator erase_one(const T& value)
    {
        return erase_one<discard_order>(value, begin());
    }

    template <bool discard_order = true>
    constexpr iterator erase_if(Predicate_t condition)
    {
        return erase_if<discard_order>(std::move(condition), begin());
    }

    template <bool discard_order = true>
    constexpr iterator erase_all_if(Predicate_t condition, iterator start)
    {
        iterator result{start};
        do
        {
            result = start;
            start  = erase_if<discard_order>(condition, start);
        } while (start != end());

        return result;
    }

    template <bool discard_order = true>
    constexpr iterator erase_all_if(Predicate_t condition)
    {
        return erase_all_if<discard_order>(std::move(condition), begin());
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
                            const iterator end,
                            const T& element) const noexcept
    {
        checkRange(begin);
        checkRange(end);

        for (; (begin != end && !(*begin == element)); ++begin)
            ;
        return begin;
    }

    template <typename F>
    constexpr const_iterator cfind_if(const_iterator begin,
                                      const const_iterator end,
                                      F&& f) const noexcept
    {
        checkRange(begin);
        checkRange(end);

        for (; (begin != end && !(std::forward<F>(f)(*begin))); ++begin)
            ;
        return begin;
    }

    template <typename F>
    constexpr const_iterator cfind_if(F&& f) const noexcept
    {
        return cfind_if(cbegin(), cend(), std::forward<F>(f));
    }

    template <typename F>
    constexpr iterator find_if(iterator begin,
                               const const_iterator end,
                               F&& f) noexcept
    {
        checkRange(begin);
        checkRange(end);

        for (; (begin != end && !(std::forward<F>(f)(*begin))); ++begin)
            ;
        return begin;
    }

    template <typename F>
    constexpr iterator find_if(F&& f) noexcept
    {
        return find_if(begin(), cend(), std::forward<F>(f));
    }

    template <typename F>
    constexpr const_iterator find_if(const const_iterator begin,
                                     const const_iterator end,
                                     F&& f) const noexcept
    {
        return cfind_if(begin, end, std::forward<F>(f));
    }

    template <typename F>
    constexpr const_iterator find_if(F&& f) const noexcept
    {
        return cfind_if(cbegin(), cend(), std::forward<F>(f));
    }

    constexpr const_iterator cfind(const_iterator begin,
                                   const const_iterator end,
                                   const T& element) const noexcept
    {
        checkRange(begin);
        checkRange(end);

        for (; (begin != end && !(*begin == element)); ++begin)
            ;
        return begin;
    }

    constexpr const_iterator cfind(const T& element) const noexcept
    {
        return cfind(cbegin(), cend(), element);
    }

    constexpr const_iterator find(const T& element) const noexcept
    {
        return cfind(element);
    }

    constexpr void shrink_to_fit() { base_.shrink_to_fit(); }

    constexpr void push_back(const T& value) { base_.push_back(value); }

    constexpr void push_back(T&& value) { base_.push_back(std::move(value)); }

    constexpr void emplace_back() { base_.emplace_back(); }

    template <typename... Args>
    constexpr void emplace_back(Args&&... args)
    {
        base_.emplace_back(std::forward<Args>(args)...);
    }

    constexpr void insert(const vector& other)
    {
        // TODO: Optimize
        if (!other.empty())
        {
            reserve(size() + other.size());
            for (const auto& element : other)
            {
                emplace_back(element);
            }
        }
    }

    constexpr void insert(vector&& other)
    {
        // TODO: Optimize
        reserve(size() + other.size());
        for (auto&& element : std::move(other))
        {
            emplace_back(std::move(element));
        }
    }

    constexpr vector& operator+=(const vector& other)
    {
        insert(other);
        return *this;
    }

    constexpr vector& operator+=(vector&& other)
    {
        insert(std::move(other));
        return *this;
    }

    constexpr void pop_back() noexcept { base_.pop_back(); }

    constexpr void reserve(const size_type capacity)
    {
        base_.reserve(capacity);
    }

    /**
     * @brief Resize the inner container of this vector
     * @note This function affects the size of the vector it might
     * leave the inner reserved memory untouched.
     * @note If the size of the vector is equal to the parameter, this
     * function will do nothing..
     *
     * @param new_size New expected size of the vector.
     */
    constexpr void resize(size_type const new_size)
    {
        // Delete to shrink
        while (size() > new_size)
        {
            pop_back();
        }

        // Append the necessary default constructed elements
        while (size() < new_size)
        {
            emplace_back();
        }
    }

    /**
     * @brief Delete all elements in the vector. but maintains the inner
     * reserved memory unmodified.
     */
    constexpr void clear() noexcept
    {
        while (size() > 0U)
        {
            pop_back();
        }
    }

    /**
     * @brief Check that this iterator is valid. This function is for debug
     * purposes
     * @param it Const iterator to check
     */
    constexpr void checkRange([[maybe_unused]] const const_iterator it) const
    {
        assert(it >= begin());
        assert(it <= end());
    }
};

template <class A>
constexpr bool operator==(const vector<A>& lhs, const vector<A>& rhs) noexcept
{
    // Comparing with yourself returns true.
    if (&lhs == &rhs)
    {
        return true;
    }
    // If the vectors have different sizes, they are different
    else if (lhs.size() != rhs.size())
    {
        return false;
    }
    else
    {
        for (auto lhs_iterator = lhs.cbegin(), rhs_iterator = rhs.cbegin();
             lhs_iterator != lhs.cend(); ++lhs_iterator, ++rhs_iterator)
        {
            if (!(*lhs_iterator == *rhs_iterator))
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

template <typename T>
using vector_shared_pointers = vector<sptr<T>>;

template <typename T>
using vector_unique_pointers = vector<uptr<T>>;

template <typename T>
using vector_weak_pointers = vector<wptr<T>>;
}  // namespace htps

#endif
