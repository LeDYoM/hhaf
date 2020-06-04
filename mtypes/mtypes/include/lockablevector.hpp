#pragma once

#ifndef MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP
#define MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP

#include "vector.hpp"
#include "function.hpp"
#include "algoutils.hpp"

namespace mtps
{
/**
 * @brief This class encapsulates the functionality of a vector with deferred
 * operations. to add and remove elements without modifying the main vector.
 * This class encapsulates 3 vectors<T>, providing a wrapper to access to the
 * modifications, the user must call one of the available methods to do that.
 * The user may also access the non updated data. The logic to hide the vectors
 * internally is part of the provided functionality.
 * @tparam T
 */
template <class T>
class LockableVector final
{
public:
    using iterator        = typename vector<T>::iterator;
    using const_iterator  = typename vector<T>::const_iterator;
    using reference       = typename vector<T>::reference;
    using const_reference = typename vector<T>::const_reference;
    using value_type      = typename vector<T>::value_type;
    using pointer         = typename vector<T>::pointer;

    /**
     * @brief Add a new element. Overload for const references.
     * @param element The new element.
     */
    constexpr void push_back(const T& element)
    {
        addingCache_.push_back(element);
    }

    /**
     * @brief Add a new element. Overload for rvalues.
     * @param element The new element.
     */
    constexpr void push_back(T&& element)
    {
        addingCache_.push_back(std::move(element));
    }

    /**
     * @brief Create the new element in place.
     *
     * @tparam Args Types of the arguments
     * @param args Arguments forwarded to the constructor of T.
     */
    template <typename... Args>
    constexpr void emplace_back(Args&&... args)
    {
        addingCache_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Remove an element. Overload for const references.
     * @param element The element to remove.
     */
    constexpr void erase_value(const T& element)
    {
        remove_cache_.push_back(element);
    }

    /**
     * @brief Remove an element. Overload for rvalues
     * @param element The element to remove.
     */
    constexpr void erase_values(T&& element)
    {
        remove_cache_.push_back(std::move(element));
    }

    /**
     * @brief Update method
     * Explicitly call this method to force an update (adding and removing
     * values) to the container.
     */
    constexpr void update()
    {
        add_to_main_container();
        remove_from_containers();
    }

    constexpr void swap()
    {
        main_container_.clear();
        update();
    }

    /**
     * @brief Clear all containers, no elements, no pending adds and no pending
     * removes after that.
     */
    constexpr void clear()
    {
        main_container_.clear();
        addingCache_.clear();
        remove_cache_.clear();
    }

    /**
     * @brief Retrieve a reference to the internal main container.
     * @return const vector<T>& lvalue reference to the main container.
     */
    constexpr const vector<T>& deferred_current() const noexcept
    {
        return main_container_;
    }

    /**
     * @brief Get a copy
     * @return constexpr vector<T>
     */
    constexpr vector<T> next() const
    {
        LockableVector<T> temp(*this);
        return temp.current();
    }

    /**
     * @brief Retrieve a constant reference to the updated internal main
     * container.
     * @return constexpr const vector<T>& const lvalue reference to the updated
     * main container.
     */
    constexpr const vector<T>& current() noexcept
    {
        update();
        return main_container_;
    }

    /**
     * @brief Retrieve the number of pending elements to be added.
     * @return constexpr size_type The number of elements.
     */
    constexpr size_type pending_add() const noexcept
    {
        return addingCache_.size();
    }

    /**
     * @brief Ask if there is any number of elements pending to be added.
     * @return true
     * @return false
     */
    constexpr bool are_pending_adds() const noexcept
    {
        return !addingCache_.empty();
    }

    /**
     * @brief Retrieve the number of pending elements to be added.
     * @return constexpr auto The number of elements.
     */
    constexpr auto pending_remove() const noexcept
    {
        return remove_cache_.size();
    }

    /**
     * @brief Ask if there is any number of elements pending to be removed.
     * @return true
     * @return false
     */
    constexpr bool are_pending_removes() const noexcept
    {
        return !remove_cache_.empty();
    }

    /**
     * @brief Automatically perform an update of the elements of the current
     * container using a functor. The functor will be called once per element in
     * the current container after updating the pending elements to add and
     * remove.
     *
     * @tparam F Forwarding reference of type of the functor passed as parameter
     * @param f Functor to be used for each element
     */
    template <typename F>
    void performUpdate(F&& f)
    {
        update();

        for_each_all(main_container_, [f](auto& element) { f(element); });

        update();
    }

private:
    template <typename Container>
    constexpr void remove_cache_elements_from(Container& c)
    {
        for (const auto& element : remove_cache_)
        {
            c.erase_one(element);
        }
    }

    constexpr void remove_from_containers()
    {
        if (are_pending_removes())
        {
            remove_cache_elements_from(main_container_);
            remove_cache_.clear();
        }
    }

    constexpr void add_to_main_container()
    {
        if (are_pending_adds())
        {
            main_container_.insert(addingCache_);
            addingCache_.clear();
        }
    }

    vector<T> main_container_;
    vector<T> addingCache_;
    vector<T> remove_cache_;
};
}  // namespace mtps

#endif
