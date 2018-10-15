#pragma once

#ifndef LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__

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
            current().push_back(element);
        }

        /**
        * Add a new element. Overload for rvalues.
        * @param element The new element.
        */
        constexpr void push_back(T &&element)
        {
            current().push_back(std::move(element));
        }

        /**
        * Create the new element in place.
        * @param args Arguments forwarded to the constructor of T.
        */
        template<typename ...Args>
        constexpr void emplace_back(Args&&... args) 
        {
            current().emplace_back(std::forward<Args>(args)...);
        }

        /**
        * Update function.
        * This function must be called by the user with a callable object returning
        * a bool. It first adds the container avaiable to the user to the internal one,
        * then process the vector with f. All elements whose f(T) returns false,
        * will be set to T() and deleted afterwards.
        * Finally adds the container available to the user in the internal again.
        * New values will be processed the next call to update.
        * @param f A callable object receiving a T& as parameter and returning a bool
        */
        constexpr void update(function<bool(T &)> f)
        {
            addSupportContainerToMainContainer();
            if (!m_mainContainer.empty()) 
            {
                lock();
                updateInternal(f);
                unlock();
                addSupportContainerToMainContainer();
            }
        }

        constexpr void clear()
        {
            m_mainContainer.clear();
            m_supportContainer.clear();
        }

        constexpr const vector<T>& ccurrent() const noexcept
        {
            return m_locked ? m_supportContainer : m_mainContainer;
        }

        constexpr bool lock() noexcept
        {
            return setLock(true);
        }

        constexpr bool unlock() noexcept
        {
            return setLock(false);
        }

    private:

        constexpr bool setLock(const bool lock) noexcept
        {
            const bool wasLocked{ m_locked };
            m_locked = lock;
            return wasLocked;
        }

        constexpr void updateInternal(function<bool(T &)> f)
        {
            bool isDirty{ false };
            for (T &element : m_mainContainer) {
                if (!f(element)) {
                    element = T();
                    isDirty = true;
                }
            }

            if (isDirty)
            {
                m_mainContainer.remove_values(T());
            }
        }

        constexpr vector<T>& current() noexcept
        {
            return m_locked ? m_supportContainer : m_mainContainer;
        }

        constexpr void addSupportContainerToMainContainer() 
        {
            if (!m_supportContainer.empty()) 
            {
                m_mainContainer.insert(m_supportContainer);
                m_supportContainer.clear();
            }
        }

        vector<T> m_mainContainer;
        vector<T> m_supportContainer;
        bool m_locked{ false };
    };
}

#endif
