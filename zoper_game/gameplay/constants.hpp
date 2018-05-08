#pragma once

#ifndef ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__
#define ZOPER_GAMEPLAY_CONSTANTS_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace zoper::gameplay::constants
{
    using namespace lib;

    constexpr u32 MillisAnimationPointsToScore = 600;
    constexpr vector2df EndPositionPointsToScore = vector2df{ 450, 100 };

    constexpr u32 MillisAnimationLaunchPlayerStep = 125;
}

#endif
