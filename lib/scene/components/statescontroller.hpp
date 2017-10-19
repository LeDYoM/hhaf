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

			constexpr void setState(const T& newState)
			{
				changeState(newState);
			}

			inline const T&currentState() const noexcept { return m_currentState; }
			inline firstChangeCompleted() const noexcept { return m_firstStateChangedCompleted; }
			/// Emit when the state changed. The new state and the previous state are sent
			emitter<const T&,const T&> stateChanged;
		private:
			inline void changeState(const T& newState) {
				const T oldState{ m_currentState };
				m_currentState = newState;
				stateChanded(m_currentState, oldState);
				m_firstStateChangedCompleted = true;
			}

			T m_currentState;
			bool m_firstStateChangedCompleted{ false };
		};
	}
}

#endif
