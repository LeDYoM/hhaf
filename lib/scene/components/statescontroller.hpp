#pragma once

#ifndef LIB_STATES_CONTROLLER_INCLUDE_HPP
#define LIB_STATES_CONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <mtypes/include/stack.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib
{
	using Action = function<void()>;
	namespace scene
	{
		template <class T>
		class StatesControllerRaw
		{
		public:
			constexpr void update() 
            {
                if (!m_pendingActions.current().empty())
                {
                    for (auto action : m_pendingActions.current())
                    {
                        action();
                        m_pendingActions.remove_value(action);
                    }
                    m_pendingActions.update();
                }
			}

			constexpr void start(T firstState) noexcept 
            {
				assert_debug(m_statesStack.empty(), "You cannot call start if the stack is not empty");
                if (m_statesStack.empty())
                {
                    BeforeStart();
                    push_state(std::move(firstState));
                }
			}

			constexpr void push_state(T firstState) noexcept 
            {
				postAction([this, firstState = std::move(firstState)]() 
                {
					if (!m_statesStack.empty()) 
                    {
						StatePaused(m_statesStack.back());
					}
					StatePushed(firstState);
                    StateStarted(firstState);
					m_statesStack.push_back(std::move(firstState));
				});
			}

			constexpr void pop_state() noexcept 
            {
				postAction([this]() 
                {
					assert_debug(m_statesStack.size() > 0, "m_statesStack.size() is 0");
                    StateFinished(m_statesStack.back());
					StatePopped(m_statesStack.back());
					if (m_statesStack.size() > 1) 
                    {
						m_statesStack.pop_back();
						StateResumed(m_statesStack.back());
					}
					else 
                    {
						m_statesStack.pop_back();
						AfterFinish();
					}
				});
			}

			constexpr void setState(T newState) 
            {
				changeState(std::move(newState));
			}

            constexpr bool hasActiveState() const
            {
                return !m_statesStack.empty();
            }

			constexpr const T&currentState() const noexcept { return m_statesStack.cback(); }
			constexpr T&currentState() noexcept { return m_statesStack.back(); }

			emitter<const T&> StateFinished;
			emitter<const T&> StateStarted;
			emitter<const T&> StatePushed;
			emitter<const T&> StatePopped;
			emitter<const T&> StatePaused;
			emitter<const T&> StateResumed;
			emitter<>          BeforeStart;
			emitter<>		   AfterFinish;

		private:
			inline void changeState(T newState) 
            {
				postAction([this, newState = std::move(newState)]() 
                {
					assert_debug(m_statesStack.size() != 0, "States stack size is 0");
					const T&oldState{ m_statesStack.back() };
					m_statesStack.pop_back();
					StateFinished(oldState);
					StateStarted(newState);
					m_statesStack.push_back(std::move(newState));
				});
			}

			constexpr void postAction(Action action) {
				m_pendingActions.push_back(std::move(action));
			}

			stack<T> m_statesStack;
			LockableVector<Action> m_pendingActions;
		};

		template <typename T>
		class StatesController : public StatesControllerRaw<T>, public IComponent
		{
        public:
			void update() override
			{
				StatesControllerRaw<T>::update();
			}
		};
	}
}

#endif
