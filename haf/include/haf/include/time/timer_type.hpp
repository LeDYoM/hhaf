HAF_PRAGMA_ONCE
#ifndef HAF_TIME_TIMER_TYPE_INCLUDE_HPP
#define HAF_TIME_TIMER_TYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::time
{

/**
 * @brief Enum class containing the different types of timer that can be created
 *
 */
enum class TimerType : htps::u8
{
    /**
     * @brief The @b Timer will be trigger continuosly until stopped.
     *
     */
    Continuous = 0U,

    /**
     * @brief The @b Timer will be triggered once.
     *
     */
    OneShot = 1U,

    /**
     * @brief The @b Timer will never be triggered. The ellapsed property
     * should be used to read from it. It will stay in the connector until
     * explicitly deleted.
     */
    Free = 2U,
};
}  // namespace haf::time

#endif
