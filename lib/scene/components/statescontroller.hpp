#pragma once

#ifndef LIB_STATES_CONTROLLER_INCLUDE_HPP__
#define LIB_STATES_CONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib
{
	namespace scene
	{
		template <class T>
		class StatesController : public DataOnlyComponent
		{
		public:
			constexpr StatesController(const T&initialState) noexcept : m_currentState{ initialState } {}
			constexpr StatesController(const T&initialState, function<void(const T&, const T&)> stateChangedCallback) noexcept
				: m_currentState{ initialState }, stateChanged{ std::move(stateChangedCallback) } {}

			virtual void onAttached() override {}

			void changeState(const T& newState) {
				const T&oldState{ m_currentState };
				m_currentState = newState;
				stateChanded(m_currentState, oldState);
			}

			/// Emit when the state changed. The new state and the previous state are sent
			emitter<const T&,const T&> stateChanged;
		private:
			T m_currentState;
		};
	}
}

#endif
