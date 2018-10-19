#pragma once

#ifndef LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP
#define LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP

#include "vector.hpp"
#include "function.hpp"

namespace lib
{
    /**
    * Vector that must not change during the iteration.

    *    This class encapsulates two vectors of T, providing a wrapper
    * to one of them to modify and doing the update in the other one.
    * The logic to hide the vectors internally is part of the provided
    * functionality.
    */
    template <class T>
    class LockableVector final
    {
    public:
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
        * Remove an element.
        * @param element The element to remove.
        */
        constexpr void remove_value(const T &element)
        {
            remove_cache_.push_back(element);
        }

        constexpr void update()
        {
            add_to_main_container();
            remove_from_containers();
        }

        constexpr void clear() noexcept
        {
            main_container_.clear();
        }

        constexpr const vector<T>& current() noexcept
        {
            update();
            return main_container_;
        }

        constexpr auto pending_add() noexcept
        {
            return addingCache_.size();
        }

        constexpr bool are_pending_adds() noexcept
        {
            return !addingCache_.empty();
        }

        constexpr auto pending_remove() noexcept
        {
            return remove_cache_.size();
        }

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
                c.remove_value(element);
            }
        }

        constexpr void remove_from_containers()
        {
            if (!remove_cache_.empty())
            {
                remove_cache_elements_from(main_container_);
                remove_cache_elements_from(remove_cache_);

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
