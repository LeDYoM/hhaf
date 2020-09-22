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
enum class GameMode : mtps::u8
{
    Token = 0,
    Time  = 1,
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

    static constexpr char StartLevel[] = "StartLevel";
    static constexpr char GameModeGame[] = "GameMode";
    static constexpr char EndLevel[] = "EndLevel";
    static constexpr char GameScore[] = "GameScore";

    bool serialize(mtps::Object& obj) const override 
    {
        bool result{true};
        result &= obj.set(StartLevel, startLevel);
        result &= obj.set(GameModeGame, gameMode);

        result &= obj.set(EndLevel, endLevel);
        result &= obj.set(GameScore, score);

        return result;

    }

    bool deserialize(mtps::Object const& obj) override
    {
        bool result = true;
        result &= obj.getValue(StartLevel).as(startLevel);
        result &= obj.getValue(GameModeGame).as(gameMode);

        result &= obj.getValue(EndLevel).as(endLevel);
        result &= obj.getValue(GameScore).as(score);

        return result;
    }

    ~GameSharedData() override = default;
};

}  // namespace zoper

#endif
