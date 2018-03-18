#pragma once

#ifndef LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__
#define LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <mtypes/include/timer.hpp>

namespace lib::scene
{
	class TimerComponent : public IComponent
	{
	public:
		using function_callback_t = function<time::TimePoint>;
		void addTimer(time::TimePoint futuretp, function_callback_t callback);
	private:
		vector<function_callback_t> m_callbacks;
	};
}

#endif
