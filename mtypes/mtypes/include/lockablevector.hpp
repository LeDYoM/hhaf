#pragma once

#ifndef LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__

namespace lib
{
    /// Vector that must not change during the iteration.
    /**
    * This class encapsulates two vectors of T, providing a wrapper
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
        constexpr void push_back(const T &element) {
            m_supportContainer.push_back(element);
        }

        /**
        * Add a new element. Overload for rvalues.
        * @param element The new element.
        */
        constexpr void push_back(T &&element) {
            m_supportContainer.push_back(std::move(element));
        }

        /**
        * Create the new element in place.
        * @param args Arguments forwarded to the constructor of T.
        */
        template<typename ...Args>
        constexpr void emplace_back(Args&&... args) {
            m_supportContainer.emplace_back(std::forward<Args>(args)...);
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
        constexpr void update(function<bool(T &)> f) {
            addSupportContainerToMainContainer();
            if (!m_mainContainer.empty()) {
                bool isDirty{ false };
                for (T &element : m_mainContainer) {
                    if (!f(element)) {
                        element = T();
                        isDirty = true;
                    }
                }

                if (isDirty) {
                    m_mainContainer.remove_values(T());
                }
                addSupportContainerToMainContainer();
            }
        }

    private:
        constexpr void addSupportContainerToMainContainer() {
            if (!m_supportContainer.empty()) {
                m_mainContainer.insert(m_supportContainer);
                m_supportContainer.clear();
            }
        }

        vector<T> m_mainContainer;
        vector<T> m_supportContainer;
    };
}

#endif
