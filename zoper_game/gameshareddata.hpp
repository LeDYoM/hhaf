#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/str.hpp>
#include <haf/time/include/timepoint.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/shareddata/include/address.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
enum class GameMode : htps::u8
{
    Token = 0,
    Time  = 1,
};

struct GameSharedData : public haf::shdata::IShareable
{
    static constexpr char address_str[] = "/";

    // MenuScene will write these
    htps::size_type startLevel{0U};
    GameMode gameMode{GameMode::Token};

    // GameScene will write these.
    htps::size_type endLevel{0U};
    htps::size_type score{0U};

    static haf::shdata::Address address()
    {
        haf::shdata::Address addr{address_str};
        return addr;
    }

    htps::str to_str() const
    {
        htps::str temp;
        temp << "Selected level " << startLevel << "\n"
             << " GameMode: " << static_cast<htps::u32>(gameMode);
        return temp;
    }

    static constexpr char StartLevel[]   = "StartLevel";
    static constexpr char GameModeGame[] = "GameMode";
    static constexpr char EndLevel[]     = "EndLevel";
    static constexpr char GameScore[]    = "GameScore";

    bool serialize(htps::Object& obj) const override
    {
        bool result{true};
        result &= obj.set(StartLevel, startLevel);
        result &= obj.set(GameModeGame, gameMode);

        result &= obj.set(EndLevel, endLevel);
        result &= obj.set(GameScore, score);

        return result;
    }

    bool deserialize(htps::Object const& obj) override
    {
        bool result{true};
        result &= obj.getValue(StartLevel).as(startLevel);
        result &= obj.getValue(GameModeGame).as(gameMode);

        result &= obj.getValue(EndLevel).as(endLevel);
        result &= obj.getValue(GameScore).as(score);

        return result;
    }
    
};

}  // namespace zoper

#endif
