#pragma once

#ifndef LIB_STATES_CONTROLLER_INCLUDE_HPP__
#define LIB_STATES_CONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <mtypes/include/stack.hpp>
#include <mtypes/include/log.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib
{
	namespace scene
	{
		template <class T>
		class StatesController : public DataOnlyComponent
		{
		public:
			constexpr StatesController() noexcept = default;

			constexpr void start(const T& firstState) noexcept {
				assert_debug(m_statesStack.size() == 0, "You cannot call start if the stack is not empty");
				BeforeStart(firstState);
				push_state(firstState);
			}

			constexpr void push_state(const T& firstState) noexcept {
				if (m_statesStack.size() > 0) {
					StatePaused(m_statesStack.back());
				}
				m_statesStack.push_back(firstState);
				StatePushed(firstState);
			}

			constexpr void pop_state() noexcept {
				assert_debug(m_statesStack.size() > 0, "m_statesStack.size() is 0");
				StateFinished(m_statesStack.back());
				if (m_statesStack.size() > 1) {
					m_statesStack.pop_back();
					StateResumed(m_statesStack.back());
				} else {
					BeforeFinish(m_statesStack.back());
					m_statesStack.pop_back();
				}
			}

			constexpr void setState(const T& newState) {
				changeState(newState);
			}

			constexpr const T&currentState() const noexcept { return m_statesStack.back(); }

			emitter<const T&> StateFinished;
			emitter<const T&> StateStarted;
			emitter<const T&> StatePushed;
			emitter<const T&> StatePopped;
			emitter<const T&> StatePaused;
			emitter<const T&> StateResumed;
			emitter<const T&> BeforeStart;
			emitter<const T&> BeforeFinish;

		private:
			inline void changeState(const T& newState) {
				assert_debug(m_statesStack.size() != 0, "States stack size is 0");
				const T&oldState{ m_statesStack.back() };
				m_statesStack.pop_back();
				StateFinished(oldState);
				m_statesStack.push_back(newState);
				StateStarted(newState);
			}

			stack<T> m_statesStack;
		};
	}
}

#endif
