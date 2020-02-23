#pragma once

#ifndef LIB_TIME_TIMER_TYPE_INCLUDE_HPP
#define LIB_TIME_TIMER_TYPE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::time
{

enum class TimerType : u8
{
    Continuous,
    OneShot
};
} // namespace lib::time

#endif
