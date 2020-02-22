#pragma once

#ifndef LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <lib/scene/include/idatawrapper.hpp>
#include <lib/time/include/timepoint.hpp>

namespace lib::time
{
/**
 * @brief @b IDataWrapper to provide access to the current time
 */
class TimeView : public scene::IDataWrapper
{
public:
    /**
     * @brief Get the current time.
     * 
     * @return TimePoint containing the current time
     */
    TimePoint now() const;
};
} // namespace lib::time

#endif
