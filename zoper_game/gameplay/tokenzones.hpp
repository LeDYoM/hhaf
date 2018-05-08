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

        vector2dst size{ 18,12 };
        Rectst centerRect{ 7,4,4,4 };

        array<TokenZone, NumWays> tokenZones;

        void generateTokenZones();
    };
}

#endif
