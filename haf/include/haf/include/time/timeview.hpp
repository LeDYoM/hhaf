#ifndef HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <haf/include/system/idatawrapper.hpp>
#include <haf/include/time/timepoint.hpp>

namespace haf::time
{
/**
 * @brief @b IDataWrapper to provide access to the current time
 */
class TimeView : public sys::IDataWrapper
{
public:
    /**
     * @brief Get the current time.
     * @return TimePoint containing the current time
     */
    TimePoint now() const;
};
}  // namespace haf::time

#endif
