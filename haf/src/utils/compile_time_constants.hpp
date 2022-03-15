#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#ifndef HAF_UTILS_COMPILE_TIME_CONSTANTS_INCLUDE_HPP
#define HAF_UTILS_COMPILE_TIME_CONSTANTS_INCLUDE_HPP

// Transform error prone defines to better compile time constexpr
namespace haf::ctc
{
inline constexpr bool AllowAcceleration{
#ifdef HAF_ALLOW_ACCELERATION
    true
#else
    false
#endif
};

inline constexpr bool ShowFPS{
#ifdef HAF_SHOW_FPS
    true
#else
    false
#endif
};

}

#endif
