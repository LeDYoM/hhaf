#pragma once

#ifndef LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__

namespace lib
{
    template <class T>
    class LockableVector
    {
    public:
        constexpr void push_back(const sptr<T>&element) {
            m_supportContainer.push_back(element);
        }

        template<typename ...Args>
        constexpr void emplace_back(Args&&... args) {
            m_supportContainer.emplace_back(msptr<T>(std::forward<Args>(args)...));
        }

        constexpr void update(function<bool(sptr<T> &)> f) {
            addSupportContainerToMainContainer();
            if (!m_mainContainer.empty()) {
                bool isDirty{ false };
                for (sptr<T> &element : m_mainContainer) {
                    if (!f(element)) {
                        element.reset();
                        isDirty = true;
                    }
                }

                if (isDirty) {
                    m_mainContainer.remove_values(nullptr);
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
        vector<sptr<T>> m_mainContainer;
        vector<sptr<T>> m_supportContainer;
    };
}

#endif
