#pragma once

#ifndef LIB_TIME_TIMER_TYPE_INCLUDE_HPP
#define LIB_TIME_TIMER_TYPE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::time
{

/**
 * @brief Enum class containing the different types of timer that can be created
 * 
 */
enum class TimerType : mtps::u8
{
    /**
     * @brief The @b Timer will be trigger continuosly until stopped.
     * 
     */
    Continuous,

    /**
     * @brief The @b Timer will be triggered once.
     * 
     */
    OneShot
};
} // namespace lib::time

#endif
