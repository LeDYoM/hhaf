#pragma once

#ifndef LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__

namespace lib
{
	template <typename Container>
	class AuxContainer final
	{
	public:
		constexpr AuxContainer() = default;
		
		constexpr Container &container() noexcept { return (*m_pContainer[0]); }
		constexpr const Container &container() const noexcept { return (*m_pContainer[0]); }

		constexpr Container &auxContainer() noexcept { return (*m_pContainer[1]); }
		constexpr const Container &auxContainer() const noexcept { return (*m_pContainer[1]); }

		constexpr void swap() noexcept {
			if (m_normalMode) {
				m_pContainer[0] = &m_container[1];
				m_pContainer[1] = &m_container[0];
				m_normalMode = false;
			} else {
				m_pContainer[0] = &m_container[0];
				m_pContainer[1] = &m_container[1];
				m_normalMode = true;
			}
		}

        constexpr void update() {
            if (!m_pendingActions.container().empty()) {
                m_pendingActions.swap();
                for (auto&& action : m_pendingActions.auxContainer()) {
                    action();
                }
                m_pendingActions.auxContainer().clear();
                m_pendingActions.swap();
            }
        }
    private:
		Container m_container[2];
		Container *m_pContainer[2] = { &m_container[0], &m_container[1] };
		bool m_normalMode{ true };
	};

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
