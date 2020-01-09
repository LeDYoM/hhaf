#pragma once

#ifndef MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP
#define MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP

#include "vector.hpp"
#include "function.hpp"

namespace lib
{
    /**
    * This class encapsulates the functionality of a vector with deferred operations.
    * This class encapsulates 3 vectors<T>, providing a wrapper
    * to add and remove elements without modifying the main vector.
    * To access to the modifications, the user must call one of the available
    * methods to do that. The user may also access the non updated data.
    * The logic to hide the vectors internally is part of the provided
    * functionality.
    */
    template <class T>
    class LockableVector final
    {
    public:
        using iterator = typename vector<T>::iterator;
        using const_iterator = typename vector<T>::const_iterator;
        using reference = typename vector<T>::reference;
        using const_reference = typename vector<T>::const_reference;
        using value_type = typename vector<T>::value_type;
        using pointer = typename vector<T>::pointer;

        /**
        * Add a new element. Overload for const references.
        * @param element The new element.
        */
        constexpr void push_back(const T &element) 
        {
            addingCache_.push_back(element);
        }

        /**
        * Add a new element. Overload for rvalues.
        * @param element The new element.
        */
        constexpr void push_back(T &&element)
        {
            addingCache_.push_back(std::move(element));
        }

        /**
        * Create the new element in place.
        * @param args Arguments forwarded to the constructor of T.
        */
        template<typename ...Args>
        constexpr void emplace_back(Args&&... args) 
        {
            addingCache_.emplace_back(std::forward<Args>(args)...);
        }

        /**
        * Remove an element. Overload for const references.
        * @param element The element to remove.
        */
        constexpr void erase_value(const T &element)
        {
            remove_cache_.push_back(element);
        }

        /**
        * Remove an element. Overload for rvalues
        * @param element The element to remove.
        */
        constexpr void erase_values(T &&element)
        {
            remove_cache_.push_back(std::move(element));
        }

        /**
        * Explicitly call this method to force an update
        * (adding and removing values) to the container.
        */
        constexpr void update()
        {
            add_to_main_container();
            remove_from_containers();
        }

        /**

        */
        constexpr void swap()
        {
            main_container_.clear();
            update();
        }

        /**
        * Clear all containers, no pending adds or removes after that.
        */
        constexpr void clear()
        {
            main_container_.clear();
            addingCache_.clear();
            remove_cache_.clear();
        }

        /**
        * Retrieve a reference to the internal main container.
        * @return lvalue reference to the main container.
        */
        constexpr const vector<T>& deferred_current() const noexcept
        {
            return main_container_;
        }

        /**
        * Get a copy 
        */
        constexpr vector<T> next() const
        {
            LockableVector<T> temp(*this);
            return temp.current();
        }

        /**
        * Retrieve a constant reference to the updated internal main container.
        * @return const lvalue reference to the updated main container.
        */
        constexpr const vector<T>& current() noexcept
        {
            update();
            return main_container_;
        }

        /**
        * Retrieve the number of pending elements to be added.
        * @return The number of elements.
        */
        constexpr size_type pending_add() noexcept
        {
            return addingCache_.size();
        }

        /**
        * Ask if there is any number of elements pending to be added.
        * @return true or false
        */
        constexpr bool are_pending_adds() noexcept
        {
            return !addingCache_.empty();
        }

        /**
        * Retrieve the number of pending elements to be added.
        * @return The number of elements.
        */
        constexpr auto pending_remove() noexcept
        {
            return remove_cache_.size();
        }

        /**
        * Ask if there is any number of elements pending to be removed.
        * @return true or false
        */
        constexpr bool are_pending_removes() noexcept
        {
            return !remove_cache_.empty();
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
            if (!remove_cache_.empty())
            {
                remove_cache_elements_from(main_container_);
                remove_cache_.clear();
            }
        }

        constexpr void add_to_main_container() 
        {
            if (!addingCache_.empty()) 
            {
                main_container_.insert(addingCache_);
                addingCache_.clear();
            }
        }

        vector<T> main_container_;
        vector<T> addingCache_;
        vector<T> remove_cache_;
        bool locked_{ false };
    };
}

#endif
