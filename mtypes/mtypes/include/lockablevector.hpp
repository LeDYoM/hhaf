#pragma once

#ifndef LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_LOCKABLE_VECTOR_CONTAINER_INCLUDE_HPP__

namespace lib
{
    template <class T>
    class LockableVector final
    {
    public:
        constexpr void push_back(const T &element) {
            m_supportContainer.push_back(element);
        }

        constexpr void push_back(T &&element) {
            m_supportContainer.push_back(std::move(element));
        }

        template<typename ...Args>
        constexpr void emplace_back(Args&&... args) {
            m_supportContainer.emplace_back(std::forward<Args>(args)...);
        }

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

        constexpr void addSupportContainerToMainContainer() {
            if (!m_supportContainer.empty()) {
                m_mainContainer.insert(m_supportContainer);
                m_supportContainer.clear();
            }
        }

    private:
        vector<T> m_mainContainer;
        vector<T> m_supportContainer;
    };
}

#endif
