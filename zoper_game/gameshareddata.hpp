#pragma once

#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP__
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/streams.hpp>
#include <lib/include/core/timer.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
    using namespace lib;

    enum class GameMode : u8
    {
        Token = 0,
        Time = 1,
    };

    class GameSharedData
    {
    public:
        size_type startLevel{ 0 };
        size_type endLevel{ 0 };
        size_type score{ 0 };

        bool exitGame{ false };
        GameMode gameMode{ GameMode::Token };
    };
}

#endif
