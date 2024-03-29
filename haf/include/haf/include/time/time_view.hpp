HTPS_PRAGMA_ONCE
#ifndef HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <haf/include/time/time_point.hpp>

namespace haf::time
{
/**
 * @brief Subsystem to provide access to the current time
 */
class ITimeView
{
protected:
    ~ITimeView() = default;

public:
    /**
     * @brief Get the current time.
     * @return TimePoint containing the current time
     */
    virtual TimePoint now() const = 0;
};

}  // namespace haf::time

#endif
