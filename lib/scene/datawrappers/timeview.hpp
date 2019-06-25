#pragma once

#ifndef LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "idatawrapper.hpp"
#include <lib/include/core/timer.hpp>

namespace lib::scene
{
    /// Component to provide access to resources.
    class TimeView : public IDataWrapper
	{
	public:
        ~TimeView() override;

        TimePoint now() const;
    };

    class Timer : public TimeView
    {
    public:
        TimePoint ellapsed() const;
        void pause();
		void resume();
		void switchPause();
		void restart();

        constexpr bool isPaused() const noexcept { return is_paused_; }
        void onCreated() override;

    private:
        TimePoint started_at_;
        TimePoint time_paused_;
        bool is_paused_;

	};
}

#endif
