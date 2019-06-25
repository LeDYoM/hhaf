#pragma once

#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/streamin.hpp>
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

    struct GameSharedData
    {
        size_type startLevel{ 0U };
        size_type endLevel{ 0U };
        size_type score{ 0U };

        bool exitGame{ false };
        GameMode gameMode{ GameMode::Token };
    };

    struct InGameData
    {
        size_type currentLevel{ 0U };
        size_type score{ 0U };
        GameMode gameMode;
    };

    inline const GameSharedData &operator>>(const GameSharedData &gsd, InGameData &igd) noexcept
    {
        igd.currentLevel = gsd.startLevel;
        igd.score = 0U;
        igd.gameMode = gsd.gameMode;
        return gsd;
    }

    inline const InGameData &operator>>(const InGameData &igd, GameSharedData &gsd) noexcept
    {
        gsd.endLevel = igd.currentLevel;
        gsd.score = igd.score;
        gsd.gameMode = igd.gameMode;
        return igd;
    }
}

#endif
