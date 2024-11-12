#ifndef ZOPER_GAME_SHARED_DATA_INCLUDE_HPP
#define ZOPER_GAME_SHARED_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/rect.hpp>
#include <facil_math/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/shared_data_updater.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>

namespace zoper
{
enum class GameMode : htps::u8
{
    Token = 0,
    Time  = 1,
};

struct GameSharedData : public haf::shdata::IShareable
{
    static constexpr char address_str[] = "/game_shared_data/";

    // MenuScene will write these
    htps::size_type startLevel{0U};
    GameMode gameMode{GameMode::Token};

    // GameScene will write these.
    htps::size_type endLevel{0U};
    htps::size_type score{0U};

    static haf::shdata::Address address();
    htps::str to_str() const;

    static constexpr char StartLevel[]   = "StartLevel";
    static constexpr char GameModeGame[] = "GameMode";
    static constexpr char EndLevel[]     = "EndLevel";
    static constexpr char GameScore[]    = "GameScore";

    bool serialize(mcs::Object& obj) const override;
    bool deserialize(mcs::Object const& obj) override;
};

}  // namespace zoper

#endif
