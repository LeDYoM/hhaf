#pragma once

#ifndef LIB_STATES_CONTROLLER_INCLUDE_HPP__
#define LIB_STATES_CONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <mtypes/include/stack.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/include/core/log.hpp>
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
			constexpr void update() {
                m_pendingActions.update([](auto action) 
                {
					action();
                });
			}

			constexpr void start(T firstState) noexcept 
            {
				assert_debug(m_statesStack.size() == 0, "You cannot call start if the stack is not empty");
				BeforeStart(firstState);
				push_state(std::move(firstState));
			}

			constexpr void push_state(T firstState) noexcept 
            {
				postAction([this, firstState = std::move(firstState)]() 
                {
					if (m_statesStack.size() > 0) 
                    {
						StatePaused(m_statesStack.back());
					}
					StatePushed(firstState);
					m_statesStack.push_back(std::move(firstState));
				});
			}

			constexpr void pop_state() noexcept 
            {
				postAction([this]() 
                {
					assert_debug(m_statesStack.size() > 0, "m_statesStack.size() is 0");
					StatePopped(m_statesStack.back());
					if (m_statesStack.size() > 1) 
                    {
						m_statesStack.pop_back();
						StateResumed(m_statesStack.back());
					}
					else 
                    {
						BeforeFinish(m_statesStack.back());
						m_statesStack.pop_back();
						AfterFinish();
					}
				});
			}

			constexpr void setState(T newState) {
				changeState(std::move(newState));
			}

			constexpr const T&currentState() const noexcept { return m_statesStack.back(); }
			constexpr T&currentState() noexcept { return m_statesStack.back(); }

			emitter<const T&> StateFinished;
			emitter<const T&> StateStarted;
			emitter<const T&> StatePushed;
			emitter<const T&> StatePopped;
			emitter<const T&> StatePaused;
			emitter<const T&> StateResumed;
			emitter<const T&> BeforeStart;
			emitter<const T&> BeforeFinish;
			emitter<>		  AfterFinish;

		private:
			inline void changeState(T newState) {
				postAction([this, newState = std::move(newState)]() {
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
			constexpr void update() override final {
				StatesControllerRaw<T>::update();
			}
		};

        template <typename T>
        class StatesControllerActuator
        {
        public:
            virtual void onEnterState(const T&) {}
            virtual void onExitState(const T&) {}
            virtual void onPushedState(const T&) {}
            virtual void onPoppedState(const T&) {}
            virtual void onPausedState(const T&) {}
            virtual void onResumedState(const T&) {}
        };

        template <typename T>
        class StatesControllerActuatorRegister
        {
        public:
            void registerStatesControllerActuator(
                StatesController<T> &statesController,
                StatesControllerActuator<T> &statesControllerActuator) 
            {
                statesController.StateStarted.connect([&statesControllerActuator](const T&startedState) {
                    statesControllerActuator.onEnterState(startedState);
                });
                statesController.StateFinished.connect([&statesControllerActuator](const T&startedState) {
                    statesControllerActuator.onExitState(startedState);
                });
            }
        };
	}
}

#endif
