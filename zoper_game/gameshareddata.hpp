#pragma once

#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/str.hpp>
#include <haf/time/include/timepoint.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include "gameplay/direction.hpp"

namespace zoper
{
enum class GameMode :  mtps::u8
{
    Token = 0,
    Time = 1,
};

struct GameSharedData : public haf::shdata::IShareable
{
    // MenuScene will write these
    mtps::size_type startLevel{0U};
    GameMode gameMode{GameMode::Token};

    // GameScene will write these.
    mtps::size_type endLevel{0U};
    mtps::size_type score{0U};

    mtps::str to_str() const
    {
        mtps::str temp;
        temp << "Selected level " << startLevel << "\n"
             << " GameMode: " << static_cast<mtps::u32>(gameMode);
        return temp;
    }

    ~GameSharedData() override = default;
};

} // namespace zoper

#endif
