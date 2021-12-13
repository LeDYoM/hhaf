#ifndef HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <haf/include/time/timepoint.hpp>

namespace haf::time
{
/**
 * @brief @b IDataWrapper to provide access to the current time
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
