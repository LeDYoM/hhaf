#pragma once

#ifndef LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/idatawrapper.hpp>
#include <lib/include/core/timepoint.hpp>

namespace lib::scene
{
/// Component to provide access to resources.
class TimeView : public IDataWrapper
{
public:
    TimePoint now() const;
};

class Timer final : public TimeView
{
public:
    TimePoint ellapsed() const;
    void pause();
    void resume();
    void switchPause();
    void restart();

    constexpr bool isPaused() const noexcept { return is_paused_; }
    void onAttached() override;

private:
    TimePoint started_at_;
    TimePoint time_paused_;
    bool is_paused_;
};
} // namespace lib::scene

#endif
