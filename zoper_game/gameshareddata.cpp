#include "gameshareddata.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/shared_data_updater.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>

namespace zoper
{

haf::shdata::Address GameSharedData::address()
{
    haf::shdata::Address addr{address_str};
    return addr;
}

htps::str GameSharedData::to_str() const
{
    htps::str temp;
    temp << "Selected level " << startLevel << "\n"
         << " GameMode: " << static_cast<htps::u32>(gameMode);
    return temp;
}

bool GameSharedData::serialize(htps::Object& obj) const
{
    bool result{true};
    result &= obj.set(StartLevel, startLevel);
    result &= obj.set(GameModeGame, gameMode);

    result &= obj.set(EndLevel, endLevel);
    result &= obj.set(GameScore, score);

    return result;
}

bool GameSharedData::deserialize(htps::Object const& obj)
{
    bool result{true};
    result &= obj.getValue(StartLevel).as(startLevel);
    result &= obj.getValue(GameModeGame).as(gameMode);

    result &= obj.getValue(EndLevel).as(endLevel);
    result &= obj.getValue(GameScore).as(score);

    return result;
}

}  // namespace zoper
