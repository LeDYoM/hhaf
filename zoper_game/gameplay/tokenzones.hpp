#pragma once

#ifndef ZOPER_TOKENZONES_INCLUDE_HPP__
#define ZOPER_TOKENZONES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/streams.hpp>

#include "direction.hpp"

namespace zoper
{
    using namespace lib;
    constexpr size_type NumWays = 4;

    struct TokenZones
    {
        struct TokenZone
        {
            Rectst zone;
            Direction direction;
            size_type size;
        };

        const vector2dst size{ 18,12 };
        const Rectst centerRect{ 7,4,4,4 };

        const array<TokenZone, NumWays> tokenZones
        {
            // From left to right
            TokenZone
            {
                Rectst{ 0,centerRect.top,centerRect.left - 1, centerRect.bottom() - 1 },
                Direction::DirectionData::Right,
                centerRect.size().y
            },
            // From top to bottom
            TokenZone
            {
                Rectst{ centerRect.left , 0, centerRect.right() - 1, centerRect.top - 1 },
                Direction::DirectionData::Down,
                centerRect.size().x
            },
            // From right to left
            TokenZone
            {
                Rectst{ size.x - 1 , centerRect.top,  centerRect.right(), centerRect.bottom() - 1 },
                Direction::DirectionData::Left,
                centerRect.size().y
            },
            // From bottom to top
            TokenZone
            {
                Rectst{ centerRect.left , size.y - 1, centerRect.right() - 1, centerRect.bottom() - 1 },
                Direction::DirectionData::Up,
                centerRect.size().x
            }
        };
    };
}

#endif
