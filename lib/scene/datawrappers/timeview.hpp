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
        virtual TimePoint ellapsed() const;
		void restart();
        void onCreated() override;
    protected:
        TimePoint started_at_;
    };

    class PausableTimer : public Timer
    {
        TimePoint ellapsed() const override;
        void pause();
		void resume();
		void switchPause();

        constexpr bool isPaused() const noexcept { return is_paused_; }
        void onCreated() override;

    private:
        TimePoint time_paused_;
        bool is_paused_;
	};
}

#endif
