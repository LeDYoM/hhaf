#ifndef ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__
#define ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace zoper::gameplay::constants
{
    using namespace haf;

    constexpr mtps::u32 MillisAnimationPointsToScore = 600U;
    constexpr mtps::vector2df EndPositionPointsToScore = mtps::vector2df{ 450.0F, 100.0F };

    constexpr mtps::u32 MillisAnimationLaunchPlayerStep = 125U;
}

#endif
