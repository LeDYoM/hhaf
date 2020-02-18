#pragma once

#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/str.hpp>
#include <lib/time/include/timepoint.hpp>
#include <lib/shareddata/include/ishareable.hpp>
#include "gameplay/direction.hpp"

namespace zoper
{
using namespace lib;

enum class GameMode : u8
{
    Token = 0,
    Time = 1,
};

struct GameSharedData : public shdata::IShareable
{
    // MenuScene will write these
    size_type startLevel{0U};
    GameMode gameMode{GameMode::Token};

    // GameScene will write these.
    size_type endLevel{0U};
    size_type score{0U};

    str to_str() const
    {
        str temp;
        temp << "Selected level " << startLevel << "\n"
             << " GameMode: " << static_cast<u32>(gameMode);
        return temp;
    }

    ~GameSharedData() override = default;
};

} // namespace zoper

#endif
